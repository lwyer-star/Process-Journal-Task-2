# Materials — Beyond Human (Task 3)

---
layout: default
title: Materials (BOM)
---

Navigation: [Home](/Process-Journal-Task-2/) · [Week 6](/Process-Journal-Task-2/weeks/week6.html) · [Week 7](/Process-Journal-Task-2/weeks/week7.html) · [Week 8](/Process-Journal-Task-2/weeks/week8.html) · [Week 9](/Process-Journal-Task-2/weeks/week9.html) · [Week 10](/Process-Journal-Task-2/weeks/week10.html) · [Week 11](/Process-Journal-Task-2/weeks/week11.html) · [materials](/Process-Journal-Task-2/materials.html)

# Materials (BOM)


Working bill of materials (BOM) for the harness + glanceable UI prototype.
_Chosen path:_ LED mirror (no haptic for v1).  
_Last updated: 2025-10-23_

---

## Soft-goods (pouch + attachment)

| Part                          | Example spec                         | Qty | Supplier (AU) | Est. unit cost | Notes |
|-------------------------------|--------------------------------------|-----|---------------|----------------|-------|
| Breathable mesh / spacer knit | 2–3 mm spacer knit / sports mesh     | 1   | Spotlight / Lincraft | $5–$10 (offcut) | Ventilates pouch so heat doesn’t trap |
| Backing fabric                | Nylon/poly ripstop 150–210 D         | 1   | Spotlight / eBay | $5–$10 (offcut) | Structure; easy to sew |
| Hook-and-loop (Velcro)        | 20–25 mm sew-on                      | 0.3 m | Spotlight / Jaycar | $3–$6 | Removable pouch + adjustable mount |
| Webbing strap                 | 20–25 mm                             | 0.2 m | Spotlight / Bunnings | $2–$4 | Anchor to harness strap |
| Elastic binding / edge tape   | 15–20 mm                             | 0.4 m | Spotlight | $3–$6 | Round edges; comfort |
| Reflective tape               | 10–15 mm                             | 0.2 m | Spotlight | $3–$6 | Night visibility |
| Snaps / bar-tacks             | Plastic snaps _or_ dense stitches    | 2   | Spotlight | $2–$4 | Secondary retention |

**Pouch guideline:** internal cavity ≈ 45 × 45 × 12 mm(tiny puck + battery). Seam allowance 6–8 mm. Two mesh vents on opposite sides.

---

## Electronics (LED mirror option — chosen)

| Part              | Example spec / swap              | Qty | Supplier (AU) | Est. unit cost | Notes |
|-------------------|----------------------------------|-----|---------------|----------------|-------|
| Microcontroller   | ESP32-C3 SuperMini / Seeed XIAO  | 1   | Core / Jaycar | $8–$18         | BLE link; simple state machine |
| RGB LED (diffused)| 5 mm diffused RGB (common anode/cathode) | 1 | Jaycar / Core | $1–$3  | Mirrors UI state (G/A/R) |
| Resistors         | 220–330 Ω (per LED channel)      | 3   | Jaycar        | <$1            | Current limiting |
| Battery (choose)  | CR2032 holder + cell (_chosen_) | 1 | Jaycar        | $3–$6          | Lighter/simpler than LiPo |
| Switch            | Mini slide switch                | 1   | Jaycar        | $2–$4          | Safe power-off |
| Enclosure         | 3D-printed (TPU/ABS), filleted   | 1   | —             | —              | Rounded edges for comfort |
| Wiring & headers  | Silicone wire / JST              | —   | Jaycar        | $2–$5          | Strain relief important |

> **Why CR2032?** Safer and simpler for v1. No on-body charging. If I later need stronger output, swap to a small **LiPo 150–300 mAh (protected)**—but keep charging off the harness.

---

## Tools

| Tool                               | Notes |
|-----------------------------------|-------|
| Sewing machine + universal needle | For mesh/ripstop |
| Fabric shears, clips, ruler       | Pattern cutting |
| Soldering iron + solder + flux    | Electronics assembly |
| Heat-shrink tubing                | Insulation/strain relief |
| 3D printer (TPU/ABS)              | Enclosure with filleted edges |

---

## Consumables

| Item               | Qty  | Notes |
|--------------------|------|-------|
| Polyester thread   | 1    | Strong; low stretch |
| Double-sided tape  | —    | Temporary placement |
| Isopropyl alcohol  | —    | Clean surfaces before bonding |
| Filament (TPU/ABS) | —    | Enclosure prints |

---

## Risk rule (current thresholds)

- **Heat Index (°C):** `<30 = Good`, `30–32.9 = Caution`, `≥33 = Alert`  
- **AQI PM2.5:** `<100 = Good`, `100–149 = Caution`, `≥150 = Alert`  
- **Dog factor (optional):** bump state up near boundaries for heavy coat/age

> Copy v2 — Chip: _Good to run / Shorten route / Slow + water_.  
> Banner (one line): “Why” + “Action” (kept terse).

---

## Sourcing links 
- Mesh & ripstop:  
- Velcro, webbing, reflective tape:  
- ESP32-C3 / XIAO, RGB LED, resistors, CR2032 + holder, switch:  
- Printing material (TPU/ABS):  

