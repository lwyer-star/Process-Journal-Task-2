---
layout: default
title: Week 12 — Build, code, and final print tests
---

**Navigation:** [Home](/Process-Journal-Task-2/) · [Materials](/Process-Journal-Task-2/materials.html) · [Week 6](/Process-Journal-Task-2/weeks/week6.html) · [Week 7](/Process-Journal-Task-2/weeks/week7.html) · [Week 8](/Process-Journal-Task-2/weeks/week8.html) · [Week 9](/Process-Journal-Task-2/weeks/week9.html) · [Week 10](/Process-Journal-Task-2/weeks/week10.html) · [Week 11](/Process-Journal-Task-2/weeks/week11.html) · [Week 12](/Process-Journal-Task-2/weeks/week12.html) · [Week 13](/Process-Journal-Task-2/weeks/week13.html) · [Week 14](/Process-Journal-Task-2/weeks/week14.html)

# Week 12 — Build, code, and final print tests

This week I assembled the hardware, flashed the ESP32 with the simple “worst-of-two” rule (eCO₂ + temperature → 3 states), verified LED colours while moving, and printed the enclosure variant that suits the lower-chest mount.

<figure>
  <img src="/Process-Journal-Task-2/assets/images/week12_enclosure_side.jpg"
       alt="Side view of 3D-printed ESP32 enclosure showing internal boards">
  <figcaption><strong>Figure 12.1.</strong> Side view of the 3D-printed main enclosure with the ESP32 and sensor interface boards installed.</figcaption>
</figure>

<figure>
  <img src="/Process-Journal-Task-2/assets/images/week12_enclosure_top_cable.jpg"
       alt="Top view of ESP32 main enclosure with cable routed to remote sensor pod">
  <figcaption><strong>Figure 12.2.</strong> Top view of the main enclosure showing board layout and the braided cable running out to the remote sensor pod.</figcaption>
</figure>


---

## Wiring (ESP32 Thing Plus → sensors + LED)

### I²C (QT / STEMMA)

- 3V3 → sensors VCC  
- GND → sensors GND  
- SDA (GPIO 21) → ENS160/TMP117 SDA  
- SCL (GPIO 22) → ENS160/TMP117 SCL  

### NeoPixel LED (WS2812)

- +5V (VUSB when on USB, or LiPo 3.7 V is OK for a single pixel) → LED VCC  
- GND → LED GND (must share ground with the ESP32)  
- DIN → GPIO 13 (recommend 330 Ω series resistor on data)  
- Optional: 100–1000 µF cap across + and GND near the LED  
- Brightness kept low for comfort and battery

---

## Thresholds v2.1 (tuned)

Decision rule picks the worst of the two signals.

- Slow + water break when eCO₂ ≥ 1250 ppm or temp ≥ 33 °C  
- Shorten route when eCO₂ ≥ 820 ppm or temp ≥ 29 °C  
- Else Good to run

---

## Firmware (Arduino)

Board: SparkFun ESP32 Thing Plus (ESP32 Arduino core)  
Libraries: `Wire.h`, `SparkFun_TMP117.h`, `SparkFun_ENS160.h`, `Adafruit_NeoPixel.h`

```cpp
#include <Wire.h>
#include <SparkFun_TMP117.h>
#include <SparkFun_ENS160.h>
#include <Adafruit_NeoPixel.h>

// NeoPixel
#define NEOPIXEL_PIN   13
#define NUM_PIXELS     1
#define BRIGHTNESS     30
Adafruit_NeoPixel pixel(NUM_PIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

// Sensors
TMP117 tmp;
SparkFun_ENS160 ens;

// Thresholds v2.1
const int   CO2_CAUTION = 820;
const int   CO2_ALERT   = 1250;
const float T_CAUTION   = 29.0;
const float T_ALERT     = 33.0;

enum State { GOOD, CAUTION, ALERT };

void pxOff()   { pixel.clear(); pixel.show(); }
void pxRed()   { pixel.setPixelColor(0, pixel.Color(255,   0,   0)); pixel.show(); }
void pxGreen() { pixel.setPixelColor(0, pixel.Color(  0, 180,   0)); pixel.show(); }
void pxAmber() { pixel.setPixelColor(0, pixel.Color(255, 120,   0)); pixel.show(); }

State decideState(int eco2, float tempC) {
  if (eco2 >= CO2_ALERT   || tempC >= T_ALERT)   return ALERT;
  if (eco2 >= CO2_CAUTION || tempC >= T_CAUTION) return CAUTION;
  return GOOD;
}

void showState(State s) {
  switch (s) {
    case GOOD:    pxGreen(); break;
    case CAUTION: pxAmber(); break;
    case ALERT:   pxRed();   break;
  }
}

void setup() {
  Serial.begin(115200);
  Wire.begin(); // SDA=21, SCL=22 on Thing Plus

  pixel.begin();
  pixel.setBrightness(BRIGHTNESS);
  pxOff();

  if (!tmp.begin())  Serial.println("TMP117 not found (check I2C).");
  if (!ens.begin())  Serial.println("ENS160 not found (check I2C).");
  else               ens.setOperatingMode(SFE_ENS160_STANDARD);

  pxRed(); delay(250); pxAmber(); delay(250); pxGreen(); delay(250);
}

void loop() {
  float tempC = tmp.readTempC();
  int   eco2  = ens.getECO2();
  if (eco2 < 0) eco2 = 600; // warm-up fallback

  State s = decideState(eco2, tempC);
  showState(s);

  Serial.print("TempC="); Serial.print(tempC, 1);
  Serial.print("  eCO2="); Serial.print(eco2);
  Serial.print("  State="); Serial.println(s == GOOD ? "Good" : s == CAUTION ? "Caution" : "Alert");
  delay(1500);
}
Physical build and mounting
Print settings (Bambu P1S, PLA)

Layer height 0.20 mm

Walls 3 (≈ 1.2 mm)

Top/bottom 4–5

Infill 15–20 % gyroid

Orientation: backplate flat; housing upright with minimal supports at the switch window

Post-process: light deburr on strap faces; no sharp edges

Assembly checks

Switch travel is positive and not easy to bump.

Battery is snug; remove to charge (no on-dog charging).

LED window/diffuser visible at ~1–2 m.

Nothing rigid over the trachea; lower-chest position is comfortable.

Remote sensor pod

The air-quality/temperature sensor sits in a small separate pod at the end of the braided cable so it can sit closer to the dog’s chest and away from the bulk of the electronics.

### Remote sensor pod

The air-quality and temperature sensor lives in a small separate pod at the end of the braided cable so it can sit closer to the dog’s chest and away from the main electronics housing.

<figure>
  <img src="/Process-Journal-Task-2/assets/images/week12_sensor_pod_open.jpg"
       alt="Open 3D-printed sensor pod showing temperature sensor PCB">
  <figcaption><strong>Figure 12.3.</strong> Remote sensor pod with the lid removed, showing the temperature/air-quality sensor board and JST connector.</figcaption>
</figure>

<figure>
  <img src="/Process-Journal-Task-2/assets/images/week12_sensor_pod_closed.jpg"
       alt="Closed sensor pod with perforated lid for airflow">
  <figcaption><strong>Figure 12.4.</strong> Sensor pod closed with a perforated lid so air can reach the sensor while still protecting the PCB.</figcaption>
</figure>

---

## Field checks (log template)


22 Oct, 7:15 am — temp __ °C, eCO₂ __ → Good to run
Notes: LED visibility, copy clarity, any confusion.

22 Oct, 5:10 pm — temp __ °C, eCO₂ __ → Shorten route
Notes: water/route prompt useful? stability near boundary?

23 Oct, 1:05 pm — temp __ °C, eCO₂ __ → Slow + water break
Notes: shade stop helpful? any latency?

What worked and what’s next

The simple rule feels predictable; LED readability is good in motion.

Next week: minor threshold/copy tweaks from logs, soften enclosure edges, and capture a short state-transition clip for the showreel.

I also noted a circular ESP32 wearable board that could better match the curve of the harness in a future version:

I also noted a circular ESP32 wearable board that could better match the curve of the harness in a future version:

<figure>
  <img src="/Process-Journal-Task-2/assets/images/week12_alt_esp32_wearable.jpg"
       alt="Duinotech ESP32 wearable development board considered for future iteration">
  <figcaption><strong>Figure 12.5.</strong> Duinotech ESP32 wearable development board spotted in-store. A round board like this would suit a curved, low-profile harness mount in a later iteration.</figcaption>
</figure>

Image checklist (to add)

assets/images/week12-wiring-overview-01.jpg

assets/images/week12-led-colour-check-01.jpg

assets/images/week12-print-variant-mounted-01.jpg

assets/images/week12-field-check-screenshot-01.jpg