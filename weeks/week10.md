**Navigation:** **Navigation:** [Home](/Process-Journal-Task-2/) · [Week 6](/Process-Journal-Task-2/weeks/week6.html) · [Week 7](/Process-Journal-Task-2/weeks/week7.html) · [Week 8](/Process-Journal-Task-2/weeks/week8.html) · [Week 9](/Process-Journal-Task-2/weeks/week9.html) · [Week 10](/Process-Journal-Task-2/weeks/week10.html) · [Week 11](/Process-Journal-Task-2/weeks/week11.html)


# Week 10 — Task 3 kickoff (refine thresholds, copy, physical feedback)

This week I start Task 3 by turning the Week 9 prototype into a tighter, testable build. I’m focusing on: (1) refining thresholds for heat + air quality, (2) sharpening the banner copy for “at-a-glance” reading, and (3) exploring a simple physical feedback option (LED/haptic) that mirrors the UI states.

---

### Goals (this week)
- Tune **risk rule v2** and document exact thresholds.
- Shorten banner copy (keep chip terse; move detail to expanded banner).
- Decide and sketch one **physical feedback** pathway (LED or haptic).
- Run two short **field checks** and log results.

---

### Changes from last week
- Added three state screenshots to Week 8 (Normal/Caution/Alert).
- Re-ordered sketches → prototype for clearer flow.
- Recorded a 3-min intro/presentation and embedded it on Home.

---

### Risk rule v2 (draft)

I’m keeping a 3-state model and nudging thresholds to be conservative for running with a dog.

<div class="table-wrap">
<table class="bom">
  <thead>
    <tr>
      <th>Signal</th>
      <th>Metric</th>
      <th>Normal</th>
      <th>Caution</th>
      <th>Alert</th>
      <th>Notes</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>Heat</td>
      <td>Heat Index (°C)</td>
      <td>&lt; 30</td>
      <td>30–32.9</td>
      <td>≥ 33</td>
      <td>Derived from temp + RH; conservative for exertion.</td>
    </tr>
    <tr>
      <td>Air quality</td>
      <td>AQI (PM2.5)</td>
      <td>&lt; 100</td>
      <td>100–149</td>
      <td>≥ 150</td>
      <td>Uses nearest station; show <em>approximate</em> badge if not local.</td>
    </tr>
    <tr>
      <td>Dog factor</td>
      <td>Multiplier</td>
      <td>×1.00</td>
      <td>×1.05</td>
      <td>×1.10</td>
      <td>Optional: heavier coat/age pushes state up sooner.</td>
    </tr>
  </tbody>
</table>
</div>

<style>
  .table-wrap{overflow-x:auto;margin:.5rem 0 1rem}
  table.bom{width:100%;border-collapse:collapse;font-size:.95rem}
  .bom th,.bom td{border:1px solid #e5e7eb;padding:8px 10px;vertical-align:top;text-align:left}
  .bom thead th{background:#f7f7f7;font-weight:700}
</style>

**Decision rule (pseudo):**
```pseudo
state = "Good to run"

if AQI >= 150 or heat_index_c >= 33:
    state = "Slow + water break"
elif AQI >= 100 or heat_index_c >= 30:
    state = "Shorten route"

# optional dog factor: if dog_factor >= 1.05 then bump state up one level when near boundaries


Copy v2 (short + glanceable)

Chip labels (3 words max):

Good to run

Shorten route

Slow + water

Banner (one line each):

Good to run — Conditions safe. Keep an easy pace.

Shorten route — Heat/AQI up. Pick a shorter loop; plan water.

Slow + water — High heat/AQI. Slow down, move to shade, give water.

Rationale: verb-first, no hedging, colour + label paired; detail stays in the expanded banner if needed.

Physical feedback option (sketch + plan)

I’m exploring a single RGB LED as a mirror of the UI chip: green = Good, amber = Caution, red = Alert. This can live in the pouch window and is visible at a glance.

<div class="img-row"> <figure> <img src="../assets/images/week10-led-sketch.jpg" alt="Sketch of harness pouch with small RGB LED window"> <figcaption>LED mirror of UI state in the pouch window.</figcaption> </figure> <figure> <img src="../assets/images/week10-haptic-sketch.jpg" alt="Sketch exploring tiny coin vibration motor placement in padded pouch"> <figcaption>Alternative: coin vibration motor for brief haptic on Alert.</figcaption> </figure> </div> <style> .img-row{display:flex;gap:12px;flex-wrap:wrap;margin:8px 0} .img-row figure{flex:1 1 360px;margin:0} .img-row img{width:100%;height:auto;border-radius:8px} .img-row figcaption{font-size:.9rem;color:#4b5563;margin-top:6px} </style>

Quick BOM (option A — LED):

RGB LED 5mm or diffused SMD behind a small light pipe

Series resistor, wired to microcontroller pin(s)

PWM for brightness; no constant flashing (battery + comfort)

Quick BOM (option B — haptic):

10–12 mm coin vibration motor with driver

Very brief pulse on transition into Alert (< 300 ms)

Testing plan (this week)

Scenarios: cool morning vs warm afternoon; breezy vs still.
Method: 10–15 min walks/jogs; note readability and action clarity.
Data: record temp, RH, AQI (station + suburb), state transitions.

18 Oct, 7:30 am — 19 °C, 65% RH, AQI 42 → Good to run. Chip readable; banner fine at arm's length.
18 Oct, 4:50 pm — 27 °C, 70% RH, AQI 108 → Shorten route. Copy clear; added water stop.
19 Oct, 1:10 pm — 31 °C, 60% RH, AQI 156 → Slow + water. Shade helpful; haptic idea seems useful.

Evidence (images)
<figure> <img src="../assets/images/week10-run-screenshot.jpg" alt="Screenshot of prototype 'Shorten route' state during afternoon test"> <figcaption>Afternoon test showing <em>Shorten route</em> with approximate label (nearest station).</figcaption> </figure> <figure> <img src="../assets/images/week10-led-prototype.jpg" alt="Photo of small diffused LED glowing amber inside pouch window"> <figcaption>LED prototype reflecting the UI state without looking at the phone.</figcaption> </figure>
What I learned / changes to make

Readability in motion is good; copy v2 feels faster to parse.

Boundaries at HI 30/33 feel right; will watch AQI 90–110 edge cases.

Physical feedback helps when the phone isn’t visible; LED seems simpler than haptic for now.

Next week (Week 11)

Lock thresholds table and publish risk rule v2.

Build a tiny “expanded banner” with 1-line reason + 1 action.

If time: LED prototype with quick swapable colours (no flashing).


---

### 2) Image checklist for Week 10
Save to `assets/images/` with these names (or your own, just keep paths consistent):

- `week10-led-sketch.jpg` — quick drawing of LED in pouch window  
- `week10-haptic-sketch.jpg` — optional drawing of coin motor placement  
- `week10-run-screenshot.jpg` — screenshot of your UI in “Caution” outside  
- `week10-led-prototype.jpg` — photo of a small amber/green LED test (if you do it)

---

### 3) Update nav (if the top nav isn’t auto-generated)
In **Week 9** and **index.md**, add a link to Week 10 like you’ve done for other weeks:
```markdown
**Navigation:** [Home](/Process-Journal-Task-2/) · [Week 6](./week6.md) · [Week 7](./week7.md) · [Week 8](./week8.md) · [Week 9](./week9.md) · **[Week 10](./week10.md)**
