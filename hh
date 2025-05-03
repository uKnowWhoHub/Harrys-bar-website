<!DOCTYPE html><html lang="en">
<head>
  <meta charset="UTF-8">
  <title>Bar Tab Tracker</title>
  <style>
    body {
      background-color: #121212;
      color: white;
      font-family: sans-serif;
      margin: 0;
      padding: 20px;
    }
    .hidden {
      display: none;
    }
    button {
      background-color: #1f1f1f;
      color: white;
      border: 1px solid #444;
      padding: 12px;
      margin: 6px;
      border-radius: 8px;
      cursor: pointer;
      font-size: 16px;
    }
    input, select {
      padding: 12px;
      margin: 6px;
      border-radius: 6px;
      border: none;
      font-size: 16px;
    }
    .item-category {
      margin-top: 20px;
    }
    .item-category h3 {
      margin-bottom: 10px;
    }
    .item-button {
      display: inline-block;
      margin: 4px;
    }
    pre {
      background: #1e1e1e;
      padding: 10px;
      border-radius: 6px;
      white-space: pre-wrap;
    }
  </style>
</head>
<body>
  <h1>Bar Tab Tracker</h1>
  <div id="home">
    <button onclick="showNewTab()">New Tab</button>
    <button onclick="showExistingTab()">Existing Tab</button>
  </div>  <div id="new-tab" class="hidden">
    <input id="new-name" placeholder="Enter name">
    <button onclick="startTab()">Start Tab</button>
    <button onclick="backToHome()">Back</button>
  </div>  <div id="select-tab" class="hidden">
    <select id="tab-list"></select>
    <button onclick="loadTab()">Load</button>
    <button onclick="backToHome()">Back</button>
  </div>  <div id="tab-view" class="hidden">
    <h2 id="tab-name"></h2><div class="item-category">
  <h3>Tap Drinks</h3>
  <div id="tap-items"></div>
</div>

<div class="item-category">
  <h3>Spirits / Mixers</h3>
  <div id="spirit-items"></div>
</div>

<div class="item-category">
  <h3>Shots</h3>
  <div id="shot-items"></div>
</div>

<div class="item-category">
  <h3>Snacks</h3>
  <div id="snack-items"></div>
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

    function showNewTab() {
      document.getElementById("home").classList.add("hidden");
      document.getElementById("new-tab").classList.remove("hidden");
    }

    function showExistingTab() {
      const select = document.getElementById("tab-list");
      select.innerHTML = "";
      Object.keys(localStorage).forEach(name => {
        const option = document.createElement("option");
        option.value = name;
        option.textContent = name;
        select.appendChild(option);
      });
      document.getElementById("home").classList.add("hidden");
      document.getElementById("select-tab").classList.remove("hidden");
    }

    function startTab() {
      const name = document.getElementById("new-name").value;
      if (!name) return;
      currentName = name;
      currentTab = {};
      showTabView();
    }

    function loadTab() {
      currentName = document.getElementById("tab-list").value;
      currentTab = JSON.parse(localStorage.getItem(currentName)) || {};
      showTabView();
    }

    function showTabView() {
      document.getElementById("new-tab").classList.add("hidden");
      document.getElementById("select-tab").classList.add("hidden");
      document.getElementById("tab-view").classList.remove("hidden");
      document.getElementById("tab-name").textContent = currentName;
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
        btn.className = "item-button";
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
      alert("Tab saved");
    }

    function backToHome() {
      document.querySelectorAll("#home, #new-tab, #select-tab, #tab-view")
        .forEach(el => el.classList.add("hidden"));
      document.getElementById("home").classList.remove("hidden");
    }
  </script></body>
</html>
