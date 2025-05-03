<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8" />
  <meta name="viewport" content="width=device-width, initial-scale=1.0"/>
  <title>Bar Tab Tracker</title>
  <style>
    :root {
      --bg: #0e0e0e;
      --card: #1a1a1a;
      --accent: #4a90e2;
      --text: #f0f0f0;
      --highlight: #222;
    }
    body {
      margin: 0;
      padding: 1rem;
      background: var(--bg);
      color: var(--text);
      font-family: "Segoe UI", sans-serif;
      display: flex;
      flex-direction: column;
      min-height: 100vh;
    }
    h2, h3 {
      margin-top: 1.5rem;
    }
    button {
      background: var(--accent);
      color: white;
      border: none;
      padding: 12px 18px;
      margin: 6px;
      border-radius: 8px;
      font-size: 16px;
      cursor: pointer;
      transition: all 0.2s ease;
    }
    button:hover {
      opacity: 0.9;
      transform: scale(1.02);
    }
    .grid {
      display: grid;
      grid-template-columns: repeat(auto-fit, minmax(120px, 1fr));
      gap: 10px;
    }
    .card {
      background: var(--card);
      padding: 1rem;
      border-radius: 10px;
      box-shadow: 0 2px 6px rgba(0,0,0,0.5);
      animation: fadeIn 0.3s ease forwards;
    }
    input, select {
      padding: 10px;
      font-size: 16px;
      width: 100%;
      margin-bottom: 10px;
      border-radius: 6px;
      border: none;
      background: var(--highlight);
      color: var(--text);
    }
    pre {
      white-space: pre-wrap;
      background: var(--highlight);
      padding: 12px;
      border-radius: 6px;
    }
    .hidden {
      display: none;
    }
    .fade {
      animation: fadeIn 0.4s ease;
    }
    @keyframes fadeIn {
      from { opacity: 0; transform: translateY(10px); }
      to { opacity: 1; transform: translateY(0); }
    }
  </style>
</head>
<body>
  <div class="card fade" id="app">
    <h2>Modern Bar Tab Tracker</h2>

    <div id="employeeSelect">
      <label>Select Your Name</label>
      <select onchange="selectEmployee(this.value)">
        <option value="">-- Choose --</option>
        <option>Tina</option>
        <option>Cameron</option>
        <option>Chloe</option>
        <option>Danielle</option>
        <option>Lily</option>
      </select>
    </div>

    <div class="hidden" id="tabInterface">
      <h3>Tabs for <span id="employeeName"></span></h3>
      <button onclick="startNewTab()">+ New Tab</button>
      <div id="tabButtons" class="grid"></div>

      <h3 class="hidden" id="currentTabTitle"></h3>
      <div class="hidden" id="itemGrid" class="grid"></div>
      <pre id="tabDisplay"></pre>

      <div class="hidden" id="tabActions">
        <button onclick="saveTab()">Save</button>
        <button onclick="showSummary()">Pay</button>
        <button onclick="resetUI()">Back</button>
      </div>
    </div>
  </div>

  <script>
    const items = [
      "Carling", "Guinness", "Vodka + Coke", "Double Vodka",
      "Tequila Rose", "Sambuca", "Jäger", "Crisps", "Bacon Fries"
    ];
    const prices = {
      "Carling": 3.2, "Guinness": 3.5, "Vodka + Coke": 4.2,
      "Double Vodka": 5.0, "Tequila Rose": 2.0, "Sambuca": 2.0,
      "Jäger": 2.0, "Crisps": 1.0, "Bacon Fries": 1.0
    };

    let employee = "";
    let tabs = {};
    let currentTab = null;

    function selectEmployee(name) {
      if (!name) return;
      employee = name;
      document.getElementById("employeeName").textContent = name;
      document.getElementById("employeeSelect").classList.add("hidden");
      document.getElementById("tabInterface").classList.remove("hidden");
      refreshTabButtons();
    }

    function refreshTabButtons() {
      const container = document.getElementById("tabButtons");
      container.innerHTML = "";
      Object.keys(tabs).forEach(name => {
        const btn = document.createElement("button");
        btn.textContent = name;
        btn.onclick = () => loadTab(name);
        container.appendChild(btn);
      });
    }

    function startNewTab() {
      const name = prompt("Enter tab name");
      if (!name || tabs[name]) return;
      tabs[name] = {};
      loadTab(name);
    }

    function loadTab(name) {
      currentTab = name;
      document.getElementById("currentTabTitle").classList.remove("hidden");
      document.getElementById("currentTabTitle").textContent = `Tab: ${name}`;
      renderItems();
      updateDisplay();
      document.getElementById("tabActions").classList.remove("hidden");
    }

    function renderItems() {
      const grid = document.getElementById("itemGrid");
      grid.classList.remove("hidden");
      grid.innerHTML = "";
      items.forEach(item => {
        const btn = document.createElement("button");
        btn.textContent = item;
        btn.onclick = () => addItem(item);
        grid.appendChild(btn);
      });
    }

    function addItem(item) {
      const tab = tabs[currentTab];
      tab[item] = (tab[item] || 0) + 1;
      updateDisplay();
    }

    function updateDisplay() {
      const tab = tabs[currentTab];
      let text = "";
      for (let item in tab) {
        text += `${item}: ${tab[item]}\n`;
      }
      document.getElementById("tabDisplay").textContent = text;
    }

    function saveTab() {
      alert("Tab Saved!");
      resetUI();
    }

    function showSummary() {
      const tab = tabs[currentTab];
      let total = 0, summary = `Summary for ${currentTab} by ${employee}:\n\n`;
      for (let item in tab) {
        const count = tab[item];
        const cost = (prices[item] || 0) * count;
        summary += `${item} x${count} = £${cost.toFixed(2)}\n`;
        total += cost;
      }
      summary += `\nTotal: £${total.toFixed(2)}`;
      alert(summary);
      resetUI();
    }

    function resetUI() {
      document.getElementById("employeeSelect").classList.remove("hidden");
      document.getElementById("tabInterface").classList.add("hidden");
      document.getElementById("currentTabTitle").classList.add("hidden");
      document.getElementById("itemGrid").classList.add("hidden");
      document.getElementById("tabActions").classList.add("hidden");
    }
  </script>
</body>
</html>
