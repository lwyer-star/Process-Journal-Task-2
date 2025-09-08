---
layout: default
title: Week 8 — Prototyping & tests
---

**Navigation:** [Home](/Process-Journal-Task-2/) · [Week 6](./week6) · [Week 7](./week7) · [Week 8](./week8) · [Week 9](./week9)

# Week 8 — Prototyping & tests

## Prototype screenshots
![Desktop mock](../assets/images/week8-desktop.png)
![Mobile mock](../assets/images/week8-mobile.png)

## Alerts (risk rule – draft)
risk = 0.4heatIndex + 0.25aqiScore + 0.25crowdScore + 0.10paceDrift
if risk >= HIGH -> "Slow + water break"
elif risk >= MED -> "Shorten route"
else -> "Good to run"

## Known issues / Workarounds
- iOS permission prompts inconsistent → provide manual **Refresh** button.
- AQI locality mismatch → fall back to nearest station + show **approximate**.

## Testing
- **Devices:** (list what you tried)
- **Scenarios:** hot midday / evening cool / windy day
- **Findings:** brief bullets

## Reflection
Early alerts are readable; I’ll fine-tune thresholds and the copy next.

