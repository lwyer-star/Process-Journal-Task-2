# Materials — Beyond Human (Task 3)

This is the working bill of materials (BOM) for the harness + glanceable UI prototype. I’ll update it as I test and refine.

_Last updated: 2025-10-23_

---

## Soft-goods (pouch + attachment)

| Part                            | Example spec                           | Qty | Est. weight | Notes |
|---------------------------------|----------------------------------------|-----|-------------|-------|
| Breathable mesh / spacer knit   | 2–3 mm 3D spacer or sports mesh        | 1   | 3–6 g       | Ventilates pouch so heat doesn’t trap |
| Backing fabric                  | Nylon/poly ripstop 150–210 D           | 1   | 3–5 g       | Structure; easy to sew |
| Hook-and-loop (Velcro)          | 20–25 mm sew-on                        | 0.3 m | 2–4 g     | Removable pouch + adjustable mount |
| Webbing strap                   | 20–25 mm                               | 0.2 m | 2–3 g     | Anchor to harness strap |
| Elastic binding / edge tape     | 15–20 mm                               | 0.4 m | 1–2 g     | Round edges; comfort against fur |
| Reflective tape                 | 10–15 mm                               | 0.2 m | <1 g      | Night visibility |
| Snaps / bar-tacks               | Plastic snaps or dense stitches        | 2   | negligible | Secondary retention |

**Pouch guideline:** internal cavity ≈ **45 × 45 × 12 mm** (tiny “puck” + battery). Seam allowance 6–8 mm. Two mesh vents on opposite sides.

---

## Electronics (LED mirror option)

| Part                | Example spec                     | Qty | Est. weight | Notes |
|--------------------|----------------------------------|-----|-------------|-------|
| Microcontroller     | nRF52840 module _or_ ESP32-C3 mini | 1 | 3–8 g      | BLE link; simple state machine |
| RGB LED             | 5 mm diffused _or_ SMD + light pipe | 1 | <1 g       | Mirrors UI state (G/A/R) |
| Resistors           | 220–330 Ω (per LED channel)      | 3   | negligible | Current limiting |
| Battery (choose)    | CR2032 _or_ LiPo 150–300 mAh     | 1 | 3 g / 6–8 g | Coin cell = lighter; LiPo = stronger output |
| Switch              | Mini slide switch                | 1 | <1 g        | Safe power-off |
| Enclosure           | 3D printed (TPU/ABS), filleted   | 1 | 5–10 g      | Rounded edges for comfort |
| Wiring & headers    | Silicone-insulated, JST, etc.    | — | —           | Strain relief important |

> Safety: **No charging on-dog.** Charge LiPo off harness; use protected cells.

---

## Tools (what I’m using)

| Tool                | Spec / Notes |
|--------------------|--------------|
| Sewing machine + universal needle | For mesh/ripstop |
| Fabric shears, clips, ruler       | Pattern cutting |
| Soldering iron + solder + flux    | Electronics assembly |
| Heat-shrink tubing                 | Insulation/strain relief |
| 3D printer (TPU/ABS)               | Enclosure with filleted edges |

---

## Consumables

| Item                  | Qty  | Notes |
|-----------------------|------|-------|
| Polyester thread      | 1    | Strong; low stretch |
| Double-sided tape     | —    | Temporary placement |
| Isopropyl alcohol     | —    | Clean surfaces before bonding |
| Filament (TPU/ABS)    | —    | Enclosure prints |

---

## Risk rule (current thresholds)

- **Heat Index (°C):** `<30 = Good`, `30–32.9 = Caution`, `≥33 = Alert`
- **AQI PM2.5:** `<100 = Good`, `100–149 = Caution`, `≥150 = Alert`
- **Dog factor (optional):** bump state up near boundaries for heavy coat/age

> Copy v2 — Chip: _Good to run / Shorten route / Slow + water_  
> Banner (one line): “Why” + “Action” (kept terse)

---

## Sourcing notes (to fill as I order)
- Mesh & ripstop:  
- Velcro, webbing, reflective tape:  
- MCU, LED, CR2032/LiPo, switch:  
- Printing material (TPU/ABS):  

