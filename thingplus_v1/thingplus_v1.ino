/* DES222 – Pet Heat-Stress Harness – v1 hardware test
   Board: SparkFun ESP32 Thing Plus C  |  I2C: SDA=21, SCL=22
   Sensors: SparkFun TMP117 (temp), SparkFun ENS160 (eCO2/TVOC)
   LED: Neo Pixel
*/


#include <Wire.h>
#include <SparkFun_TMP117.h> // Corrected with underscore
#include <SparkFun_ENS160.h> // <-- USING THE SPARKFUN LIBRARY
#include <Adafruit_NeoPixel.h> 

// --- NeoPixel Setup ---
#define NEOPIXEL_PIN   13  // Your NeoPixel data pin
#define NUM_PIXELS     1   
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

// --- Sensor Objects (SparkFun) ---
TMP117 tmp;
SparkFun_ENS160 ens; // <-- Create object for SparkFun library

// --- Thresholds (from your files) ---
const int   CO2_CAUTION = 820;  //
const int   CO2_ALERT   = 1250; //
const float T_CAUTION   = 29.0; //
const float T_ALERT     = 33.0; //

enum State { GOOD, CAUTION, ALERT };

// --- LED Functions (NeoPixel) ---
void ledOff()   { strip.setPixelColor(0, strip.Color(0, 0, 0)); strip.show(); }
void ledRed()   { strip.setPixelColor(0, strip.Color(150, 0, 0)); strip.show(); }
void ledAmber() { strip.setPixelColor(0, strip.Color(150, 150, 0)); strip.show(); } // Amber is R+G
void ledGreen() { strip.setPixelColor(0, strip.Color(0, 150, 0)); strip.show(); }

// --- Logic (from your files) ---
State decideState(int eco2, float tempC) {
  if (eco2 >= CO2_ALERT || tempC >= T_ALERT) return ALERT;
  if (eco2 >= CO2_CAUTION || tempC >= T_CAUTION) return CAUTION;
  return GOOD;
}

void showState(State s) {
  switch (s) {
    case GOOD:    ledGreen(); break;
    case CAUTION: ledAmber(); break;
    case ALERT:   ledRed();   break;
  }
}

void setup() {
  Serial.begin(115200);
  Wire.begin(); // Thing Plus SDA=21, SCL=22

  // --- NeoPixel Init ---
  strip.begin();  
  strip.show();   
  strip.setBrightness(200); 

  if (!tmp.begin()) {
    Serial.println("TMP117 not found (check I2C wiring).");
  }

  // --- SparkFun ENS160 Init ---
  if (!ens.begin()) {
    Serial.println("ENS160 not found (check I2C wiring).");
  } else {
    // Use the SparkFun library's function to set mode
    ens.setOperatingMode(SFE_ENS160_STANDARD); 
  }
  
  // Quick LED channel check
  ledRed();   delay(500);
  ledAmber(); delay(500);
  ledGreen(); delay(500);
  ledOff();   delay(250);
}

void loop() {
  float tempC = tmp.readTempC();
  
  // Use the SparkFun library's function to get eCO2
  int eco2 = ens.getECO2();

  if (eco2 < 0) eco2 = 600; 

  State s = decideState(eco2, tempC);
  showState(s);

  Serial.print("TempC="); Serial.print(tempC, 1);
  Serial.print("  eCO2="); Serial.print(eco2);
  Serial.print("  State=");
  Serial.println(s == GOOD ? "Good" : s == CAUTION ? "Caution" : "Alert");

  delay(1500);
}