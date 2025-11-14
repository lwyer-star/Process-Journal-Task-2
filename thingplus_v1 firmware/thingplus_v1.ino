#include <Wire.h>
#include <SparkFun_TMP117.h>
#include <SparkFun_ENS160.h>
#include <Adafruit_NeoPixel.h>

// --- BLE includes ---
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

// ---------------- NeoPixel config ----------------
#define NEOPIXEL_PIN   13
#define NUM_PIXELS     1
#define BRIGHTNESS     30
Adafruit_NeoPixel pixel(NUM_PIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

// ---------------- Sensor objects ----------------
TMP117 tmp;
SparkFun_ENS160 ens;

// ---------------- Thresholds v2.1 ----------------
const int   CO2_CAUTION = 820;
const int   CO2_ALERT   = 1250;
const float T_CAUTION   = 29.0;
const float T_ALERT     = 33.0;

enum State { GOOD, CAUTION, ALERT };

// ---------------- BLE config ----------------
#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

BLEServer*         pServer         = nullptr;
BLEService*        pService        = nullptr;
BLECharacteristic* pCharacteristic = nullptr;

// Remember last received BLE text (optional)
String lastBleCommand = "";

// Callbacks for when the phone writes to the characteristic
class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic* pCharacteristic) override {
      // FIX: use Arduino String here, not std::string
      String value = pCharacteristic->getValue();

      if (value.length() > 0) {
        Serial.println("*********");
        Serial.print("New BLE value: ");
        Serial.println(value);
        Serial.println("*********");

        lastBleCommand = value;

        // Example: later you could do:
        // if (lastBleCommand == "alert") { showState(ALERT); }
      }
    }
};

// ---------------- LED helper functions ----------------
void pxOff()   { pixel.clear(); pixel.show(); }
void pxRed()   { pixel.setPixelColor(0, pixel.Color(255,   0,   0)); pixel.show(); }
void pxGreen() { pixel.setPixelColor(0, pixel.Color(  0, 180,   0)); pixel.show(); }
void pxAmber() { pixel.setPixelColor(0, pixel.Color(255, 120,   0)); pixel.show(); }

// Decide state based on thresholds
State decideState(int eco2, float tempC) {
  if (eco2 >= CO2_ALERT   || tempC >= T_ALERT)   return ALERT;
  if (eco2 >= CO2_CAUTION || tempC >= T_CAUTION) return CAUTION;
  return GOOD;
}

// Update NeoPixel based on state
void showState(State s) {
  switch (s) {
    case GOOD:    pxGreen(); break;
    case CAUTION: pxAmber(); break;
    case ALERT:   pxRed();   break;
  }
}

// ---------------- Setup ----------------
void setup() {
  Serial.begin(115200);
  delay(1000);

  // --- I2C + sensors ---
  Wire.begin(); // SDA=21, SCL=22 on Thing Plus

  if (!tmp.begin()) {
    Serial.println("TMP117 not found (check I2C).");
  } else {
    Serial.println("TMP117 OK.");
  }

  if (!ens.begin()) {
    Serial.println("ENS160 not found (check I2C).");
  } else {
    Serial.println("ENS160 OK; setting STANDARD mode.");
    ens.setOperatingMode(SFE_ENS160_STANDARD);
  }

  // --- NeoPixel ---
  pixel.begin();
  pixel.setBrightness(BRIGHTNESS);
  pxOff();

  // Startup LED sweep
  pxRed();   delay(250);
  pxAmber(); delay(250);
  pxGreen(); delay(250);
  pxOff();   delay(100);

  // --- BLE setup ---
  Serial.println("BLE setup...");
  Serial.println("1- Install a BLE scanner app on your phone");
  Serial.println("2- Scan for BLE devices");
  Serial.println("3- Connect to HeatHarnessESP32");
  Serial.println("4- Open the custom characteristic to read live values or write text");

  BLEDevice::init("HeatHarnessESP32"); // Name that appears on your phone
  pServer  = BLEDevice::createServer();
  pService = pServer->createService(SERVICE_UUID);

  // Add NOTIFY so we can push updates out
  pCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID,
                      BLECharacteristic::PROPERTY_READ   |
                      BLECharacteristic::PROPERTY_WRITE  |
                      BLECharacteristic::PROPERTY_NOTIFY
                    );

  pCharacteristic->setCallbacks(new MyCallbacks());

  // Initial value
  pCharacteristic->setValue("Hello from HeatHarness");
  pService->start();

  BLEAdvertising* pAdvertising = pServer->getAdvertising();
  pAdvertising->start();

  Serial.println("BLE advertising started.");
}

// ---------------- Loop ----------------
void loop() {
  // --- Read sensors ---
  float tempC = tmp.readTempC();
  int   eco2  = ens.getECO2();
  if (eco2 < 0) eco2 = 600; // warm-up fallback

  // --- Decide state + update LED ---
  State s = decideState(eco2, tempC);
  showState(s);

  // --- Serial logging ---
  Serial.print("TempC=");
  Serial.print(tempC, 1);
  Serial.print("  eCO2=");
  Serial.print(eco2);
  Serial.print("  State=");
  Serial.println(s == GOOD ? "Good" : s == CAUTION ? "Caution" : "Alert");

  // --- BLE update: push a small status string ---
  if (pCharacteristic != nullptr) {
    char buf[80];
    const char* stateText = (s == GOOD) ? "Good" : (s == CAUTION) ? "Caution" : "Alert";
    snprintf(buf, sizeof(buf), "T=%.1f,eCO2=%d,State=%s", tempC, eco2, stateText);

    pCharacteristic->setValue((uint8_t*)buf, strlen(buf));
    pCharacteristic->notify();  // send to connected phone (if any)
  }

  delay(1500); // ~1.5s between updates
}
