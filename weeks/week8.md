---
layout: default
title: Week 8 — Prototyping & tests
---

**Navigation:** [Home](/Process-Journal-Task-2/) · [Week 6](./week6) · [Week 7](./week7) · [Week 8](./week8) · [Week 9](./week9)

# Week 8 — Prototyping & tests

The step forward and planned focus of this week is turning Week 7 research into a working prototype. I sketched the UI, built a first version of the banner logic and ran quick tests to see what works in motion.

### Sketches — early UI ideas
<img src="../assets/images/week8-sketch-01.jpg" alt="Week 8 sketch 1: banner variations and glanceable chip" style="max-width:48%;height:auto;margin-right:1%;">
<img src="../assets/images/week8-sketch-02.jpg" alt="Week 8 sketch 2: expanded banner with single action" style="max-width:48%;height:auto;">
<br>
<img src="../assets/images/week8-sketch-03.jpg" alt="Week 8 sketch 3: dog profile factors and water timer" style="max-width:48%;height:auto;margin-right:1%;">
<img src="../assets/images/week8-flow.jpg" alt="Week 8 user flow: inputs → risk rule → three banner states" style="max-width:48%;height:auto;">

#### What this is
Fast paper sketches exploring the glanceable chip, the expanded banner with one clear action, and how optional dog factors might adjust thresholds. A simple flow maps inputs → risk rule → three states.

#### Why I did it
Sketching let me try multiple layouts quickly before committing to code and verify the “glanceable UI” direction from Week 7.

#### What it means
I chose a chip + expandable banner pattern because it suits running (low reading time), supports progressive disclosure, and keeps cognitive load low.

### Glanceable chip — what it is and why I’m using it

#### What it is
A small, always-visible UI element that compresses state into 2–3 words and a color (e.g., green “Good to run”). Tapping it expands into a short banner with the reason and a single action.

#### Why this pattern for running
- Minimizes reading while moving; works at arm’s length.
- Keeps attention on the environment, not the screen.
- Works on both phone and potential device outputs (LED/haptic).

#### Design rules I’m following
- Content: 2–3 words max; no numbers unless essential.
- Color + label always paired (color-blind safe); contrast ≥ 4.5:1.
- Touch target ≥ 44px height; safe margins around edges.
- One job: show state; tap to expand for the “why” + one action.
- Idle battery use: no constant animations; only change on state updates.

#### How it maps to my three states
- Good to run → chip label “Good to run” (green).  
- Shorten route → label “Shorten route” (amber).  
- Slow + water break → label “Slow + water break” (red + optional haptic).

#### Accessibility and clarity
- Color is never the only signal (text label + icon optional).
- Plain, verb-first language; no jargon.  
- Announces state changes with a brief haptic (configurable) and keeps an “approximate” badge when data is from the nearest station.

#### Trade-offs and mitigations
- Chip is terse by design → mitigation: expand to banner for the reason and single recommended action.  
- Possible over-attention to color → mitigation: bold labels, icon, and consistent wording.

#### Live example (static demo)

<!-- Glanceable chip demo (pure HTML/CSS; no scripts) -->
<style>
  .chip-demo{margin:12px 0 20px;font-family:system-ui,-apple-system,"Segoe UI",Roboto,Arial,sans-serif}
  .chip-row{display:flex;flex-wrap:wrap;gap:12px;align-items:center}
  .chip{display:inline-flex;align-items:center;gap:.5rem;padding:.4rem .8rem;border-radius:999px;
        font-weight:600;font-size:.95rem;line-height:1;border:1px solid transparent}
  .chip--good{background:#e6f6ea;color:#145a32;border-color:#bde5c8}
  .chip--med{background:#fff7e6;color:#7a4a00;border-color:#ffe0a3}
  .chip--high{background:#fdeaea;color:#7a1212;border-color:#f3b2b2}

  .banner{margin-top:10px;padding:12px 14px;border-radius:12px;border:1px solid #e5e7eb;background:#fff}
  .banner--good{border-color:#bde5c8}
  .banner--med{border-color:#ffe0a3}
  .banner--high{border-color:#f3b2b2}
  .banner h4{margin:0 0 .25rem 0;font-size:1rem}
  .banner p{margin:.25rem 0}
  .badge{font-size:.75rem;font-weight:600;padding:.15rem .45rem;border-radius:6px;background:#f3f4f6;color:#111827}

  details.chip-details{margin-top:8px}
  details > summary{list-style:none;cursor:pointer}
  details > summary::-webkit-details-marker{display:none}
  summary .chip{box-shadow:0 1px 2px rgba(0,0,0,.06)}

  @media (max-width:640px){
    .chip-row{gap:8px}
    .chip{font-size:.9rem}
  }
</style>

<div class="chip-demo" role="region" aria-label="Glanceable chip demo">
  <!-- The three states (static samples) -->
  <div class="chip-row" aria-hidden="true">
    <span class="chip chip--good" title="Good to run">✅ Good to run</span>
    <span class="chip chip--med"  title="Shorten route">⚠️ Shorten route</span>
    <span class="chip chip--high" title="Slow + water break">⛔ Slow + water break</span>
  </div>

  <!-- Expandable example using details/summary -->
  <details class="chip-details">
    <summary aria-label="Expand example banner">
      <span class="chip chip--med">⚠️ Shorten route</span>
    </summary>
    <div class="banner banner--med">
      <h4>Why</h4>
      <p>Heat index elevated and AQI moderate. Data is <span class="badge">approximate</span> (nearest station).</p>
      <h4>Action</h4>
      <p>Choose a shorter loop and plan a water stop. Tap <strong>Refresh</strong> to re-check in 5 minutes.</p>
    </div>
  </details>
</div>

---

### Prototype screenshots
<img src="../assets/images/week8-desktop.png" alt="Prototype desktop screen with status banner" style="max-width:48%;height:auto;margin-right:1%;">
<img src="../assets/images/week8-mobile.png" alt="Prototype mobile screen with status banner" style="max-width:48%;height:auto;">

#### What this is
First interactive prototype showing the three states: Good to run, Shorten route, Slow + water break. Includes a manual Refresh and an “approximate” label to signal nearest-station data.

#### Why I did it
To test whether the banner is legible at a glance and whether people understand the one-line advice without needing a dashboard.

#### What it means
The prototype operationalises Week 7 decisions: real-time prompts (not logs), privacy-first (no trails/IDs), and simple, unambiguous actions.

---

### Risk rule v1 (draft)

inputs:

temperature (°C), relative humidity (%)

AQI PM2.5 (nearest station)

optional: dog factors (size/age/coat) as a simple multiplier

derived:

heat_index_c = Steadman HI from temp + RH

decision (three states):

if AQI >= 150 OR heat_index_c >= 33 → Slow + water break

else if AQI >= 100 OR heat_index_c >= 30 → Shorten route

else → Good to run

banner copy:

Good to run — Conditions look safe. Keep an easy pace; watch your dog’s breathing.

Shorten route — Heat/AQI elevated. Pick a shorter loop; plan a water stop.

Slow + water break — High heat/AQI. Slow down now, move to shade, give water.

yaml
Copy code

#### What this is
A first pass at turning weather and AQI into three clear states and one recommended action.

#### Why I did it
To make the system testable now. Thresholds are conservative and will be tuned after trials.

#### What it means
This shows how Week 7 research (AQI categories, heat guidance) becomes a concrete rule the UI can act on. It also supports the “human + dog” framing via the optional dog factor.

---

### Known issues / Workarounds
- iOS permission prompts are inconsistent → provide a manual **Refresh** button.  
- AQI locality mismatch → fall back to nearest station and show **approximate**.  
- Battery: avoid continuous GPS; check on demand or when conditions change.

---

### Testing

#### Plan
Devices: list phones/browsers i use  
Scenarios: hot midday, cool evening, windy day  
Routes/locations: where you walked/ran  
Method: short sessions; note when states switch; use Refresh; record any confusion

#### Why I did it
I needed evidence that the banner is seen and understood in motion, and whether copy or thresholds need changes.

#### What it means
This is proof of responsive behaviour and informs the exact copy/threshold changes for Week 9.

---

### Findings (short)
- Banner readability: what was easy/hard to see  
- Thresholds: too strict or too lax  
- Performance: geolocation/API delays  
- Privacy/UI: did “approximate” label make sense; any concern about data

---

### Changes for v2 (Week 9)
- Thresholds: list specific numbers/rules to adjust  
- Copy: shorter verbs; remove hedging  
- UI: stronger contrast; haptic nudge on “Slow + water break”  
- Tech: debounce Refresh; event-based checks; cache last reading

---

### Reflection
Early alerts are readable and the one-action banner keeps decisions simple during a run. The prototype also demonstrates my Week 7 stance: real-time micro-advice over dashboards, privacy by design (coarse, ephemeral data) and combined human + dog safety. Next, I’ll tune thresholds from testing, tighten the copy and polish the UI for the Week 9 wrap-up.
