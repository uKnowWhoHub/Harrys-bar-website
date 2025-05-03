<!DOCTYPE html><html lang="en">
<head>
  <meta charset="UTF-8">
  <title>Bar Tab Tracker</title>
  <style>
    body {
      background-color: #000033;
      color: white;
      font-family: sans-serif;
      margin: 0;
      padding: 20px;
    }
    .hidden {
      display: none;
    }
    button {
      background-color: #1f1fbf;
      color: white;
      border: 2px solid #444;
      padding: 16px;
      margin: 8px;
      border-radius: 8px;
      cursor: pointer;
      font-size: 18px;
      width: 140px;
    }
    input, select {
      padding: 12px;
      margin: 6px;
      border-radius: 6px;
      border: none;
      font-size: 16px;
    }
    .grid {
      display: flex;
      flex-wrap: wrap;
      gap: 10px;
    }
    .item-category {
      margin-top: 20px;
    }
    .item-category h3 {
      margin-bottom: 10px;
    }
    .item-button {
      display: inline-block;
    }
    pre {
      background: #1e1e3f;
      padding: 10px;
      border-radius: 6px;
      white-space: pre-wrap;
    }
    .till-btn {
      background-color: #0044cc;
      width: 160px;
      font-weight: bold;
    }
    #save-popup {
      position: fixed;
      top: 20px;
      left: 50%;
      transform: translateX(-50%);
      background: green;
      color: white;
      padding: 10px 20px;
      border-radius: 5px;
      display: none;
      font-size: 20px;
    }
  </style>
</head>
<body>
  <div id="save-popup">Tab Saved!</div>  <div id="employee-select">
    <h2>Select Employee</h2>
    <div class="grid">
      <button class="till-btn" onclick="selectEmployee('Tina')">Tina</button>
      <button class="till-btn" onclick="selectEmployee('Cameron')">Cameron</button>
      <button class="till-btn" onclick="selectEmployee('Chloe')">Chloe</button>
      <button class="till-btn" onclick="selectEmployee('Danielle')">Danielle</button>
      <button class="till-btn" onclick="selectEmployee('Lily')">Lily</button>
    </div>
  </div>  <div id="home" class="hidden">
    <h2>Tabs</h2>
    <div id="tab-buttons" class="grid"></div>
    <button onclick="showNewTab()">New Tab</button>
  </div>  <div id="new-tab" class="hidden">
    <input id="new-name" placeholder="Enter name">
    <button onclick="startTab()">Start Tab</button>
    <button onclick="backToHome()">Back</button>
  </div>  <div id="tab-view" class="hidden">
    <h2 id="tab-name"></h2><div class="item-category">
  <h3>Draught Beer</h3>
  <div id="tap-items" class="grid"></div>
</div>

<div class="item-category">
  <h3>Spirits / Mixers</h3>
  <div id="spirit-items" class="grid"></div>
</div>

<div class="item-category">
  <h3>Shots</h3>
  <div id="shot-items" class="grid"></div>
</div>

<div class="item-category">
  <h3>Snacks</h3>
  <div id="snack-items" class="grid"></div>
</div>

<input id="custom-item" placeholder="Custom item">
<button onclick="addCustomItem()">Add Custom</button>

<div>
  <h3>Tab Total:</h3>
  <pre id="tab-content"></pre>
</div>
<button onclick="saveTab()">Save</button>
<button onclick="backToHome()">Back</button>

  </div>  <script>
    const taps = ["Carling", "Fosters", "Strongbow", "Guinness", "Madri", "John Smiths", "Cruzcampo", "Smiths"];
    const spirits = ["Vodka + Coke", "Vodka + Lemon", "Double Vodka", "Kraken + Coke", "Smirnoff", "Jamesons"];
    const shots = ["Tequila Rose", "Fireball", "Sambuca", "Jäger", "Baby Guinness", "Shanky's Whip", "Midori"];
    const snacks = ["Crisps", "Bacon Fries", "Pork Cracklings"];

    let currentName = "";
    let currentTab = {};
    let currentEmployee = "";

    function selectEmployee(name) {
      currentEmployee = name;
      document.getElementById("employee-select").classList.add("hidden");
      document.getElementById("home").classList.remove("hidden");
      refreshTabButtons();
    }

    function refreshTabButtons() {
      const container = document.getElementById("tab-buttons");
      container.innerHTML = "";
      Object.keys(localStorage).forEach(name => {
        const btn = document.createElement("button");
        btn.className = "till-btn";
        btn.textContent = name;
        btn.onclick = () => loadTab(name);
        container.appendChild(btn);
      });
    }

    function showNewTab() {
      document.getElementById("home").classList.add("hidden");
      document.getElementById("new-tab").classList.remove("hidden");
    }

    function startTab() {
      const name = document.getElementById("new-name").value.trim();
      if (!name) return;
      currentName = name;
      currentTab = {};
      showTabView();
    }

    function loadTab(name) {
      currentName = name;
      currentTab = JSON.parse(localStorage.getItem(currentName)) || {};
      showTabView();
    }

    function showTabView() {
      document.getElementById("home").classList.add("hidden");
      document.getElementById("new-tab").classList.add("hidden");
      document.getElementById("tab-view").classList.remove("hidden");
      document.getElementById("tab-name").textContent = `${currentName} - ${currentEmployee}`;
      renderItems();
      updateTabContent();
    }

    function renderItems() {
      renderCategory("tap-items", taps);
      renderCategory("spirit-items", spirits);
      renderCategory("shot-items", shots);
      renderCategory("snack-items", snacks);
    }

    function renderCategory(containerId, items) {
      const container = document.getElementById(containerId);
      container.innerHTML = "";
      items.forEach(item => {
        const btn = document.createElement("button");
        btn.className = "item-button till-btn";
        btn.textContent = item;
        btn.onclick = () => addItem(item);
        container.appendChild(btn);
      });
    }

    function addItem(item) {
      currentTab[item] = (currentTab[item] || 0) + 1;
      updateTabContent();
    }

    function addCustomItem() {
      const item = document.getElementById("custom-item").value.trim();
      if (!item) return;
      if (!currentTab[item]) currentTab[item] = 0;
      currentTab[item] += 1;
      document.getElementById("custom-item").value = "";
      updateTabContent();
    }

    function updateTabContent() {
      const output = Object.entries(currentTab)
        .map(([item, count]) => `${item}: ${count}`)
        .join("\n");
      document.getElementById("tab-content").textContent = output;
    }

    function saveTab() {
      localStorage.setItem(currentName, JSON.stringify(currentTab));
      const popup = document.getElementById("save-popup");
      popup.style.display = "block";
      setTimeout(() => {
        popup.style.display = "none";
        backToHome();
      }, 2000);
    }

    function backToHome() {
      document.querySelectorAll("#home, #new-tab, #tab-view")
        .forEach(el => el.classList.add("hidden"));
      document.getElementById("home").classList.remove("hidden");
      refreshTabButtons();
    }
  </script></body>
</html>
