---
layout: default
title: Week 12 — Build, code, and final print tests
---

**Navigation:** [Home](/Process-Journal-Task-2/) · [Week 6](/Process-Journal-Task-2/weeks/week6.html) · [Week 7](/Process-Journal-Task-2/weeks/week7.html) · [Week 8](/Process-Journal-Task-2/weeks/week8.html) · [Week 9](/Process-Journal-Task-2/weeks/week9.html) · [Week 10](/Process-Journal-Task-2/weeks/week10.html) · [Week 11](/Process-Journal-Task-2/weeks/week11.html) · [Week 12](/Process-Journal-Task-2/weeks/week12.html)

# Week 12 — Build, code, and final print tests

This week I put the hardware together, flashed the ESP32 with a simple rule (CO₂ + temperature → 3 states), verified LED colours in motion, and printed the enclosure variant that fits the lower-chest mount best.

---

## Wiring (ESP32 Thing Plus → sensors + LED)

### I²C (QT/STEMMA)
- 3V3 → sensors VCC  
- GND → sensors GND  
- SDA (GPIO 21) → ENS160/TMP117 SDA  
- SCL (GPIO 22) → ENS160/TMP117 SCL

### RGB LED (diffused, common **cathode**)
- R anode → ESP32 GPIO 13 through 220–330 Ω  
- G anode → ESP32 GPIO 12 through 220–330 Ω  
- B anode → ESP32 GPIO 14 through 220–330 Ω  
- LED cathode → GND

> If your LED is **common anode**, connect the common to 3V3 and invert the logic in code (write `LOW` to turn a colour on).

---

## Thresholds (v2)

- Slow + water break: `co2 ≥ 1200 ppm` **or** `temp ≥ 32 °C`  
- Shorten route: `co2 ≥ 800 ppm` **or** `temp ≥ 28 °C`  
- Else: Good to run

These are conservative for running with a dog and match Week 11.

---

## Firmware (Arduino IDE)

- Board: **ESP32 Arduino** (SparkFun ESP32 Thing Plus WROOM)  
- Libraries:  
  - **Wire** (built-in)  
  - **SparkFun TMP117** (or Adafruit TMP117)  
  - **Adafruit ENS160** (or Pimoroni/Generic ENS160). If unavailable, you can stub the CO₂ reading temporarily.

> If your ENS160 library reports eCO₂ directly, read that. If it reports TVOC only, keep the structure and mock with a fixed value until swapped.

```cpp
// Week12: ESP32 Thing Plus + ENS160 (eCO2) + TMP117 (temp) + RGB LED status
#include <Wire.h>

// TMP117 (temp)
#include <SparkFunTMP117.h>        // Install "SparkFun TMP117" library
TMP117 tmp;

// ENS160 (air quality) - choose the library you installed.
// Example uses Adafruit_ENS160. If you use a different lib, adjust names accordingly.
#include <Adafruit_ENS160.h>
Adafruit_ENS160 ens;

enum State { GOOD, CAUTION, ALERT };
State state = GOOD;

// GPIOs for RGB (common cathode)
const int PIN_R = 13;  // series resistor 220–330 Ω
const int PIN_G = 12;
const int PIN_B = 14;

// Thresholds (v2)
const int   CO2_CAUTION = 800;
const int   CO2_ALERT   = 1200;
const float T_CAUTION   = 28.0;
const float T_ALERT     = 32.0;

// Helper: set LED to a solid colour
void ledOff()  { digitalWrite(PIN_R, LOW); digitalWrite(PIN_G, LOW); digitalWrite(PIN_B, LOW); }
void ledRed()  { digitalWrite(PIN_R, HIGH); digitalWrite(PIN_G, LOW);  digitalWrite(PIN_B, LOW);  }
void ledAmber(){ digitalWrite(PIN_R, HIGH); digitalWrite(PIN_G, HIGH); digitalWrite(PIN_B, LOW);  }
void ledGreen(){ digitalWrite(PIN_R, LOW);  digitalWrite(PIN_G, HIGH); digitalWrite(PIN_B, LOW);  }

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
  Wire.begin(); // SDA 21, SCL 22 on Thing Plus by default

  // TMP117 init
  if (!tmp.begin()) {
    Serial.println("TMP117 not found; check I2C wiring.");
  }

  // ENS160 init
  if (!ens.begin()) {
    Serial.println("ENS160 not found; check I2C wiring.");
  } else {
    ens.setMode(ENS160_OPMODE_STD); // standard mode
  }

  // brief colour cycle to confirm LED channels
  ledRed();   delay(300);
  ledAmber(); delay(300);
  ledGreen(); delay(300);
}

void loop() {
  // Read temperature
  float tempC = NAN;
  if (tmp.dataReady()) {
    tempC = tmp.readTempC();
  } else {
    tempC = tmp.readTempC(); // force read if your lib requires it
  }

  // Read eCO2 from ENS160
  int eco2 = -1;
  ens.readGas();           // library-dependent; may update internal values
  eco2 = ens.geteCO2();    // returns eCO2 ppm if supported

  // Fallback if sensor lib doesn’t expose eCO2 (temporary dev)
  if (eco2 < 0) {
    eco2 = 600; // mock baseline value so the rest of the pipeline can be tested
  }

  // Decide state and show LED
  state = decideState(eco2, tempC);
  showState(state);

  // Serial log for Week 12 field notes
  Serial.print("TempC: "); Serial.print(tempC, 1);
  Serial.print("  eCO2: "); Serial.print(eco2);
  Serial.print("  State: ");
  Serial.println(state == GOOD ? "Good" : state == CAUTION ? "Caution" : "Alert");

  delay(1500); // gentle cadence for walking tests
}
