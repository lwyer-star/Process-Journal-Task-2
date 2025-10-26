**Navigation:** [Home](/Process-Journal-Task-2/) · [Week 6](./week6.md) · [Week 7](./week7.md) · [Week 8](./week8.md) · [Week 9](./week9.md) · [Week 10](./week10.md) · **[Week 11](./week11.md)**

# Week 11 — Expanded banner & clearer actions

This week I implemented the **expanded banner**: tapping the chip reveals one short **Why** and one clear **Action**. I also added a **Refresh** button and an **approximate** badge for non-local AQI.

---

### What I set out to do
- Add expanded banner (Why + one Action).
- Make copy faster to parse in motion.
- Keep the 3-state logic (Good / Caution / Alert).

---

### What I built
- **Expanded banner** that opens on tap (chip stays terse; banner carries reason + action).
- **Refresh** control to re-check state on demand.
- **Approximate** badge when data comes from the nearest station (not local).

<figure>
  <img src="../assets/images/week11-expanded-caution.png" alt="Expanded banner open in Caution with Why and one Action">
  <figcaption>Expanded banner — <em>Caution</em>. One line of “Why” and one actionable step.</figcaption>
</figure>

<figure>
  <img src="../assets/images/week11-expanded-alert.png" alt="Expanded banner open in Alert with Why and one Action">
  <figcaption>Expanded banner — <em>Alert</em>. Stronger, unambiguous language; no extra info.</figcaption>
</figure>

> **Copy v2 (kept terse)**
> - **Chip:** Good to run / Shorten route / Slow + water  
> - **Banner (1 line):**  
>   - Good — Conditions safe. Keep an easy pace.  
>   - Caution — Heat/AQI up. Pick a shorter loop; plan water.  
>   - Alert — High heat/AQI. Slow down, shade, give water.

---

### Tests & observations
20 Oct, 7:20 am — 20 °C, 68% RH, AQI 54 (local) → Good.
Notes: Chip readable; banner not needed unless tapped.

20 Oct, 5:10 pm — 28 °C, 62% RH, AQI 112 (approx) → Caution.
Notes: “Plan water” prompt was useful; approximate badge reduced confusion.

21 Oct, 1:05 pm — 31 °C, 58% RH, AQI 152 (approx) → Alert.
Notes: Stronger wording improved compliance; opening on demand works best.

---

### What I learned / next changes
- Expanded banner should **open on demand** (tap), not automatically.
- **Approximate** badge helps when station ≠ suburb.
- Next: explore **physical feedback (LED)** to reduce screen glances.

**Next week (Week 12)**
- 2–3 field checks (cool morning vs warm arvo).  
- Lock thresholds v2 numbers; add a short battery/performance note.  
- Capture a **state-transition** clip for the showreel.

---

### Links
- **Live demo:** [/banner-prototype/](../banner-prototype/)  
- **Materials (BOM):** [materials.md](./materials.md)
