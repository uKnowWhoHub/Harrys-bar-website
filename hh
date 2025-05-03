Here’s the complete HTML code for your dark-mode bar tab app. You can copy this into a .html file and open it in a mobile browser, or wrap it in a WebView for Android later:

<!DOCTYPE html>
<html lang="en">
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
      background-color: #1e1e1e;
      color: white;
      border: 1px solid #333;
      padding: 10px;
      margin: 5px;
      border-radius: 5px;
      cursor: pointer;
    }
    input, select {
      padding: 10px;
      margin: 5px;
      border-radius: 5px;
      border: none;
    }
    .item-button {
      display: inline-block;
      margin: 5px;
    }
    pre {
      background: #1e1e1e;
      padding: 10px;
      border-radius: 5px;
      white-space: pre-wrap;
    }
  </style>
</head>
<body>
  <h1>Bar Tab Tracker</h1>
  <div id="home">
    <button onclick="showNewTab()">New Tab</button>
    <button onclick="showExistingTab()">Existing Tab</button>
  </div>

  <div id="new-tab" class="hidden">
    <input id="new-name" placeholder="Enter name">
    <button onclick="startTab()">Start Tab</button>
    <button onclick="backToHome()">Back</button>
  </div>

  <div id="select-tab" class="hidden">
    <select id="tab-list"></select>
    <button onclick="loadTab()">Load</button>
    <button onclick="backToHome()">Back</button>
  </div>

  <div id="tab-view" class="hidden">
    <h2 id="tab-name"></h2>
    <div id="items"></div>
    <input id="custom-item" placeholder="Custom item">
    <button onclick="addCustomItem()">Add Custom</button>
    <div>
      <h3>Tab Total:</h3>
      <pre id="tab-content"></pre>
    </div>
    <button onclick="saveTab()">Save</button>
    <button onclick="backToHome()">Back</button>
  </div>

  <script>
    const itemList = [
      "Bottle wine", "Sol", "Corona (Pint)", "Desperados", "Carling",
      "Guinness", "Fosters", "Strongbow", "Madri", "John Smiths",
      "Cruzcampo", "Smiths", "VK", "Hooch", "Monster",
      "Tequila Rose", "Fireball", "Sambuca", "Jäger", "Baby Guinness",
      "Shanky's Whip", "Midori", "Jamesons", "Kraken", "Smirnoff",
      "Vodka + Coke", "Vodka + Lemon", "Double Vodka",
      "Crisps", "Bacon Fries", "Pork Cracklings"
    ];

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
      updateItems();
      updateTabContent();
    }

    function updateItems() {
      const container = document.getElementById("items");
      container.innerHTML = "";
      itemList.forEach(item => {
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
      const item = document.getElementById("custom-item").value;
      if (item) {
        itemList.push(item);
        document.getElementById("custom-item").value = "";
        updateItems();
      }
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
  </script>
</body>
</html>

Let me know if you’d like:

A "Paid" checkbox or button for each person

Total value calculation based on item prices

Help wrapping this as an Android app with a guide or APK


Want the Android wrapper next?

