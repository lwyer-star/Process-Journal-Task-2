---
layout: default
title: Week 12 — Build, code, and final print tests
---

**Navigation:** [Home](/Process-Journal-Task-2/) · [Materials](/Process-Journal-Task-2/materials.html) · [Week 6](/Process-Journal-Task-2/weeks/week6.html) · [Week 7](/Process-Journal-Task-2/weeks/week7.html) · [Week 8](/Process-Journal-Task-2/weeks/week8.html) · [Week 9](/Process-Journal-Task-2/weeks/week9.html) · [Week 10](/Process-Journal-Task-2/weeks/week10.html) · [Week 11](/Process-Journal-Task-2/weeks/week11.html) · [Week 12](/Process-Journal-Task-2/weeks/week12.html) · [Week 13](/Process-Journal-Task-2/weeks/week13.html) · [Week 14](/Process-Journal-Task-2/weeks/week14.html)

# Week 12 — Build, code, and final print tests

This week I put the hardware together, flashed the ESP32 with a simple rule (CO₂ + temperature → 3 states), verified LED colours in motion, and printed the enclosure variant that fits the lower-chest mount best.

---

## Wiring (ESP32 Thing Plus → sensors + LED)

### I²C (QT/STEMMA)
- 3V3 → sensors VCC
- GND → sensors GND
- SDA (GPIO 21) → ENS160/TMP117 SDA
- SCL (GPIO 22) → ENS160/TMP117 SCL

### NeoPixel LED (WS2812)
- VCC/5V → 3V3
- GND → GND
- Data In (DIN) → GPIO 13

---

## Thresholds v2.1 (Tuned)
(Using the tuned thresholds from Week 13 logs)
- Slow + water break when `eCO₂ ≥ 1250 ppm` **or** `temp ≥ 33 °C`
- Shorten route when `eCO₂ ≥ 820 ppm` **or** `temp ≥ 29 °C`
- Else Good to run

Decision rule picks the worst of the two signals.

---

## Firmware (Arduino)

Board: SparkFun ESP32 Thing Plus (ESP32 Arduino core)
Libraries:
- `Wire.h` (built-in)
- `SparkFun_TMP117.h`
- `SparkFun_ENS160.h`
- `Adafruit_NeoPixel.h`

```cpp
#include <Wire.h>
#include <SparkFun_TMP117.h> // Corrected with underscore
#include <SparkFun_ENS160.h> // Using the SparkFun library
#include <Adafruit_NeoPixel.h> 

// --- NeoPixel Setup ---
#define NEOPIXEL_PIN   13  // Your NeoPixel data pin
#define NUM_PIXELS     1   
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

// --- Sensor Objects (SparkFun) ---
TMP117 tmp;
SparkFun_ENS160 ens; // Create object for SparkFun library

// --- Thresholds (v2.1 - Tuned in Week 13) ---
const int   CO2_CAUTION = 820;
const int   CO2_ALERT   = 1250;
const float T_CAUTION   = 29.0;
const float T_ALERT     = 33.0;

enum State { GOOD, CAUTION, ALERT };

// --- LED Functions (NeoPixel) ---
void ledOff()   { strip.setPixelColor(0, strip.Color(0, 0, 0)); strip.show(); }
void ledRed()   { strip.setPixelColor(0, strip.Color(150, 0, 0)); strip.show(); }
void ledAmber() { strip.setPixelColor(0, strip.Color(150, 150, 0)); strip.show(); } // Amber is R+G
void ledGreen() { strip.setPixelColor(0, strip.Color(0, 150, 0)); strip.show(); }

// --- Logic ---
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

  if (eco2 < 0) eco2 = 600; // Fallback if eCO2 not available yet

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
Layer height 0.20 mm Walls 3 (≈1.2 mm) Top/bottom 4–5 Infill 15–20% gyroid Orientation: backplate flat; housing upright with minimal supports around the switch window Post-process: light deburr on strap faces; ensure no sharp edges

Assembly checks
Switch travel is positive; not easy to bump.

Battery cannot rattle; remove to charge (no on-dog charging).

LED window/diffuser visible at ~1–2 m.

Nothing rigid sits over the trachea; lower-chest position comfortable.

Field checks (log template)
22 Oct, 7:15 am — temp . °C, eCO₂ ____ → Good to run Notes: LED visibility, copy clarity, any confusion.

22 Oct, 5:10 pm — temp . °C, eCO₂ ____ → Shorten route Notes: water/route prompt useful? stability near boundary?

23 Oct, 1:05 pm — temp . °C, eCO₂ ____ → Slow + water break Notes: shade stop helpful? any latency?

What worked and what’s next
The simple rule feels predictable; LED readability is good in motion.

Next week: minor threshold/copy tweaks from logs, polish enclosure edges, capture a short state-transition clip for the showreel.

Image checklist to create later
assets/images/week12-wiring-overview-01.jpg

assets/images/week12-led-colour-check-01.jpg

assets/images/week12-print-variant-mounted-01.jpg

assets/images/week12-field-check-screenshot-01.jpg