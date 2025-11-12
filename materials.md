---
layout: default
title: Build of Materials (BOM)
---

**Navigation:** [Home](/Process-Journal-Task-2/) · [Materials](/Process-Journal-Task-2/materials.html) · [Week 6](/Process-Journal-Task-2/weeks/week6.html) · [Week 7](/Process-Journal-Task-2/weeks/week7.html) · [Week 8](/Process-Journal-Task-2/weeks/week8.html) · [Week 9](/Process-Journal-Task-2/weeks/week9.html) · [Week 10](/Process-Journal-Task-2/weeks/week10.html) · [Week 11](/Process-Journal-Task-2/weeks/week11.html) · [Week 12](/Process-Journal-Task-2/weeks/week12.html) · [Week 13](/Process-Journal-Task-2/weeks/week13.html) · [Week 14](/Process-Journal-Task-2/weeks/week14.html)

# Materials (BOM)

Working bill of materials (BOM) for the harness + glanceable LED prototype.
_Chosen path:_ LED mirror of UI states (no haptic for v1).
_Last updated: 2025-10-23_

---

## Soft-goods (pouch + attachment)

| Part                          | Example spec                         | Qty | Supplier (AU)         | Est. unit cost | Notes |
|-------------------------------|--------------------------------------|-----|-----------------------|----------------|-------|
| Breathable mesh / spacer knit | 2–3 mm spacer knit / sports mesh     | 1   | Spotlight / Lincraft  | $5–$10 (offcut) | Ventilates pouch so heat doesn’t trap |
| Backing fabric                | Nylon/poly ripstop 150–210 D         | 1   | Spotlight / eBay      | $5–$10 (offcut) | Structure; easy to sew |
| Hook-and-loop (Velcro)        | 20–25 mm sew-on                      | 0.3 m | Spotlight / Jaycar   | $3–$6          | Removable pouch + adjustable mount |
| Webbing strap                 | 20–25 mm                             | 0.2 m | Spotlight / Bunnings | $2–$4          | Anchor to harness strap |
| Elastic binding / edge tape   | 15–20 mm                             | 0.4 m | Spotlight            | $3–$6          | Round edges; comfort |
| Reflective tape               | 10–15 mm                             | 0.2 m | Spotlight            | $3–$6          | Night visibility |
| Snaps / bar-tacks             | Plastic snaps _or_ dense stitches    | 2    | Spotlight            | $2–$4          | Secondary retention |

Pouch guideline: internal cavity ≈ 45 × 45 × 12 mm (tiny puck space). Seam allowance 6–8 mm. Two mesh vents on opposite sides.

---

## Electronics (current build)

| Part                    | Example / model                                   | Qty | Supplier (AU)       | Est. unit cost | Notes |
|------------------------|----------------------------------------------------|-----|---------------------|----------------|-------|
| Microcontroller        | SparkFun Thing Plus – ESP32 WROOM (USB-C)** | 1   | Core / Little Bird  | $35–$45        | BLE built-in, LiPo JST & charger on board |
| Air-quality sensor     | PiicoDev ENS160 (TVOC/eCO₂)                    | 1   | Core (PiicoDev)     | $25–$35        | I²C via QT/STEMMA |
| Temperature sensor     | PiicoDev TMP117 | 1   | Core (PiicoDev)     | $18–$25        | I²C via QT/STEMMA |
| Cable                  | QT/STEMMA cable (male–male)                    | 1   | Core / Little Bird  | $3–$6          | Daisy-chain sensors |
| Indicator LED          | NeoPixel WS2812 (single LED)                   | 1   | Core / Little Bird  | $2–$4          | Mirrors UI state (G/A/R). No resistors needed. |
| Slide switch           | Mini slide switch                                  | 1   | Jaycar              | $2–$4          | Safe power-off |
| Battery                | LiPo 3.7 V 300–500 mAh w/ JST-PH               | 1   | Core / Jaycar       | $10–$18        | Charge off-harness; ESP32 board has charger |
| Enclosure              | 3D-printed PLA housing + backplate             | 1   | —                   | —              | Soft edges; window for LED/switch |
| Wiring / headers       | Silicone wire, JST, heat-shrink                    | —   | Jaycar              | $2–$5          | Strain relief important |

Pin plan (v1): ENS160/TMP117 over I²C (3V3, GND, SDA=21, SCL=22).  
LED: NeoPixel DIN → GPIO13.  
BLE used for manual state testing.

---

## Tools

| Tool                               | Notes |
|------------------------------------|-------|
| Sewing machine + universal needle  | Mesh/ripstop |
| Fabric shears, clips, ruler        | Pattern cutting |
| Soldering iron + solder + flux     | Electronics assembly |
| Heat-shrink tubing                 | Insulation/strain relief |
| 3D printer (PLA)                   | Printed housing + lid (Bambu P1S) |

---

## Consumables

| Item               | Qty  | Notes |
|--------------------|------|-------|
| Polyester thread   | 1    | Strong; low stretch |
| Double-sided tape  | —    | Temporary placement |
| Isopropyl alcohol  | —    | Clean before bonding |
| PLA filament       | —    | Housing + backplate |

---

## Risk rule (current, local sensors)

- **CO₂ (ppm proxy from ENS160 eCO₂):** `< 800 = Good`, `800–1199 = Caution`, `≥ 1200 = Alert`  
- **Temperature (°C):** `< 28 = Good`, `28–31.9 = Caution`, `≥ 32 = Alert`  
- **Decision:** pick the *orst of the two signals.  
- **Dog factor (optional):** bump one level near boundaries for heavy coat/age.

Chip labels: _Good to run / Shorten route / Slow + water_  
Banner: one-line Why + one-line Action (kept terse).

---

## Sourcing (AU quick list)
- **Core Electronics** / PiicoDev — ESP32 boards, ENS160, TMP117, QT cables, LiPo, NeoPixels.  
- **Jaycar** — Slide switch, wire, heat-shrink.  
- **Spotlight / Lincraft / Bunnings** — mesh, ripstop, webbing, hook-and-loop, reflective tape.  
- Filament— PLA from Core, Bilby 3D, or local stores.