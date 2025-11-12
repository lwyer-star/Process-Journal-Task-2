/* DES222 – Pet Heat-Stress Harness – v1 hardware test
   Board: SparkFun ESP32 Thing Plus C  |  I2C: SDA=21, SCL=22
   Sensors: SparkFun TMP117 (temp), SparkFun ENS160 (eCO2/TVOC)
   LED: R=GPIO13, G=GPIO12, B=GPIO14 (common cathode)
*/


#include <Wire.h>
#include <SparkFun_TMP117.h>
#include <SparkFun_ENS160.h> // Using the SparkFun library

TMP117 tmp;
SparkFun_ENS160 ens; // Create object for SparkFun library

// --- Pins and Thresholds (from your files) ---
const int PIN_R = 13;
const int PIN_G = 12;
const int PIN_B = 14;

const int   CO2_CAUTION = 820;  //
const int   CO2_ALERT   = 1250; //
const float T_CAUTION   = 29.0; //
const float T_ALERT     = 33.0; //

enum State { GOOD, CAUTION, ALERT };

// --- LED Functions (from your file) ---
void ledOff()   { digitalWrite(PIN_R, LOW);  digitalWrite(PIN_G, LOW);  digitalWrite(PIN_B, LOW); }
void ledRed()   { digitalWrite(PIN_R, HIGH); digitalWrite(PIN_G, LOW);  digitalWrite(PIN_B, LOW); }
void ledAmber() { digitalWrite(PIN_R, HIGH); digitalWrite(PIN_G, HIGH); digitalWrite(PIN_B, LOW); }
void ledGreen() { digitalWrite(PIN_R, LOW);  digitalWrite(PIN_G, HIGH); digitalWrite(PIN_B, LOW); }

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
  pinMode(PIN_R, OUTPUT);
  pinMode(PIN_G, OUTPUT);
  pinMode(PIN_B, OUTPUT);
  ledOff();

  Serial.begin(115200);
  Wire.begin(); // Thing Plus SDA=21, SCL=22

  if (!tmp.begin()) {
    Serial.println("TMP117 not found (check I2C wiring).");
  }

  if (!ens.begin()) {
    Serial.println("ENS160 not found (check I2C wiring).");
  } else {
    ens.setOperatingMode(SFE_ENS160_STANDARD); // SparkFun library's init command
  }
  
  // Quick LED channel check
  ledRed();   delay(250);
  ledAmber(); delay(250);
  ledGreen(); delay(250);
}

void loop() {
  float tempC = tmp.readTempC();
  
  int eco2 = ens.getECO2(); // SparkFun library's read command

  if (eco2 < 0) eco2 = 600; 

  State s = decideState(eco2, tempC);
  showState(s);

  Serial.print("TempC="); Serial.print(tempC, 1);
  Serial.print("  eCO2="); Serial.print(eco2);
  Serial.print("  State=");
  Serial.println(s == GOOD ? "Good" : s == CAUTION ? "Caution" : "Alert");

  delay(1500);
}