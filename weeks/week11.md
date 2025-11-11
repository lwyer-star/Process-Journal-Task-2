---
layout: default
title: Week 11 — Hardware pivot (ESP32), thresholds, LED mirror
---

**Navigation:** [Home](/Process-Journal-Task-2/) · [Week 6](/Process-Journal-Task-2/weeks/week6.html) · [Week 7](/Process-Journal-Task-2/weeks/week7.html) · [Week 8](/Process-Journal-Task-2/weeks/week8.html) · [Week 9](/Process-Journal-Task-2/weeks/week9.html) · [Week 10](/Process-Journal-Task-2/weeks/week10.html) · [Week 11](/Process-Journal-Task-2/weeks/week11.html)

# Week 11 — Hardware pivot + clearer thresholds

This week I committed to the ESP32 hardware, wired local sensors, printed a soft-edged PLA housing, and mirrored the UI states on a diffused RGB LED. Copy was kept terse for glanceability.

---

## What I built


### Board
SparkFun Thing Plus ESP32 (BLE/USB-C). Chosen for native BLE and simple 3.3 V power.

### Sensors
PiicoDev ENS160 (eCO₂/TVOC) + TMP117 (temperature) over I²C via QT/STEMMA. Simple, keyed cabling and stable libraries.

### Indicator
Diffused RGB LED on GPIO 13/12/14 with 220–330 Ω resistors. Solid colours only (no flashing) for glanceability and battery life.

### Enclosure
PLA print with rounded edges, mounted lower on the chest. Lid/backplate includes a slide-switch window; no on-dog charging.


<figure>
  <img src="../assets/images/housing-on-strap.jpg" alt="Soft-edged rectangular PLA housing mounted low on the chest strap">
  <figcaption>Printed PLA housing with filleted edges mounted low on the chest strap. LED window visible at ~1–2 m.</figcaption>
</figure>

<figure>
  <img src="../assets/images/housing-open.jpg" alt="Inside the housing showing ESP32, RGB LED with resistors, and sensor wiring">
  <figcaption>Inside view: ESP32, RGB LED on GPIO 13/12/14 via 220–330 Ω, ENS160/TMP117 on I²C (3V3, GND, SDA 21, SCL 22).</figcaption>
</figure>

---

## Risk rule v2 (now includes local CO₂ + temp)
Inputs: CO₂ (ppm from ENS160 eCO₂), Temperature (°C).  
Decision: choose the **worst** of the two signals.

```pseudo
state = "Good to run"

if co2_ppm >= 1200 or temp_c >= 32:
    state = "Slow + water break"
elif co2_ppm >= 800 or temp_c >= 28:
    state = "Shorten route"
# else: Good to run```

Optional dog factor: when near a boundary, a small multiplier (e.g., ×1.05 for heavy coat/age) can bump the state up one level.

Copy v2 (kept terse)

Chip labels (≤3 words): Good to run · Shorten route · Slow + water

Banner (one line each):

Good — Conditions safe. Keep an easy pace.

Caution — Heat/air rising. Pick a shorter loop; plan water.

Alert — High heat/air. Slow down, shade, give water.

Physical feedback (plan & tests)

Using one diffused RGB LED as a mirror of the UI chip: green = Good, amber = Caution, red = Alert. Solid colours only (no flashing).

<div class="img-row"> <figure> <img src="../assets/images/week10-led-sketch.jpg" alt="Sketch of harness pouch with small RGB LED window"> <figcaption>LED mirror of UI state in the pouch window.</figcaption> </figure> <figure> <img src="../assets/images/week10-haptic-sketch.jpg" alt="Sketch exploring tiny coin vibration motor placement in padded pouch"> <figcaption>Alternative considered: brief haptic on Alert (deferred).</figcaption> </figure> </div> <style> .img-row{display:flex;gap:12px;flex-wrap:wrap;margin:8px 0} .img-row figure{flex:1 1 360px;margin:0} .img-row img{width:100%;height:auto;border-radius:8px} .img-row figcaption{font-size:.9rem;color:#4b5563;margin-top:6px} </style>
Evidence (this week)
<figure> <img src="../assets/images/week10-parts-flatlay-02.jpg" alt="Flat lay of air-quality sensor, temperature sensor, ESP32 board, LiPo battery and QT/STEMMA cable (annotated)"> <figcaption>Annotated parts flat-lay used for wiring plan and BOM cross-check.</figcaption> </figure> <figure> <img src="../assets/images/week10-cad-housing-internals-iso-01.png" alt="CAD isometric view of PLA housing showing internal posts and slide-switch window"> <figcaption>Housing internals: standoffs for ESP32, rounded interior edges, and a small window for the slide switch/light pipe.</figcaption> </figure> <figure> <img src="../assets/images/week10-cad-housing-internals-02.png" alt="CAD interior view highlighting board standoffs, cable channel and switch pocket"> <figcaption>Detail of internal features: standoffs, cable relief, and switch pocket to avoid board stress.</figcaption> </figure> <figure> <img src="../assets/images/week10-cad-housing-lid-01.png" alt="CAD view of housing with lid closed and slide-switch slot visible"> <figcaption>Closed-lid view confirming tolerances and slot alignment for the switch.</figcaption> </figure>
Tests & observations

Placement: lower chest mount stayed stable over a 5–10 min walk/jog.

Readability: LED visible at ~1–2 m; chip alone usually enough; banner opened on demand.

Copy: stronger wording in Alert improved compliance.

What I’ll do next (Week 12)

Two short field checks (cool morning vs warm arvo) and log CO₂/Temp → state.

Lock threshold numbers for v2.

Capture a short state-transition clip for the showreel.