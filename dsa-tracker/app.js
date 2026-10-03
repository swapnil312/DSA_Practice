(() => {
  "use strict";

  const STORAGE_KEY = "dsa-tracker-fallback-v1";
  const HANDLE_DB = "dsa-tracker-handles";
  const HANDLE_STORE = "handles";
  const DEFAULT_DATA = { trackingStartDate: "2026-10-01", weeklyStart: "monday", goal: 5, entries: {} };

  const state = {
    data: null,
    view: "dashboard",
    chartRange: 30,
    logSearch: "",
    logSort: "date-desc",
    connected: false,
    permission: "none",
    directoryHandle: null,
    dataFileHandle: null,
    dataDirHandle: null,
    editingDate: null,
    calendarCursor: new Date(new Date().getFullYear(), new Date().getMonth(), 1),
    theme: localStorage.getItem("dsa-theme") || "dark"
  };

  const $ = (sel, root = document) => root.querySelector(sel);
  const $$ = (sel, root = document) => [...root.querySelectorAll(sel)];

  function pad(n) { return String(n).padStart(2, "0"); }
  function localDateKey(date = new Date()) {
    return `${date.getFullYear()}-${pad(date.getMonth() + 1)}-${pad(date.getDate())}`;
  }
  function parseDateKey(key) {
    const [y, m, d] = key.split("-").map(Number);
    return new Date(y, m - 1, d);
  }
  function addDays(date, amount) {
    const d = new Date(date);
    d.setDate(d.getDate() + amount);
    return d;
  }
  function daysBetween(startKey, endKey) {
    const a = parseDateKey(startKey), b = parseDateKey(endKey);
    return Math.floor((Date.UTC(b.getFullYear(), b.getMonth(), b.getDate()) - Date.UTC(a.getFullYear(), a.getMonth(), a.getDate())) / 86400000);
  }
  function dateRange(startKey, endKey) {
    const out = [];
    if (startKey > endKey) return out;
    let d = parseDateKey(startKey), end = parseDateKey(endKey);
    while (d <= end) { out.push(localDateKey(d)); d = addDays(d, 1); }
    return out;
  }
  function todayKey() { return localDateKey(); }
  function isFuture(key) { return key > todayKey(); }
  function getCount(key) {
    const e = state.data?.entries?.[key];
    return e && Number.isInteger(e.problems) && e.problems >= 0 ? e.problems : 0;
  }
  function fmtDate(key, opts = { month: "short", day: "numeric", year: "numeric" }) {
    return parseDateKey(key).toLocaleDateString(undefined, opts);
  }
  function fmtLong(key) {
    return parseDateKey(key).toLocaleDateString(undefined, { weekday: "long", month: "long", day: "numeric", year: "numeric" });
  }
  function escapeHtml(value = "") {
    return String(value).replace(/[&<>"']/g, c => ({ "&":"&amp;", "<":"&lt;", ">":"&gt;", '"':"&quot;", "'":"&#039;" }[c]));
  }
  function formatNumber(n) {
    return Number(n).toLocaleString(undefined, { maximumFractionDigits: 2 });
  }

  function normalizeData(raw) {
    if (!raw || typeof raw !== "object" || Array.isArray(raw)) throw new Error("Data must be a JSON object.");
    const trackingStartDate = String(raw.trackingStartDate || DEFAULT_DATA.trackingStartDate);
    if (!/^\d{4}-\d{2}-\d{2}$/.test(trackingStartDate) || Number.isNaN(parseDateKey(trackingStartDate).getTime())) {
      throw new Error("trackingStartDate must be a valid YYYY-MM-DD date.");
    }
    const entries = raw.entries && typeof raw.entries === "object" && !Array.isArray(raw.entries) ? raw.entries : {};
    const cleaned = {};
    for (const [key, value] of Object.entries(entries)) {
      if (!/^\d{4}-\d{2}-\d{2}$/.test(key)) continue;
      if (!value || typeof value !== "object") continue;
      const problems = Number(value.problems);
      if (!Number.isInteger(problems) || problems < 0) continue;
      cleaned[key] = {
        problems,
        names: Array.isArray(value.names) ? value.names.map(String).map(s => s.trim()).filter(Boolean) : [],
        notes: typeof value.notes === "string" ? value.notes : ""
      };
    }
    return {
      trackingStartDate,
      weeklyStart: "monday",
      goal: Number.isInteger(Number(raw.goal)) && Number(raw.goal) >= 0 ? Number(raw.goal) : DEFAULT_DATA.goal,
      entries: cleaned
    };
  }

  function serializeData() {
    return JSON.stringify(state.data, null, 2) + "\n";
  }

  async function openHandleDB() {
    if (!("indexedDB" in window)) return null;
    return new Promise((resolve) => {
      const req = indexedDB.open(HANDLE_DB, 1);
      req.onupgradeneeded = () => {
        if (!req.result.objectStoreNames.contains(HANDLE_STORE)) req.result.createObjectStore(HANDLE_STORE);
      };
      req.onsuccess = () => resolve(req.result);
      req.onerror = () => resolve(null);
    });
  }
  async function saveHandle(handle) {
    const db = await openHandleDB(); if (!db) return;
    return new Promise(resolve => {
      const tx = db.transaction(HANDLE_STORE, "readwrite");
      tx.objectStore(HANDLE_STORE).put(handle, "directory");
      tx.oncomplete = () => resolve();
      tx.onerror = () => resolve();
    });
  }
  async function loadHandle() {
    const db = await openHandleDB(); if (!db) return null;
    return new Promise(resolve => {
      const tx = db.transaction(HANDLE_STORE, "readonly");
      const req = tx.objectStore(HANDLE_STORE).get("directory");
      req.onsuccess = () => resolve(req.result || null);
      req.onerror = () => resolve(null);
    });
  }

  async function verifyPermission(handle, readWrite = true) {
    if (!handle) return false;
    const opts = readWrite ? { mode: "readwrite" } : {};
    try {
      if (await handle.queryPermission(opts) === "granted") return true;
      if (await handle.requestPermission(opts) === "granted") return true;
    } catch (_) {}
    return false;
  }

  async function getDataFileHandles(dirHandle) {
    // The user normally selects the dsa-tracker project root. Reuse its
    // existing /data folder. If the user accidentally selects the /data
    // folder itself, use that folder directly so we never create /data/data.
    try {
      const directFile = await dirHandle.getFileHandle("dsa-data.json", { create: false });
      return { dataDir: dirHandle, file: directFile, selectedDataFolder: true };
    } catch (_) {
      // No dsa-data.json directly inside the selected folder; continue below.
    }

    const dataDir = await dirHandle.getDirectoryHandle("data", { create: true });
    const file = await dataDir.getFileHandle("dsa-data.json", { create: true });
    return { dataDir, file, selectedDataFolder: false };
  }

  async function readJsonFromHandle(fileHandle) {
    const file = await fileHandle.getFile();
    const text = await file.text();
    if (!text.trim()) return normalizeData(DEFAULT_DATA);
    return normalizeData(JSON.parse(text));
  }

  async function writeJsonToHandle(fileHandle) {
    const payload = serializeData();
    const writable = await fileHandle.createWritable();
    try {
      await writable.write(payload);
      await writable.close();

      // Verify the browser can immediately read back the exact data it wrote.
      // This prevents the UI from claiming success when the disk write did not
      // actually complete.
      const savedFile = await fileHandle.getFile();
      const savedText = await savedFile.text();
      if (savedText !== payload) {
        throw new Error("The JSON file could not be verified after writing.");
      }
    } catch (err) {
      try { await writable.abort(); } catch (_) {}
      throw err;
    }
  }

  function loadFallback() {
    try {
      const raw = localStorage.getItem(STORAGE_KEY);
      return raw ? normalizeData(JSON.parse(raw)) : normalizeData(DEFAULT_DATA);
    } catch (_) {
      return normalizeData(DEFAULT_DATA);
    }
  }

  async function persist() {
    if (state.connected && state.dataFileHandle) {
      if (!(await verifyPermission(state.directoryHandle, true))) {
        state.connected = false;
        state.permission = "needs-permission";
        updateConnectionUI();
        throw new Error("Permission to write the tracker folder is no longer available.");
      }
      await writeJsonToHandle(state.dataFileHandle);
      return true;
    }

    // Browser fallback is deliberately explicit: it is NOT the JSON file.
    localStorage.setItem(STORAGE_KEY, serializeData());
    return false;
  }

  async function connectFolder(explicit = true) {
    if (!("showDirectoryPicker" in window)) {
      state.connected = false;
      state.permission = "unsupported";
      updateConnectionUI();
      if (explicit) toast("File System Access is unavailable. Using browser fallback.", "warning");
      return false;
    }
    try {
      const dir = await window.showDirectoryPicker({ mode: "readwrite" });
      if (!(await verifyPermission(dir))) {
        state.permission = "denied";
        updateConnectionUI();
        toast("Folder permission was not granted.", "error");
        return false;
      }
      const handles = await getDataFileHandles(dir);
      let data;
      try { data = await readJsonFromHandle(handles.file); }
      catch (err) {
        if (err instanceof SyntaxError) {
          toast("The JSON file is invalid. Fix or replace it before connecting.", "error");
          return false;
        }
        throw err;
      }
      state.directoryHandle = dir;
      state.dataDirHandle = handles.dataDir;
      state.dataFileHandle = handles.file;
      state.data = data;
      state.connected = true;
      state.permission = "granted";
      await saveHandle(dir);
      updateConnectionUI();
      render();
      toast(handles.selectedDataFolder
        ? "Connected to the existing data folder."
        : "Tracker project folder connected. Using data/dsa-data.json.", "success");
      return true;
    } catch (err) {
      if (err?.name === "AbortError") return false;
      state.permission = "error";
      updateConnectionUI();
      toast(`Could not connect: ${err.message || "unknown error"}`, "error");
      return false;
    }
  }

  async function tryReconnectStored() {
    if (!("showDirectoryPicker" in window)) {
      state.permission = "unsupported";
      updateConnectionUI();
      return;
    }
    const dir = await loadHandle();
    if (!dir) return;
    state.directoryHandle = dir;
    const ok = await verifyPermission(dir, false);
    if (!ok) {
      state.permission = "needs-permission";
      updateConnectionUI();
      return;
    }
    try {
      const handles = await getDataFileHandles(dir);
      state.data = await readJsonFromHandle(handles.file);
      state.dataDirHandle = handles.dataDir;
      state.dataFileHandle = handles.file;
      state.connected = true;
      state.permission = "granted";
      updateConnectionUI();
      render();
    } catch (_) {
      state.permission = "needs-permission";
      updateConnectionUI();
    }
  }

  async function reloadData() {
    if (state.connected && state.dataFileHandle) {
      try {
        state.data = await readJsonFromHandle(state.dataFileHandle);
        render();
        toast("JSON reloaded from disk.", "success");
      } catch (err) {
        toast(`Could not reload JSON: ${err.message}`, "error");
      }
    } else {
      state.data = loadFallback();
      render();
      toast("Fallback data reloaded.", "success");
    }
  }

  async function saveCurrent(showToast = true) {
    try {
      await persist();
      if (showToast) toast(state.connected ? "Progress saved to dsa-data.json." : "Saved in browser fallback.", "success");
      return true;
    } catch (err) {
      toast("Could not save your progress. Reconnect the tracker folder and try again.", "error");
      return false;
    }
  }

  function updateConnectionUI() {
    const dot = $("#connection-dot"), label = $("#connection-label"), detail = $("#connection-detail");
    if (!dot) return;
    dot.className = "status-dot";
    if (state.connected) {
      dot.classList.add("connected");
      label.textContent = "Connected";
      detail.textContent = "JSON file is writable";
    } else if (state.permission === "needs-permission") {
      dot.classList.add("warning");
      label.textContent = "Permission required";
      detail.textContent = "Reconnect the tracker folder";
    } else if (state.permission === "unsupported") {
      label.textContent = "Fallback mode";
      detail.textContent = "File Access API unavailable";
    } else {
      label.textContent = "Not connected";
      detail.textContent = "Using local fallback";
    }
  }

  function elapsedKeys() {
    const start = state.data.trackingStartDate, today = todayKey();
    return start <= today ? dateRange(start, today) : [];
  }
  function overallStats() {
    const keys = elapsedKeys();
    let total = 0;
    for (const key of keys) total += getCount(key);
    return { total, days: keys.length, average: keys.length ? total / keys.length : 0 };
  }
  function weekBounds(ref = new Date()) {
    const d = new Date(ref); d.setHours(0,0,0,0);
    const day = d.getDay(); // Sunday 0
    const diff = day === 0 ? -6 : 1 - day;
    const monday = addDays(d, diff);
    return [localDateKey(monday), localDateKey(addDays(monday, 6))];
  }
  function weekStats(ref = new Date()) {
    const [start, end] = weekBounds(ref);
    const today = todayKey();
    const effectiveEnd = end > today ? today : end;
    const keys = dateRange(start, effectiveEnd);
    const total = keys.reduce((sum, key) => sum + getCount(key), 0);
    return { start, end, elapsedDays: keys.length, total, average: keys.length ? total / keys.length : 0 };
  }
  function calculateCurrentStreak() {
    let d = parseDateKey(todayKey()), count = 0;
    while (true) {
      const key = localDateKey(d);
      if (getCount(key) > 0) { count++; d = addDays(d, -1); }
      else break;
    }
    return count;
  }
  function calculateLongestStreak() {
    const keys = elapsedKeys();
    let longest = 0, current = 0;
    for (const key of keys) {
      if (getCount(key) > 0) { current++; longest = Math.max(longest, current); }
      else current = 0;
    }
    return longest;
  }

  function greeting() {
    const h = new Date().getHours();
    if (h < 12) return "Good morning";
    if (h < 18) return "Good afternoon";
    return "Good evening";
  }

  function render() {
    updateConnectionUI();
    const app = $("#app");
    if (!app) return;
    const renderer = {
      dashboard: renderDashboard,
      log: renderLog,
      analytics: renderAnalytics,
      calendar: renderCalendar,
      settings: renderSettings
    }[state.view];
    renderer();
    $$(".nav-item").forEach(btn => btn.classList.toggle("active", btn.dataset.view === state.view));
  }

  function renderDashboard() {
    const today = todayKey(), todayCount = getCount(today), week = weekStats(), overall = overallStats();
    const current = calculateCurrentStreak(), longest = calculateLongestStreak();
    const goal = state.data.goal || 0;
    const goalPct = goal > 0 ? Math.min(100, todayCount / goal * 100) : 0;
    $("#app").innerHTML = `
      <div class="page-head">
        <div>
          <div class="eyebrow">Your daily coding progress</div>
          <h1>${greeting()} 👋</h1>
          <p class="subtitle">${fmtLong(today)}</p>
        </div>
        <div class="header-actions">
          <button class="secondary-button" data-action="connect">📁 ${state.connected ? "Connected" : "Connect folder"}</button>
          <button class="primary-button" data-action="jump-entry">＋ Log today</button>
        </div>
      </div>

      <section class="card hero">
        <div class="hero-copy">
          <div class="eyebrow">Today's progress</div>
          <h2 style="font-size:22px">Keep building the streak.</h2>
          <div class="date-line">${fmtDate(today, { weekday: "long", month: "long", day: "numeric", year: "numeric" })}</div>
          <div class="today-number"><strong>${todayCount}</strong><span>problems solved</span></div>
        </div>
        <div class="goal-wrap">
          <div class="goal-ring" style="--goal:${goalPct}%">
            <div class="goal-ring-inner"><strong>${goal > 0 ? Math.round(goalPct) + "%" : "—"}</strong><span>daily goal</span></div>
          </div>
          <div>
            <div style="font-weight:700;font-size:13px">${goal > 0 ? `${todayCount} / ${goal} problems` : "No daily goal"}</div>
            <div class="goal-caption" style="text-align:left;margin-top:5px">Set your target in Settings.</div>
          </div>
        </div>
      </section>

      <section class="stat-grid">
        ${statCard("Today", todayCount, "problems")}
        ${statCard("This week", week.total, `${formatNumber(week.average)} avg / day`)}
        ${statCard("Overall avg", formatNumber(overall.average), "per calendar day")}
        ${statCard("Overall total", overall.total, `${overall.days} days elapsed`)}
        ${statCard("Streak", `<span class="fire">🔥</span> ${current}`, `longest ${longest}`)}
      </section>

      <section class="grid-2">
        <div class="card section-card">
          <div class="section-title">
            <div><h2>Daily progress</h2><p>Recent problem-solving volume</p></div>
            <div class="range-tabs">
              ${[7,30,90].map(n => `<button class="range-tab ${state.chartRange===n?"active":""}" data-range="${n}">${n}d</button>`).join("")}
            </div>
          </div>
          <div class="chart-wrap">${renderBarChart(state.chartRange)}</div>
        </div>
        <div class="card section-card">
          <div class="section-title"><div><h2>At a glance</h2><p>Keep an eye on consistency</p></div></div>
          <div class="mini-list">
            <div class="mini-row"><span>Current streak</span><strong>🔥 ${current} day${current===1?"":"s"}</strong></div>
            <div class="mini-row"><span>Longest streak</span><strong>${longest} day${longest===1?"":"s"}</strong></div>
            <div class="mini-row"><span>Days elapsed</span><strong>${overall.days}</strong></div>
            <div class="mini-row"><span>Week average</span><strong>${formatNumber(week.average)}</strong></div>
            <div class="mini-row"><span>Tracking since</span><strong>${fmtDate(state.data.trackingStartDate)}</strong></div>
          </div>
        </div>
      </section>

      <section class="card heatmap-card">
        <div class="section-title"><div><h2>Contribution heatmap</h2><p>Every calendar day counts—even a zero.</p></div></div>
        ${renderHeatmap()}
      </section>

      <section class="card quick-entry" id="quick-entry">
        <div class="section-title"><div><h2>${state.editingDate ? "Edit daily progress" : "Log today's progress"}</h2><p>Problem names and notes are optional.</p></div></div>
        ${renderEntryForm(state.editingDate || today)}
      </section>
    `;
    bindDashboardEvents();
  }

  function statCard(label, value, meta) {
    return `<div class="card stat-card"><div class="stat-label">${label}</div><div class="stat-value">${value}</div><div class="stat-meta">${meta}</div></div>`;
  }

  function renderEntryForm(dateKey) {
    const entry = state.data.entries[dateKey] || { problems: 0, names: [], notes: "" };
    return `
      <form id="entry-form" data-date="${dateKey}">
        <div class="form-grid">
          <div class="field">
            <label for="entry-date">Date</label>
            <input class="input" id="entry-date" type="date" value="${dateKey}" max="${todayKey()}">
          </div>
          <div class="field">
            <label for="entry-problems">Problems solved <span style="color:var(--danger)">*</span></label>
            <input class="input" id="entry-problems" type="number" min="0" step="1" value="${entry.problems}" required>
          </div>
          <div class="field span-2">
            <label for="entry-names">Problem names <span class="helper">(optional · one per line or comma-separated)</span></label>
            <textarea class="textarea" id="entry-names" rows="3" placeholder="Two Sum&#10;Binary Search">${escapeHtml(entry.names.join("\n"))}</textarea>
          </div>
          <div class="field span-2">
            <label for="entry-notes">Notes <span class="helper">(optional)</span></label>
            <textarea class="textarea" id="entry-notes" placeholder="What did you learn today?">${escapeHtml(entry.notes)}</textarea>
          </div>
          <div class="form-actions span-2">
            ${state.editingDate ? `<button type="button" class="secondary-button" data-action="cancel-edit">Cancel</button>` : ""}
            <button class="primary-button" type="submit">✓ Save ${state.editingDate ? "changes" : "today's progress"}</button>
          </div>
        </div>
      </form>
    `;
  }

  function renderBarChart(range) {
    const today = parseDateKey(todayKey());
    const keys = [];
    for (let i = range - 1; i >= 0; i--) keys.push(localDateKey(addDays(today, -i)));
    const max = Math.max(1, ...keys.map(getCount));
    return `<div class="bar-chart">${keys.map((key, idx) => {
      const count = getCount(key), h = count ? Math.max(3, count / max * 82) : 1;
      const showLabel = range <= 7 || idx % Math.ceil(range / 7) === 0 || idx === range - 1;
      return `<div class="bar-col" title="${escapeHtml(fmtDate(key))}: ${count} problems"><span class="bar-value">${showLabel ? count : ""}</span><div class="bar" style="height:${h}%"></div><span class="bar-label">${showLabel ? fmtDate(key,{month:"short",day:"numeric"}).replace(" "," ") : ""}</span></div>`;
    }).join("")}</div>`;
  }

  function renderHeatmap() {
    const end = parseDateKey(todayKey());
    const start = addDays(end, -364);
    // Align to Sunday so seven rows represent Sun-Sat.
    const alignedStart = addDays(start, -start.getDay());
    const weeks = Math.ceil((daysBetween(localDateKey(alignedStart), todayKey()) + 1) / 7);
    const cells = [];
    let maxCount = Math.max(1, ...dateRange(localDateKey(alignedStart), todayKey()).map(getCount));
    for (let w = 0; w < weeks; w++) {
      const first = addDays(alignedStart, w * 7);
      const monthName = first.getDate() <= 7 ? first.toLocaleDateString(undefined, {month:"short"}) : "";
      cells.push(`<div class="hm-month" style="grid-column:${w+1}">${monthName}</div>`);
      for (let r = 0; r < 7; r++) {
        const d = addDays(first, r), key = localDateKey(d);
        const count = key <= todayKey() ? getCount(key) : 0;
        const level = count === 0 ? "" : count <= 2 ? "l1" : count <= 4 ? "l2" : count <= 7 ? "l3" : "l4";
        cells.push(`<div class="hm-cell ${level}" style="grid-column:${w+1};grid-row:${r+2}" title="${escapeHtml(fmtDate(key,{month:"long",day:"numeric",year:"numeric"}))}: ${count} problem${count===1?"":"s"}"></div>`);
      }
    }
    return `<div class="heatmap-scroll"><div class="heatmap">${cells.join("")}</div></div>
      <div class="heatmap-legend"><span>Less</span><span class="hm-cell"></span><span class="hm-cell l1"></span><span class="hm-cell l2"></span><span class="hm-cell l3"></span><span class="hm-cell l4"></span><span>More</span></div>`;
  }

  function bindDashboardEvents() {
    $$(".range-tab").forEach(btn => btn.addEventListener("click", () => { state.chartRange = Number(btn.dataset.range); renderDashboard(); }));
    $("#entry-form")?.addEventListener("submit", handleEntrySubmit);
    $("#entry-date")?.addEventListener("change", e => {
      const form = $("#entry-form");
      if (form && e.target.value > todayKey()) e.target.value = todayKey();
      if (form && !state.editingDate) {
        const key = e.target.value;
        const entry = state.data.entries[key] || { problems: 0, names: [], notes: "" };
        $("#entry-problems").value = entry.problems;
        $("#entry-names").value = entry.names.join("\n");
        $("#entry-notes").value = entry.notes;
      }
    });
    $$("[data-action='connect']").forEach(b => b.addEventListener("click", () => connectFolder(true)));
    $$("[data-action='jump-entry']").forEach(b => b.addEventListener("click", () => $("#entry-problems")?.focus()));
    $$("[data-action='cancel-edit']").forEach(b => b.addEventListener("click", () => { state.editingDate = null; renderDashboard(); }));
  }

  async function handleEntrySubmit(e) {
    e.preventDefault();
    const date = $("#entry-date").value, problems = Number($("#entry-problems").value);
    if (!/^\d{4}-\d{2}-\d{2}$/.test(date) || Number.isNaN(parseDateKey(date).getTime())) return toast("Please choose a valid date.", "error");
    if (date > todayKey()) return toast("Future dates cannot be logged.", "error");
    if (!Number.isInteger(problems) || problems < 0) return toast("Problems solved must be a non-negative whole number.", "error");
    const rawNames = $("#entry-names").value;
    const names = rawNames.split(/[\n,]/).map(s => s.trim()).filter(Boolean);
    const notes = $("#entry-notes").value.trim();
    state.data.entries[date] = { problems, names, notes };
    const ok = await saveCurrent(false);
    if (!ok) return;
    state.editingDate = null;
    render();
    toast("Progress saved.", "success");
  }

  function renderLog() {
    let rows = Object.entries(state.data.entries)
      .filter(([date]) => !isFuture(date))
      .map(([date, entry]) => ({date, ...entry}));
    const q = state.logSearch.trim().toLowerCase();
    if (q) rows = rows.filter(r => r.date.toLowerCase().includes(q) || r.names.join(" ").toLowerCase().includes(q) || r.notes.toLowerCase().includes(q));
    rows.sort((a,b) => state.logSort === "date-asc" ? a.date.localeCompare(b.date) : b.date.localeCompare(a.date));
    $("#app").innerHTML = `
      <div class="page-head">
        <div><div class="eyebrow">Your history</div><h1>Daily Log</h1><p class="subtitle">Search, review, edit, and remove your saved entries.</p></div>
        <div class="header-actions"><button class="primary-button" data-action="new-entry">＋ Add entry</button></div>
      </div>
      <div class="card table-card">
        <div class="table-toolbar">
          <div class="search-wrap"><span class="search-icon">⌕</span><input class="input" id="log-search" placeholder="Search date, problem name, or notes…" value="${escapeHtml(state.logSearch)}"></div>
          <select class="select" id="log-sort" style="width:auto"><option value="date-desc" ${state.logSort==="date-desc"?"selected":""}>Newest first</option><option value="date-asc" ${state.logSort==="date-asc"?"selected":""}>Oldest first</option></select>
        </div>
        ${rows.length ? `<div class="table-scroll"><table><thead><tr><th>Date</th><th>Problems</th><th>Problem names</th><th>Notes</th><th>Actions</th></tr></thead><tbody>
          ${rows.map(r => `<tr>
            <td>${escapeHtml(fmtDate(r.date))}</td><td><span class="badge">${r.problems}</span></td>
            <td>${r.names.length ? escapeHtml(r.names.join(", ")) : '<span class="muted">—</span>'}</td>
            <td>${r.notes ? escapeHtml(r.notes) : '<span class="muted">—</span>'}</td>
            <td><div class="row-actions"><button class="small-button" data-edit="${r.date}">Edit</button><button class="small-button" data-delete="${r.date}">Delete</button></div></td>
          </tr>`).join("")}
        </tbody></table></div>` : `<div class="empty"><div class="empty-icon">⌕</div><h3>No entries found</h3><p>${q ? "Try a different search term." : "Your saved daily entries will appear here."}</p><button class="primary-button" data-action="new-entry">Log your first day</button></div>`}
      </div>
    `;
    $("#log-search").addEventListener("input", e => { state.logSearch = e.target.value; renderLog(); const input=$("#log-search"); input.focus(); input.setSelectionRange(input.value.length,input.value.length); });
    $("#log-sort").addEventListener("change", e => { state.logSort = e.target.value; renderLog(); });
    $$("[data-edit]").forEach(b => b.addEventListener("click", () => { state.editingDate = b.dataset.edit; state.view="dashboard"; render(); setTimeout(()=>$("#quick-entry")?.scrollIntoView({behavior:"smooth"}),50); }));
    $$("[data-delete]").forEach(b => b.addEventListener("click", () => confirmDelete(b.dataset.delete)));
    $("[data-action='new-entry']").addEventListener("click", () => { state.editingDate=null; state.view="dashboard"; render(); setTimeout(()=>$("#entry-problems")?.focus(),50); });
  }

  function renderAnalytics() {
    const overall = overallStats(), week = weekStats(), current = calculateCurrentStreak(), longest = calculateLongestStreak();
    const weekRows = [];
    const today = parseDateKey(todayKey());
    for (let i=11;i>=0;i--) {
      const end = addDays(today, -i*7);
      const monday = addDays(end, end.getDay()===0?-6:1-end.getDay());
      const sunday = addDays(monday,6);
      const startKey=localDateKey(monday), endKey=localDateKey(sunday>today?today:sunday);
      const total=dateRange(startKey,endKey).reduce((s,k)=>s+getCount(k),0);
      weekRows.push({start:startKey,total});
    }
    const maxWeek = Math.max(1,...weekRows.map(x=>x.total));
    $("#app").innerHTML = `
      <div class="page-head"><div><div class="eyebrow">Patterns & consistency</div><h1>Analytics</h1><p class="subtitle">See how your daily practice adds up over time.</p></div></div>
      <div class="analytics-grid">
        <div class="card section-card"><div class="eyebrow">Overall volume</div><div class="metric-big">${overall.total}</div><div class="subtitle">Problems across ${overall.days} elapsed calendar days.</div><div class="progress-line"><span style="width:${Math.min(100, overall.average/10*100)}%"></span></div><div class="helper">Average: ${formatNumber(overall.average)} problems/day</div></div>
        <div class="card section-card"><div class="eyebrow">Consistency</div><div class="metric-big">🔥 ${current}</div><div class="subtitle">Current streak · longest is ${longest} day${longest===1?"":"s"}.</div><div class="progress-line"><span style="width:${Math.min(100,current/30*100)}%"></span></div><div class="helper">A zero or missed day breaks a streak.</div></div>
        <div class="card section-card"><div class="section-title"><div><h2>Weekly totals</h2><p>Last 12 calendar weeks</p></div></div><div class="week-list">${weekRows.map(w=>`<div class="week-row"><span>${escapeHtml(fmtDate(w.start,{month:"short",day:"numeric"}))}</span><div class="week-track"><span style="width:${w.total/maxWeek*100}%"></span></div><strong>${w.total}</strong></div>`).join("")}</div></div>
        <div class="card section-card"><div class="section-title"><div><h2>This week</h2><p>${fmtDate(week.start)} – ${fmtDate(week.end)}</p></div></div><div class="metric-big">${week.total}</div><div class="subtitle">${formatNumber(week.average)} average per elapsed day.</div><div class="mini-list" style="margin-top:14px"><div class="mini-row"><span>Elapsed days</span><strong>${week.elapsedDays}</strong></div><div class="mini-row"><span>Daily goal</span><strong>${state.data.goal || "Off"}</strong></div></div></div>
      </div>
    `;
  }

  function renderCalendar() {
    const cursor = new Date(state.calendarCursor.getFullYear(), state.calendarCursor.getMonth(), 1);
    const year=cursor.getFullYear(), month=cursor.getMonth(), first=new Date(year,month,1), last=new Date(year,month+1,0);
    const start=addDays(first, -first.getDay()), end=addDays(last, 6-last.getDay());
    const days=dateRange(localDateKey(start),localDateKey(end));
    $("#app").innerHTML = `
      <div class="page-head"><div><div class="eyebrow">Calendar view</div><h1>Calendar</h1><p class="subtitle">A monthly view of your daily problem count.</p></div></div>
      <div class="card section-card">
        <div class="calendar-head"><button class="secondary-button" data-cal="prev">← Previous</button><div class="calendar-title">${cursor.toLocaleDateString(undefined,{month:"long",year:"numeric"})}</div><button class="secondary-button" data-cal="next">Next →</button></div>
        <div class="month-grid">${["Sun","Mon","Tue","Wed","Thu","Fri","Sat"].map(x=>`<div class="day-name">${x}</div>`).join("")}${days.map(key=>{
          const d=parseDateKey(key), outside=d.getMonth()!==month, count=getCount(key);
          return `<div class="calendar-day ${outside?"outside":""} ${key===todayKey()?"today":""}" title="${escapeHtml(fmtDate(key,{month:"long",day:"numeric",year:"numeric"}))}: ${count} problems">
            <span class="calendar-day-number">${d.getDate()}</span><strong class="calendar-count">${key>todayKey()?"":count}</strong>
            <span class="calendar-note">${state.data.entries[key]?.names?.[0] ? escapeHtml(state.data.entries[key].names[0]) : key<=todayKey() && count===0 ? "No problems" : ""}</span>
          </div>`;
        }).join("")}</div>
      </div>
    `;
    $$("[data-cal]").forEach(b=>b.addEventListener("click",()=>{state.calendarCursor.setMonth(state.calendarCursor.getMonth()+(b.dataset.cal==="next"?1:-1));renderCalendar();}));
  }

  function renderSettings() {
    $("#app").innerHTML = `
      <div class="page-head"><div><div class="eyebrow">Preferences & data</div><h1>Settings</h1><p class="subtitle">Control storage, goals, and the local tracker connection.</p></div></div>
      <div class="settings-grid">
        <section class="card settings-card">
          <div class="section-title"><div><h2>Tracking</h2><p>These settings affect calculations.</p></div></div>
          <div class="field"><label for="start-date">Tracking start date</label><input class="input" id="start-date" type="date" value="${state.data.trackingStartDate}" max="${todayKey()}"><div class="helper">Overall averages and elapsed days start here.</div></div>
          <div class="field" style="margin-top:16px"><label for="daily-goal">Daily problem goal</label><input class="input" id="daily-goal" type="number" min="0" step="1" value="${state.data.goal}"><div class="helper">Set to 0 to turn the goal off.</div></div>
          <div class="setting-row"><div><div class="setting-title">Week starts Monday</div><div class="setting-desc">The tracker uses Monday–Sunday weeks.</div></div><strong style="color:var(--success)">✓ Fixed</strong></div>
          <div class="form-actions" style="margin-top:16px"><button class="primary-button" id="save-settings">Save settings</button></div>
        </section>
        <section class="card settings-card">
          <div class="section-title"><div><h2>Data & storage</h2><p>Keep the JSON file under your control.</p></div></div>
          ${storageNotice()}
          <div class="setting-row"><div><div class="setting-title">Tracker folder</div><div class="setting-desc">${state.connected ? "Connected to your project folder." : "Connect the project folder to enable direct JSON writes."}</div></div><button class="secondary-button" id="settings-connect">📁 ${state.connected?"Reconnect":"Connect"}</button></div>
          <div class="setting-row"><div><div class="setting-title">Reload JSON</div><div class="setting-desc">Read the current file from disk again.</div></div><button class="secondary-button" id="reload-data">🔄 Reload</button></div>
          <div class="setting-row"><div><div class="setting-title">Export JSON</div><div class="setting-desc">Download a portable backup of your current data.</div></div><button class="secondary-button" id="export-data">💾 Export</button></div>
          <div class="setting-row"><div><div class="setting-title">Import JSON</div><div class="setting-desc">Validate the file before replacing current data.</div></div><button class="secondary-button" id="import-data">📥 Import</button></div>
        </section>
      </div>
      <div class="card settings-card" style="margin-top:14px">
        <div class="section-title"><div><h2>Browser status</h2><p>File System Access API and local fallback.</p></div></div>
        <div class="${"showDirectoryPicker" in window ? "notice success-notice":"notice"}">
          ${"showDirectoryPicker" in window ? "✓ File System Access API is available. Chrome and Edge can connect directly to dsa-data.json." : "File System Access is unavailable in this browser. The app is using LocalStorage fallback; export JSON regularly."}
        </div>
      </div>
    `;
    $("#save-settings").addEventListener("click", async ()=>{
      const start=$("#start-date").value, goal=Number($("#daily-goal").value);
      if (!start || start>todayKey()) return toast("Tracking start date must be today or earlier.", "error");
      if (!Number.isInteger(goal)||goal<0) return toast("Daily goal must be a non-negative whole number.", "error");
      state.data.trackingStartDate=start; state.data.goal=goal;
      if (await saveCurrent(false)) { render(); toast("Settings saved.", "success"); }
    });
    $("#settings-connect").addEventListener("click",()=>connectFolder(true));
    $("#reload-data").addEventListener("click",reloadData);
    $("#export-data").addEventListener("click",exportJson);
    $("#import-data").addEventListener("click",()=>$("#import-file").click());
  }

  function storageNotice() {
    if (state.connected) return `<div class="notice success-notice">✓ Connected. Changes are written to <strong>data/dsa-data.json</strong> only after the disk write succeeds.</div>`;
    if (state.permission==="needs-permission") return `<div class="notice">⚠ The saved folder handle needs permission. Click Connect/Reconnect to authorize it again.</div>`;
    return `<div class="notice">Your browser is currently the fallback store. Connect the project folder to make <strong>data/dsa-data.json</strong> the primary source of truth.</div>`;
  }

  function exportJson() {
    const blob = new Blob([serializeData()], {type:"application/json"});
    const a=document.createElement("a"); a.href=URL.createObjectURL(blob); a.download=`dsa-data-${todayKey()}.json`; a.click();
    setTimeout(()=>URL.revokeObjectURL(a.href),1000); toast("JSON backup exported.", "success");
  }

  function importJson(file) {
    if (!file) return;
    const reader=new FileReader();
    reader.onload=async ()=>{
      try {
        const parsed=normalizeData(JSON.parse(reader.result));
        await showConfirm("Import JSON?", "The validated file will replace your current tracker data. Make sure you have a backup if needed.", "Import");
        state.data=parsed;
        if (await saveCurrent(false)) { render(); toast("JSON imported and saved.", "success"); }
      } catch(err) {
        if (err?.message==="__CANCELLED__") return;
        toast(`Invalid JSON file: ${err.message || "unknown error"}`, "error");
      }
    };
    reader.readAsText(file);
  }

  async function confirmDelete(date) {
    try {
      await showConfirm("Delete this entry?", `This will remove the ${fmtDate(date)} entry from your JSON file. This action cannot be undone.`, "Delete");
      delete state.data.entries[date];
      if (await saveCurrent(false)) { render(); toast("Entry deleted.", "success"); }
    } catch (err) {
      if (err?.message !== "__CANCELLED__") toast("Could not delete the entry.", "error");
    }
  }

  function showConfirm(title, message, confirmText) {
    return new Promise((resolve,reject)=>{
      const dialog=$("#confirm-dialog"), oldConfirm=$("#dialog-confirm");
      $("#dialog-title").textContent=title; $("#dialog-message").textContent=message; oldConfirm.textContent=confirmText;
      const clean=()=>{dialog.close(); oldConfirm.onclick=null; $("#dialog-cancel").onclick=null;};
      oldConfirm.onclick=()=>{clean();resolve();};
      $("#dialog-cancel").onclick=()=>{clean();reject(new Error("__CANCELLED__"));};
      dialog.showModal();
    });
  }

  function toast(message, type="success") {
    const el=document.createElement("div"); el.className=`toast ${type}`;
    el.innerHTML=`<span>${type==="success"?"✓":type==="error"?"⚠":"•"}</span><span>${escapeHtml(message)}</span>`;
    $("#toast-region").appendChild(el); setTimeout(()=>el.remove(),4200);
  }

  function setupNavigation() {
    $$(".nav-item").forEach(btn=>btn.addEventListener("click",()=>{state.view=btn.dataset.view;state.editingDate=null;render();$("#sidebar").classList.remove("open");}));
    $("#connect-btn").addEventListener("click",()=>connectFolder(true));
    $("#mobile-connect").addEventListener("click",()=>connectFolder(true));
    $("#mobile-menu").addEventListener("click",()=>$("#sidebar").classList.toggle("open"));
    $("#import-file").addEventListener("change",e=>{importJson(e.target.files[0]);e.target.value="";});
  }

  async function init() {
    state.data=loadFallback();
    setupNavigation();
    render();
    await tryReconnectStored();
  }

  // Expose small pure calculation helpers for optional browser-console/manual testing.
  window.DSATracker = {
    calculateWeeklyAverage: () => weekStats().average,
    calculateOverallAverage: () => overallStats().average,
    calculateCurrentStreak,
    calculateLongestStreak
  };

  document.addEventListener("DOMContentLoaded", init);
})();
