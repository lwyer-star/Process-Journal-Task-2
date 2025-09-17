(() => {
  const STATES = [
    {name: "Normal",  colorVar: "--normal",  meta: "All readings within expected range"},
    {name: "Caution", colorVar: "--caution", meta: "Elevated values detected — monitor closely"},
    {name: "Alert",   colorVar: "--alert",   meta: "Threshold exceeded — take action"},
  ];

  const chip  = document.getElementById("statusChip");
  const label = document.getElementById("statusLabel");
  const dot   = chip.querySelector(".dot");
  const meta  = document.getElementById("statusMeta");

  let i = 0;
  let paused = false;
  let timer = null;

  function applyState(s){
    label.textContent = s.name;
    dot.style.backgroundColor = getComputedStyle(document.documentElement)
      .getPropertyValue(s.colorVar).trim();
    meta.textContent = s.meta;
  }

  function tick(){
    if (paused) return;
    i = (i + 1) % STATES.length;
    applyState(STATES[i]);
  }

  function start(){
    if (timer) clearInterval(timer);
    timer = setInterval(tick, 2000);
  }

  // init
  applyState(STATES[i]);
  start();

  // Click to pause/resume for demo control
  chip.addEventListener("click", () => {
    paused = !paused;
    chip.title = paused ? "Paused — click to resume" : "Click to pause";
    // small visual feedback
    chip.style.outline = paused ? "2px solid rgba(255,255,255,0.3)" : "none";
  });

  // Clean up if needed
  window.addEventListener("beforeunload", () => timer && clearInterval(timer));
})();
