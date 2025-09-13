---
layout: default
title: Week 7 — Related works & research
---

**Navigation:** [Home](/Process-Journal-Task-2/) · [Week 6](./week6) · [Week 7](./week7) · [Week 8](./week8) · [Week 9](./week9)

# Week 7 — Related works & research

## Landscape scan
1. **Crowd heatmaps in running apps** — pattern for time/zone-based density; informs my anonymous “busy time” idea.
![Strava heatmap](../assets/images/week7-heatmap.jpg)  
*Strava Global Heatmap showing running and cycling activity across Brisbane and surrounding areas.*
The Strava Global Heatmap visualises where users run and cycle most often. Each line on the map represents GPS traces from thousands of workouts uploaded by Strava users. Brighter and denser blue lines indicate **heavily used routes**, while fainter lines show **less popular paths**. This kind of crowd-sourced data helps identify safe, well-travelled areas or highlight quieter routes depending on a runner’s needs.  

This inspired my idea of giving runners a “busy time” or “quiet path” alert, since density information can shape decisions about when and where to run. However, Strava’s 2018 heatmap also revealed sensitive military base locations because even anonymised data can still expose private patterns when zoomed in (Hern, 2018). This highlighted for me the importance of only using **coarse, aggregated data** in my project, never precise trails or individual locations.

Apps like Strava show where and when people run most often. This pattern inspired my idea of giving “busy time” alerts, but it also raised concerns about privacy — previous heatmaps accidentally revealed sensitive locations.    
2. **Pet wearables (general)** — mostly health logging; my pivot is **shared, in-moment guidance**.
These devices track activity, rest, and sometimes location for dogs. They mostly provide long-term stats, but don’t offer immediate safety advice. This gap is important: my concept focuses on *real-time nudges* during a run.   
3. **Weather/AQI risk guidance** — informs thresholds and copy for alerts.
Government AQI dashboards and running apps sometimes give “unhealthy air” warnings. I realised I could adapt this into a simple 3-tier banner system for heat, humidity, and air quality.  

## What I’m taking forward
- **Interaction patterns:** glanceable banners, progressive disclosure.  
- **Tech:** Web Geolocation; Weather/AQI API; basic risk scoring.  
- **Human/cultural:** accessibility (clear language), privacy (no trails/IDs), animal welfare.

## References
- Strava (2018). *Strava Global Heatmap Privacy Statement*. https://blog.strava.com  
- Whistle (2023). *Whistle Health Device*. https://www.whistle.com  
- Australian Government (2024). *Air Quality Index Categories*. https://www.environment.gov.au  

## Reflection
The strongest leverage is timely, clear micro-advice rather than dashboards. Privacy needs to be strict to avoid creepiness; aggregation + k-anonymity feels right. This week helped me validate that my idea has a gap compared to existing products. While other tools log data or provide static dashboards, there is little real-time advice that responds to *both* human and animal needs. I also became more aware of privacy risks, so I decided to prioritise aggregation and transparency. This learning will directly inform the rules and prototype I start in Week 8.
