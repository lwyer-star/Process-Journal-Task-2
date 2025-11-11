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

## Thresholds v2 (conservative)
- Slow + water break when `eCO₂ ≥ 1200 ppm` **or** `temp ≥ 32 °C`  
- Shorten route when `eCO₂ ≥ 800 ppm` **or** `temp ≥ 28 °C`  
- Else Good to run

Decision rule picks the worst of the two signals.

---

## Firmware (Arduino)

Board: SparkFun ESP32 Thing Plus (ESP32 Arduino core)  
Libraries: Wire (built-in), SparkFun TMP117 (or Adafruit TMP117), Adafruit ENS160 (or your ENS160 lib)

```cpp
// Week 12 firmware: ESP32 Thing Plus + ENS160 (eCO2) + TMP117 (temp) + RGB LED status
#include <Wire.h>

// TMP117 temperature sensor
#include <SparkFunTMP117.h>      // Install "SparkFun TMP117" library
TMP117 tmp;

// ENS160 air-quality sensor (library may vary)
// Example uses Adafruit_ENS160; adjust to match your installed library.
#include <Adafruit_ENS160.h>
Adafruit_ENS160 ens;

// RGB LED pins (common cathode)
const int PIN_R = 13;
const int PIN_G = 12;
const int PIN_B = 14;

// Thresholds (v2)
const int   CO2_CAUTION = 800;
const int   CO2_ALERT   = 1200;
const float T_CAUTION   = 28.0;
const float T_ALERT     = 32.0;

enum State { GOOD, CAUTION, ALERT };

void ledOff()   { digitalWrite(PIN_R, LOW);  digitalWrite(PIN_G, LOW);  digitalWrite(PIN_B, LOW); }
void ledRed()   { digitalWrite(PIN_R, HIGH); digitalWrite(PIN_G, LOW);  digitalWrite(PIN_B, LOW); }
void ledAmber() { digitalWrite(PIN_R, HIGH); digitalWrite(PIN_G, HIGH); digitalWrite(PIN_B, LOW); }
void ledGreen() { digitalWrite(PIN_R, LOW);  digitalWrite(PIN_G, HIGH); digitalWrite(PIN_B, LOW); }

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

  // TMP117 init
  if (!tmp.begin()) {
    Serial.println("TMP117 not found (check I2C wiring).");
  }

  // ENS160 init
  if (!ens.begin()) {
    Serial.println("ENS160 not found (check I2C wiring).");
  } else {
    ens.setMode(ENS160_OPMODE_STD); // standard mode
  }

  // Quick LED channel check
  ledRed();   delay(250);
  ledAmber(); delay(250);
  ledGreen(); delay(250);
}

void loop() {
  // Read temperature
  float tempC = tmp.readTempC(); // some libs require dataReady(); this one tolerates direct read

  // Read eCO2 from ENS160
  ens.readGas();                 // library-dependent; updates internal measurements
  int eco2 = ens.geteCO2();      // ppm (returns -1 if unsupported or error)

  // Fallback if eCO2 not available yet
  if (eco2 < 0) eco2 = 600;

  // Decide and display
  State s = decideState(eco2, tempC);
  showState(s);

  // Serial log for field notes
  Serial.print("TempC="); Serial.print(tempC, 1);
  Serial.print("  eCO2="); Serial.print(eco2);
  Serial.print("  State=");
  Serial.println(s == GOOD ? "Good" : s == CAUTION ? "Caution" : "Alert");

  delay(1500);
}
Print settings (Bambu P1S, PLA)

Layer height 0.20 mm

Walls 3 (≈1.2 mm)

Top/bottom 4–5

Infill 15–20% gyroid

Orientation: backplate flat; housing upright with minimal supports around the switch window

Post-process: light deburr on strap faces; ensure no sharp edges

Assembly checks

Switch travel is positive; not easy to bump.

Battery cannot rattle; remove to charge (no on-dog charging).

LED window/diffuser visible at ~1–2 m.

Nothing rigid sits over the trachea; lower-chest position comfortable.

Field checks (log template)

22 Oct, 7:15 am — temp . °C, eCO₂ ____ → Good to run
Notes: LED visibility, copy clarity, any confusion.

22 Oct, 5:10 pm — temp . °C, eCO₂ ____ → Shorten route
Notes: water/route prompt useful? stability near boundary?

23 Oct, 1:05 pm — temp . °C, eCO₂ ____ → Slow + water break
Notes: shade stop helpful? any latency?
What worked and what’s next

The simple rule feels predictable; LED readability is good in motion.

Next week: minor threshold/copy tweaks from logs, polish enclosure edges, capture a short state-transition clip for the showreel.


### Image checklist to create later
- `assets/images/week12-wiring-overview-01.jpg`  
- `assets/images/week12-led-colour-check-01.jpg`  
- `assets/images/week12-print-variant-mounted-01.jpg`  
- `assets/images/week12-field-check-screenshot-01.jpg