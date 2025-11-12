---
layout: default
title: Week 13 — Tweaks, tuning, polish
---

**Navigation:** [Home](/Process-Journal-Task-2/) · [Week 6](/Process-Journal-Task-2/weeks/week6.html) · [Week 7](/Process-Journal-Task-2/weeks/week7.html) · [Week 8](/Process-Journal-Task-2/weeks/week8.html) · [Week 9](/Process-Journal-Task-2/weeks/week9.html) · [Week 10](/Process-Journal-Task-2/weeks/week10.html) · [Week 11](/Process-Journal-Task-2/weeks/week11.html) · [Week 12](/Process-Journal-Task-2/weeks/week12.html) · [Week 13](/Process-Journal-Task-2/weeks/week13.html) · [Week 14](/Process-Journal-Task-2/weeks/week14.html)

# Week 13 — Tweaks, tuning, polish

This week I tuned thresholds using Week 12 logs, cleaned the enclosure edges, improved the LED diffuser seat, and captured short state-transition clips for the final edit.

---

## Threshold tuning (stability near boundaries)

Late-arvo tests showed occasional bouncing around the Caution boundary. I widened the gap slightly to keep the LED and banner stable without losing conservatism.

- Slow + water break: `eCO₂ ≥ 1250 ppm` **or** `temp ≥ 33 °C`  
- Shorten route: `eCO₂ ≥ 820 ppm` **or** `temp ≥ 29 °C`  
- Else: Good to run

Rationale: safety-first; small nudges reduce flip-flopping when readings hover near 28–29 °C or ~800 ppm.

---

## Copy refinements (faster to parse)

- Caution — “Pick a shorter loop; plan a water stop.”  
- Alert — “Slow down now, move to shade, give water.”  
- Good — unchanged (short, calm language still works best).

---

## Enclosure polish

- Added a 0.5 mm recessed diffuser seat so the LED sits flush (less hotspot).  
- Filleted the switch slot corners by +0.3 mm (less snagging on straps).  
- Softened backplate edges and added a thin EVA strip against the harness.

---

## Short test notes (field)

- 25 Oct, 7:05 am — 20.1 °C, eCO₂ 610 → Good  
  Notes: chip alone sufficient; LED visible peripherally.

- 25 Oct, 5:30 pm — 29.3 °C, eCO₂ 840 → Caution  
  Notes: stable (no bouncing); “plan a water stop” prompt helpful.

- 26 Oct, 12:50 pm — 33.4 °C, eCO₂ 1210 → Alert (temp-driven)  
  Notes: red LED decisive; moved to shade and gave water.

---

## Evidence placeholders (add when ready)

Save photos to `assets/images/` using these filenames. Replace the TODO captions later.

<figure>
  <img src="../assets/images/week13-led-diffuser-seat.jpg" alt="Close photo of recessed LED diffuser seat inside the housing lid">
  <figcaption>TODO: diffuser seat detail showing flush fit and less hotspot.</figcaption>
</figure>

<figure>
  <img src="../assets/images/week13-switch-slot-fillet.jpg" alt="Macro shot of switch slot with small corner fillets">
  <figcaption>TODO: switch slot fillet close-up to reduce snag risk.</figcaption>
</figure>

<figure>
  <img src="../assets/images/week13-strap-fit.jpg" alt="Housing mounted on lower chest strap showing rounded edges and EVA strip">
  <figcaption>TODO: strap fit and comfort—rounded edges + EVA backing.</figcaption>
</figure>

<figure>
  <img src="../assets/images/week13-state-transition-clip-still.jpg" alt="Still frame from state transition clip showing LED colour change">
  <figcaption>TODO: still from state-transition clip (Good → Caution or Caution → Alert).</figcaption>
</figure>

---

## Ready for Week 14

- Hardware: printed, assembled, and comfortable in use.  
- Firmware: thresholds v2.1 applied; LED mirror stable.  
- Media: have multiple short clips; next is the final 1–3 min showreel and submission packaging.
