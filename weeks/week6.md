---
layout: default
title: Week 6 — Ideation & framing
---

**Navigation:** [Home](/Process-Journal-Task-2/) · [Week 6](./week6) · [Week 7](./week7) · [Week 8](./week8) · [Week 9](./week9)

# Week 6 — Ideation & framing

## Idea Card
**Adaptive Run Companion – Liam W**  
Most likely a solo project.  
**Form** – Mobile app (possible wearable extension)  
**Configuration** – Human + Nonhuman (shared run)  
**Input** – GPS, weather/AQI APIs, pace/movement  
**Output** – Advisory feedback  

This is a responsive running companion for people and their dogs. It adapts runs to heat/humidity/AQI with suggestions to slow, shorten, or take water. If pace is steady, it encourages continuing. Future: anonymous “busy time” alerts with strict privacy.

---

## Provocation & Intent
- **Chosen provocation:** *Beyond Human*  
- **Problem/context:** Running with dogs can be unsafe in heat, humidity, or poor air quality; owners lack simple, real-time guidance.  
- **Audience:** Recreational runners who take their dog on daily runs.  
- **Design intent:** Provide adaptive, context-aware advice that keeps both human and dog safer and more comfortable during runs.

## Concept Directions
1. **Direction A — Adaptive Run Companion (mobile web):** GPS + weather/AQI → adjust pacing; suggest water/shade breaks.  
2. **Direction B — Community-aware alerts:** anonymous, privacy-safe “busy/heat” pings aggregated by area/time to recommend quieter/cooler windows.  
3. **Direction C — Wearable harness add-on (later):** optional harness sensor to refine fatigue/overheating cues.  

*Selected:* **A** for Week 9 demo; **B** as a light extension.

## Interaction loop
**Sense → Decide → Act → Reflect**  
- **Inputs:** GPS, weather/AQI APIs, simple pace trend  
- **Rules:** if `heatIndex ≥ threshold` → suggest slow/shorten/water  
- **Outputs:** on-screen banner; optional haptic (device)  
- **Feedback:** user taps “took water/shortened run” to improve advice

## Notes & Decisions
- Start as **mobile web** (Geolocation + public weather API).
- Privacy-by-design for any community pings (opt-in, geohash rounding, k-anonymity, no history).
- **Feasibility:** live weather-driven alerts + mock heatmap for Week 9.

## Reflection
This shifts me away from “medical pet tracking” into a shared, situational experience. It foregrounds human factors (safety, comfort, timing) and applies design principles (clarity, timely feedback). Next I’ll validate thresholds for heat/AQI and the wording of alerts.
