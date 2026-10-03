# DSA Progress Tracker

A local-first, dark-mode DSA progress tracker built with **HTML, CSS, and vanilla JavaScript**. It is designed for daily use: record the number of problems you solved, optionally add problem names and notes, then review streaks, averages, charts, and a contribution-style heatmap.

The primary data source is the human-readable file:

```text
data/dsa-data.json
```

No Node.js, npm, database, Firebase, or backend framework is required.

---

## Features

- Modern dark-mode-first productivity dashboard
- Daily problem count with optional names and notes
- Daily Log with search, sorting, editing, and deletion
- Daily, weekly, and overall statistics
- Monday–Sunday week calculation
- Missed days count as zero in averages
- Current and longest streaks
- Recent daily progress charts
- Weekly analytics
- Contribution-style yearly heatmap
- Monthly calendar
- JSON import/export
- Direct JSON persistence through the File System Access API
- IndexedDB remembers the selected project folder when supported
- LocalStorage fallback for browsers without File System Access
- Safe save behavior: success is reported only after the write completes
- Responsive desktop/tablet/smaller-screen layout
- Git/GitHub-friendly data file
- One-click Windows startup through `start-tracker.bat`

---

## Project Structure

```text
dsa-tracker/
├── index.html
├── style.css
├── app.js
├── README.md
├── start-tracker.bat
└── data/
    └── dsa-data.json
```

The project intentionally stays small. There are no dependencies to install.

---

## Requirements

### Recommended

- Windows
- Python 3
- Google Chrome or Microsoft Edge

Chrome/Edge are recommended because the **File System Access API** is best supported there.

The app can still run in browsers without File System Access by using the LocalStorage fallback and JSON import/export.

### Python

Python is required for the included one-click `.bat` launcher.

Verify Python:

```bash
python --version
```

If Windows does not recognize `python`, try:

```bash
py --version
```

If `py` works but `python` does not, you can edit `start-tracker.bat` and replace the `python -m http.server 8000` command with:

```bat
py -m http.server 8000
```

If neither command works, install Python from the official Python website and make sure the Python launcher/PATH option is enabled.

---

## Installation

1. Extract the `dsa-tracker` folder somewhere convenient.
2. Make sure Python is installed.
3. Double-click:

```text
start-tracker.bat
```

The script changes into the project directory, starts a local HTTP server on port `8000`, waits briefly, and opens the browser.

You can also start it manually:

```bash
cd path\to\dsa-tracker
python -m http.server 8000
```

Then visit:

```text
http://localhost:8000
```

---

## Running the Application

The preferred URL is:

```text
http://localhost:8000
```

`localhost` means **this computer**. The tracker is not being published to the internet.

The Python server only serves the frontend files. It is **not the database** and it does not contain your DSA progress.

Your actual primary data is:

```text
data/dsa-data.json
```

---

## One-Click Startup

Double-click:

```text
start-tracker.bat
```

It will:

1. Navigate to the folder containing the batch file.
2. Start Python's built-in HTTP server on port `8000`.
3. Wait approximately two seconds.
4. Open `http://localhost:8000`.
5. Keep the server alive while its terminal window remains open.

When you are finished, close the server terminal window.

Your JSON data is **not deleted** when the server stops.

---

## How start-tracker.bat Works

The important part is:

```bat
cd /d "%~dp0"
python -m http.server 8000
```

`%~dp0` resolves to the directory containing the `.bat` file, so the script does not depend on the current Windows working directory.

The browser is opened separately at:

```text
http://localhost:8000
```

If the browser does not open automatically, manually visit that address.

If port `8000` is already in use, either stop the existing Python server or change the port consistently in the batch file and the URL it opens.

---

## Python Installation

Install Python 3 if needed.

After installation, open a new Command Prompt and verify:

```bash
python --version
```

or:

```bash
py --version
```

If Windows says:

```text
'python' is not recognized...
```

Python may not be installed or may not be on PATH. Reinstall/repair Python with the PATH option enabled, or use the `py` launcher and update the batch file as described above.

---

## Connecting the Tracker Folder

The first time you use the app in Chrome/Edge:

1. Start the local server.
2. Open `http://localhost:8000`.
3. Click **Connect folder**.
4. Select the `dsa-tracker` project folder.
5. Allow read/write permission.

The app then looks for:

```text
data/
```

and creates it if needed.

It also finds or creates:

```text
data/dsa-data.json
```

The JSON is read and loaded into the application.

When you save a daily entry, the app writes the updated JSON to that file.

### Important

A browser may require permission to be granted again later. The UI reports:

```text
Permission required
```

instead of pretending the folder is connected.

---

## File System Access API

When supported, the app uses:

```javascript
window.showDirectoryPicker()
```

to let you select the project folder.

It then uses the directory/file handles to read and write:

```text
data/dsa-data.json
```

Saving uses the standard writable-file flow:

```javascript
const writable = await fileHandle.createWritable();
await writable.write(jsonText);
await writable.close();
```

The app does not display a successful-save message until the write has completed.

If the write fails, the app reports an error and keeps the in-memory data available so you can retry/reconnect or export a backup.

---

## Remembering the Connected Folder

When possible, the directory handle is stored in IndexedDB.

On the next visit, the app attempts to reuse it.

If the browser says permission is already available, the app reconnects automatically.

If permission is required again, the UI says:

```text
Permission required
```

and asks you to reconnect.

The app never claims a connection exists without a usable file handle.

---

## Why localhost Is Used

There is an important difference between:

```text
file:///C:/.../index.html
```

and:

```text
http://localhost:8000
```

Opening an HTML file directly uses the browser's `file://` origin. Browser security restrictions make direct local-file usage unsuitable for reliably using modern file APIs.

This tracker therefore runs through a local HTTP server.

`localhost` means:

> the server is running on your own computer.

It does **not** mean the tracker is public.

The Python server simply serves HTML/CSS/JavaScript. The tracker data remains in:

```text
data/dsa-data.json
```

---

## JSON Data Storage

The primary source of truth is:

```text
data/dsa-data.json
```

You can open it directly in VS Code and inspect your progress.

Initial file:

```json
{
  "trackingStartDate": "2026-10-01",
  "entries": {}
}
```

The app may also store the configured daily goal.

A normal populated file looks like:

```json
{
  "trackingStartDate": "2026-10-01",
  "weeklyStart": "monday",
  "goal": 5,
  "entries": {
    "2026-10-01": {
      "problems": 5,
      "names": [
        "Two Sum",
        "Binary Search"
      ],
      "notes": "Arrays and searching"
    }
  }
}
```

Problem count is authoritative. The number of names does not have to equal the problem count.

---

## Daily Entry

From the dashboard, enter:

- Problems solved — required, non-negative integer
- Problem names — optional
- Notes — optional

Names can be entered one per line or comma-separated.

If today has no JSON entry, calculations treat it as:

```text
0 problems
```

The app does not create a physical zero entry merely because you opened the dashboard.

---

## Missed-Day Logic

A missing entry represents zero for calculations.

Example:

```text
Monday = 5
Tuesday = 4
Wednesday = 6
Thursday = missed
```

The total is:

```text
5 + 4 + 6 + 0 = 15
```

Days elapsed:

```text
4
```

Average:

```text
15 / 4 = 3.75
```

Missed days are therefore **not excluded** from averages.

---

## Weekly Average Calculation

Weeks are:

```text
Monday → Sunday
```

The current week only includes elapsed calendar days.

For example, if today is Thursday:

```text
Monday = 5
Tuesday = 4
Wednesday = 6
Thursday = 0
```

Then:

```text
Weekly total = 15
Elapsed days = 4
Weekly average = 15 / 4 = 3.75
```

It is not divided by seven before the week is complete.

---

## Overall Average Calculation

Overall average is:

```text
total problems solved
---------------------
calendar days elapsed
```

from:

```text
trackingStartDate
```

through:

```text
today
```

Every elapsed calendar day counts, including zero/missed days.

Future dates never affect the calculation.

---

## Streak Calculation

### Current Streak

The current streak counts consecutive calendar days ending today where:

```text
problems > 0
```

A zero or missing day breaks it.

Example:

```text
Monday    5
Tuesday   3
Wednesday 7
Thursday  0
Friday    4
```

Friday's current streak is:

```text
1
```

### Longest Streak

The longest streak is the maximum consecutive run of elapsed calendar days where:

```text
problems > 0
```

---

## Dashboard

The dashboard includes:

- Today's problem count
- Today's date
- Daily goal progress
- This week's total and average
- Overall total and average
- Days elapsed
- Current streak
- Longest streak
- Recent daily chart
- Contribution heatmap
- Quick daily entry form

---

## Daily Log

Daily Log supports:

- Date search
- Problem-name search
- Notes search
- Newest/oldest sorting
- Edit
- Delete with confirmation

Edits and deletions are persisted to the connected JSON file.

If a delete/save operation cannot be written, the app reports the failure rather than claiming success.

---

## Charts

The dashboard daily chart supports:

- 7 days
- 30 days
- 90 days

It uses the local calendar and treats missing entries as zero.

Analytics also shows the totals for recent calendar weeks.

---

## Heatmap

The heatmap shows approximately one year of calendar activity.

Intensity:

```text
0       → empty
1–2     → low
3–4     → medium
5–7     → high
8+      → very high
```

Hover over a square to see the date and problem count.

Future dates are not counted.

---

## Calendar

The Calendar page provides a monthly view.

Each day shows the number of problems solved. Today is visually highlighted.

Missing days are displayed as zero for the current/past calendar view.

---

## Import / Export

### Export

Use:

```text
Settings → Export JSON
```

This downloads a dated backup such as:

```text
dsa-data-2026-10-03.json
```

### Import

Use:

```text
Settings → Import JSON
```

The file is parsed and validated before it replaces the current in-memory data.

The app does not replace the current data when the selected JSON is invalid.

After successful validation, the imported data is saved through the currently connected storage method.

---

## Backup

A simple backup strategy is:

1. Use **Export JSON** periodically.
2. Keep the generated JSON somewhere safe.
3. Commit `data/dsa-data.json` to Git if you want version history.

Because the tracker is local-first, you remain in control of the raw data file.

---

## Git Workflow

From the project directory:

```bash
git status
git add data/dsa-data.json
git commit -m "Update DSA progress"
git push
```

You can also commit code changes:

```bash
git add .
git commit -m "Update tracker"
git push
```

Do not commit credentials, tokens, passwords, or other secrets.

---

## GitHub Usage

GitHub is being used for:

> version control and backup

It is **not** the live database.

The local app writes:

```text
data/dsa-data.json
```

Git tracks that file.

The Python server does not push anything to GitHub automatically.

---

## Data Safety

The application follows these principles:

- The JSON file is the primary source of truth when File System Access is available.
- A success toast is shown only after the file write succeeds.
- Failed writes show an error.
- Current in-memory data is retained after a failed save so you can retry or export it.
- Import files are validated before replacement.
- Future dates are ignored by progress calculations.
- No API keys or credentials are required.
- The app does not send your DSA data to a remote service.

### LocalStorage fallback

If File System Access is unavailable, the app uses LocalStorage as a temporary browser fallback.

In that mode, the UI explicitly reports that the fallback is active.

Export your JSON regularly because LocalStorage is tied to the browser profile and is not the same thing as your project JSON file.

---

## Troubleshooting

### Python not found

If you see:

```text
'python' is not recognized...
```

try:

```bash
py --version
```

If `py` works, update the batch file to use:

```bat
py -m http.server 8000
```

Otherwise install Python and enable the PATH option.

---

### Port 8000 already in use

If another program/server is using port `8000`, stop it or choose another port.

For example:

```bash
python -m http.server 8001
```

If changing the port, also change the URL opened by `start-tracker.bat` from:

```text
http://localhost:8000
```

to:

```text
http://localhost:8001
```

---

### Browser does not open

Manually visit:

```text
http://localhost:8000
```

Keep the server terminal open while using the application.

---

### Folder permission problem

Click:

```text
Connect folder
```

again and select the `dsa-tracker` project folder.

When prompted, allow read/write access.

The application needs permission to write:

```text
data/dsa-data.json
```

---

### JSON save failure

If the app reports:

```text
Could not save your progress
```

do not assume the file was updated.

Reconnect the tracker folder and retry.

You can also use:

```text
Settings → Export JSON
```

to create a backup of the current in-memory state.

---

### File System Access unavailable

Use Chrome or Edge for the best experience.

If the browser does not support the API, the app continues in fallback mode using LocalStorage and JSON import/export.

---

### I edited dsa-data.json manually

Use:

```text
Settings → Reload
```

to read the current JSON from disk again.

If you edit the file externally while the app is open, reload before making additional changes.

---

## Browser Compatibility

### Recommended

- Google Chrome
- Microsoft Edge

### Fallback

Browsers without the File System Access API can still use:

- dashboard calculations
- LocalStorage fallback
- JSON import
- JSON export
- charts
- heatmap
- daily log

Direct automatic writing to the project JSON requires a browser with File System Access support.

---

## FAQ

### Is my data uploaded anywhere?

No. The tracker is designed as a local application. The Python server serves files from your computer, and the File System Access API writes to your local JSON file.

### Is localhost public?

No.

```text
localhost = this computer
```

It is not automatically accessible from the public internet.

### Is Python my database?

No. Python's built-in HTTP server only serves the frontend files.

The data is:

```text
data/dsa-data.json
```

### What happens when I close the server?

The local web server stops. Your JSON file remains exactly where it was. Nothing is deleted.

### Why isn't today's missing entry written as zero?

A missing entry is interpreted as zero for calculations. Avoiding automatic zero entries keeps the JSON cleaner. You can explicitly save a zero if you want an entry to appear in the Daily Log.

### Do future entries affect my average?

No. Future dates are ignored by totals, averages, streaks, and current progress calculations.

### Does a missed day break a streak?

Yes. A missing entry or an entry with zero problems breaks a streak.

### Does a missed day affect averages?

Yes. It counts as zero and remains part of the elapsed calendar-day denominator.

### Can I use GitHub as the database?

The intended design is no. GitHub is for version control and backup. The local JSON file is the live data source.

### Can I change the weekly start day?

The tracker deliberately uses Monday as the fixed week start to keep the calculations consistent with the requested behavior.

---

## Calculation Test Cases

The core calculation rules are:

### Test 1

```text
5
4
6
0
```

Total:

```text
15
```

Average:

```text
3.75
```

### Test 2

```text
5
4
6
```

Average:

```text
5
```

### Test 3

```text
5
0
6
```

Average:

```text
11 / 3 = 3.666...
```

### Test 4

```text
5
4
6
```

Current streak:

```text
3
```

### Test 5

```text
5
4
0
6
```

Current streak:

```text
1
```

Longest streak:

```text
2
```

### Test 6

A future entry such as:

```text
2099-01-01
```

does not contribute to current totals, averages, charts, heatmap progress, or streaks.

---

## Notes for Daily Use

A simple workflow is:

1. Start the tracker.
2. Connect the folder once in Chrome/Edge.
3. Each day, enter your problem count.
4. Optionally add names and notes.
5. Commit `data/dsa-data.json` to Git whenever you want a versioned backup.
6. Export an occasional JSON backup as an extra safety measure.

The goal is to make the daily action take only a few seconds.


### Folder selection note
Select the `dsa-tracker` project folder, not its `data` subfolder. The app reuses the existing `data/dsa-data.json`; if `data` itself is selected, it will not create another `data` folder.
