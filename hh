Here is the full updated HTML for your till-style bar tab tracker with employee selection, simplified contribution tracking, pay summary, and categorized drink buttons:

<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <title>Bar Tab Tracker</title>
  <style>
    body {
      background-color: #d9ecff;
      color: black;
      font-family: sans-serif;
      margin: 0;
      padding: 10px;
    }
    .hidden { display: none; }
    button {
      font-size: 14px;
      font-weight: bold;
      padding: 10px;
      margin: 4px;
      width: 100px;
      height: 60px;
      border: none;
      border-radius: 4px;
      color: white;
    }
    .yellow { background-color: #ffdc00; color: black; }
    .pink { background-color: #ff69b4; }
    .blue { background-color: #0074d9; }
    .red { background-color: #ff4136; }
    .green { background-color: #2ecc40; }
    .orange { background-color: #ff851b; }
    .purple { background-color: #b10dc9; }
    .gray { background-color: #aaaaaa; color: black; }
    .grid { display: flex; flex-wrap: wrap; gap: 6px; }
    .topbar { display: flex; justify-content: space-between; margin-bottom: 10px; }
    pre { white-space: pre-wrap; background: #f0f0f0; padding: 10px; border-radius: 4px; }
    .popup {
      position: fixed;
      top: 10px;
      left: 50%;
      transform: translateX(-50%);
      background: green;
      color: white;
      padding: 8px 16px;
      border-radius: 5px;
      display: none;
      font-size: 16px;
      z-index: 999;
    }
    #pay-summary {
      position: fixed;
      top: 50%;
      left: 50%;
      transform: translate(-50%, -50%);
      background: white;
      color: black;
      padding: 20px;
      border-radius: 8px;
      width: 90%;
      max-width: 400px;
      z-index: 1000;
      box-shadow: 0 0 10px rgba(0,0,0,0.3);
    }
  </style>
</head>
<body>
<div class="popup" id="save-popup">Tab Saved!</div>
<div id="pay-summary" class="hidden">
  <h3>Confirm Payment</h3>
  <div id="summary-content"></div>
  <button class="green" onclick="confirmPayment()">Confirm</button>
  <button class="red" onclick="cancelPayment()">Cancel</button>
</div>

<div id="employee-select">
  <h2>Select Employee</h2>
  <div class="grid">
    <button class="blue" onclick="selectEmployee('Tina')">Tina</button>
    <button class="blue" onclick="selectEmployee('Cameron')">Cameron</button>
    <button class="blue" onclick="selectEmployee('Chloe')">Chloe</button>
    <button class="blue" onclick="selectEmployee('Danielle')">Danielle</button>
    <button class="blue" onclick="selectEmployee('Lily')">Lily</button>
  </div>
</div>

<div id="home" class="hidden">
  <h2>Tabs</h2>
  <div class="grid" id="tab-buttons"></div>
  <button class="green" onclick="showNewTab()">New Tab</button>
  <button class="orange" onclick="showPaidTabs()">Paid Tabs</button>
</div>

<div id="new-tab" class="hidden">
  <input id="new-name" placeholder="Enter name">
  <button class="green" onclick="startTab()">Start Tab</button>
  <button class="red" onclick="returnToEmployeeScreen()">Cancel</button>
</div>

<div id="tab-view" class="hidden">
  <div class="topbar">
    <h2 id="tab-name"></h2>
    <button class="gray" onclick="viewContributions()">Who Added What</button>
  </div>
  <div class="grid">
    <button class="yellow" onclick="renderCategory('Draught', taps)">Draught Beer</button>
    <button class="pink" onclick="renderCategory('Singles', spirits)">Single Spirits</button>
    <button class="purple" onclick="renderCategory('Shots', shots)">Shots</button>
    <button class="green" onclick="renderCategory('Snacks', snacks)">Snacks</button>
  </div>
  <div id="items" class="grid"></div>
  <input id="custom-item" placeholder="Custom item">
  <button class="gray" onclick="addCustomItem()">Add Custom</button>
  <pre id="tab-content"></pre>
  <button class="green" onclick="saveTab()">Save</button>
  <button class="orange" onclick="payTab()">Pay</button>
  <button class="red" onclick="returnToEmployeeScreen()">Back</button>
</div>

<div id="paid-tabs" class="hidden">
  <h2>Paid Tabs</h2>
  <pre id="paid-content"></pre>
  <button class="red" onclick="returnToEmployeeScreen()">Back</button>
</div>

<script>
  const taps = ["Carling", "Fosters", "Strongbow", "Guinness", "Madri"];
  const spirits = ["Vodka + Coke", "Smirnoff", "Double Vodka", "Kraken + Coke"];
  const shots = ["Tequila Rose", "Fireball", "Sambuca", "Jäger"];
  const snacks = ["Crisps", "Bacon Fries"];
  const prices = {
    "Carling": 3.0, "Fosters": 2.9, "Strongbow": 3.1, "Guinness": 3.5, "Madri": 3.7,
    "Vodka + Coke": 4.0, "Smirnoff": 3.8, "Double Vodka": 4.5, "Kraken + Coke": 4.5,
    "Tequila Rose": 2.0, "Fireball": 2.0, "Sambuca": 2.0, "Jäger": 2.0,
    "Crisps": 1.0, "Bacon Fries": 1.0
  };

  let currentName = "", currentTab = {}, currentEmployee = "", contributions = {};
  let paidTabs = JSON.parse(localStorage.getItem("__PAID__") || "[]");

  function selectEmployee(name) {
    currentEmployee = name;
    document.getElementById("employee-select").classList.add("hidden");
    document.getElementById("home").classList.remove("hidden");
    refreshTabButtons();
  }

  function refreshTabButtons() {
    const c = document.getElementById("tab-buttons");
    c.innerHTML = "";
    Object.keys(localStorage).filter(k => k !== "__PAID__").forEach(name => {
      const b = document.createElement("button");
      b.className = "blue";
      b.textContent = name;
      b.onclick = () => loadTab(name);
      c.appendChild(b);
    });
  }

  function showNewTab() {
    document.getElementById("home").classList.add("hidden");
    document.getElementById("new-tab").classList.remove("hidden");
  }

  function startTab() {
    currentName = document.getElementById("new-name").value;
    if (!currentName) return;
    currentTab = {};
    contributions = {};
    showTabView();
  }

  function loadTab(name) {
    currentName = name;
    currentTab = JSON.parse(localStorage.getItem(name) || "{}");
    contributions = {};
    showTabView();
  }

  function showTabView() {
    document.getElementById("new-tab").classList.add("hidden");
    document.getElementById("home").classList.add("hidden");
    document.getElementById("tab-view").classList.remove("hidden");
    document.getElementById("tab-name").textContent = currentName + ' - ' + currentEmployee;
    renderCategory("Draught", taps);
    updateTabContent();
  }

  function renderCategory(label, list) {
    const c = document.getElementById("items");
    c.innerHTML = "";
    list.forEach(item => {
      const b = document.createElement("button");
      b.className = "gray";
      b.textContent = item;
      b.onclick = () => addItem(item);
      c.appendChild(b);
    });
  }

  function addItem(item) {
    currentTab[item] = (currentTab[item] || 0) + 1;
    if (!contributions[item]) contributions[item] = [];
    contributions[item].push(currentEmployee);
    updateTabContent();
  }

  function addCustomItem() {
    const item = document.getElementById("custom-item").value;
    if (!item) return;
    currentTab[item] = (currentTab[item] || 0) + 1;
    if (!contributions[item]) contributions[item] = [];
    contributions[item].push(currentEmployee);
    updateTabContent();
    document.getElementById("custom-item").value = "";
  }

  function updateTabContent() {
    const out = Object.entries(currentTab).map(([i, c]) => `${i}: ${c}`).join("\n");
    document.getElementById("tab-content").textContent = out;
  }

  function saveTab() {
    localStorage.setItem(currentName, JSON.stringify(currentTab));
    const popup = document.getElementById("save-popup");
    popup.style.display = "block";
    setTimeout(() => {
      popup.style.display = "none";
      returnToEmployeeScreen();
    }, 2000);
  }

  function returnToEmployeeScreen() {
    document.querySelectorAll("#home, #new-tab, #tab-view, #paid-tabs")
      .forEach(el => el.classList.add("hidden"));
    document.getElementById("employee-select").classList.remove("hidden");
  }

  function viewContributions() {
    const personMap = {};
    for (let item in contributions) {
      contributions[item].forEach(name => {
        if (!personMap[name]) personMap[name] = {};
        personMap[name][item] = (personMap[name][item] || 0) + 1;
      });
    }
    let msg = "";
    for (let person in personMap) {
      msg += `${person}:\n`;
      for (let item in personMap[person]) {
        msg += `  - ${item} x${personMap[person][item]}\n`;
      }
    }
    alert(msg || "No contributions recorded.");
  }

  function payTab() {
    const content = document.getElementById("summary-content");
    let html = `<strong>Tab:</strong> ${currentName}<br><strong>Employee:</strong> ${currentEmployee}<br><br>`;
    let total = 0;
    for (let item in currentTab) {
      const count = currentTab[item];
      const price = prices[item] || 0;
      const itemTotal = price * count;
      total += itemTotal;
      html += `${item} x${count} @ £${price.toFixed(2)} = £${itemTotal.toFixed(2)}<br>`;
    }
    html += `<br><strong>Total: £${total.toFixed(2)}</strong>`;
    content.innerHTML = html;
    document.getElementById("pay-summary").classList.remove("hidden");
  }

  function confirmPayment() {
    let total = 0;
    for (let item in currentTab) {
      total += (prices[item] || 0) * currentTab[item];
    }
    const record = {
      name: currentName,
      total: total.toFixed(2),
      by: currentEmployee,
      when: new Date().toLocaleString(),
      items: { ...currentTab }
    };
    paidTabs.push(record);
    localStorage.setItem("__PAID__", JSON.stringify(paidTabs));
    localStorage.removeItem(currentName);
    document.getElementById("pay-summary").classList.add("hidden");
    returnToEmployeeScreen();
  }

  function cancelPayment() {
    document.getElementById("pay-summary").classList.add("hidden");
  }

  function showPaidTabs() {
    document.getElementById("home").classList.add("hidden");
    document.getElementById("paid-tabs").classList.remove("hidden");
    document.getElementById("paid-content").textContent = paidTabs.map(r =>
      `${r.name} | £${r.total} | ${r.by} | ${r.when}\n` +
      Object.entries(r.items).map(([i, c]) => `- ${i}: ${c}`).join("\n") +
      "\n--------------------------------------"
    ).join("\n");
  }
</script>
</body>
</html>

Let me know when you’re ready to package this as an Android app or want features like item removal/editing in the pay screen.

