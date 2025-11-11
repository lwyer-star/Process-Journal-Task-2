const STATES = {
  good: {
    chip: "Good to run",
    color: "#1f8f4e",
    why: "Conditions safe.",
    action: "Keep an easy pace.",
    approx: false
  },
  caution: {
    chip: "Shorten route",
    color: "#c68a13",
    why: "Heat/AQI up.",
    action: "Pick a shorter loop; plan water.",
    approx: true
  },
  alert: {
    chip: "Slow + water",
    color: "#c93030",
    why: "High heat/AQI.",
    action: "Slow down, shade, give water.",
    approx: true
  }
};

const chipBtn = document.getElementById("chipBtn");
const chipLabel = document.getElementById("chipLabel");
const dot = document.querySelector(".dot");
const approx = document.getElementById("approxBadge");
const whyLine = document.getElementById("whyLine");
const actionLine = document.getElementById("actionLine");
const refreshBtn = document.getElementById("refreshBtn");
const expander = document.getElementById("expander");

let stateKey = "good";

function render() {
  const s = STATES[stateKey];
  chipLabel.textContent = s.chip;
  dot.style.backgroundColor = s.color;
  approx.hidden = !s.approx;
  whyLine.textContent = s.why;
  actionLine.textContent = s.action;
}

chipBtn.addEventListener("click", () => {
  const open = expander.open;
  expander.open = !open;
  chipBtn.setAttribute("aria-expanded", String(!open));
});

refreshBtn.addEventListener("click", () => {
  stateKey = stateKey === "good" ? "caution" : stateKey === "caution" ? "alert" : "good";
  render();
});

render();
