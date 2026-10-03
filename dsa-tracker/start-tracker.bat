@echo off
title DSA Progress Tracker

cd /d "%~dp0"

echo ========================================
echo       DSA Progress Tracker
echo ========================================
echo.
echo Starting local server...
echo.

where python >nul 2>&1
if %errorlevel%==0 (
    start "" /min cmd /c "python -m http.server 8000"
) else (
    where py >nul 2>&1
    if %errorlevel%==0 (
        start "" /min cmd /c "py -m http.server 8000"
    ) else (
        echo ERROR: Python was not found.
        echo Install Python 3 and ensure "python" or "py" works in Command Prompt.
        echo.
        pause
        exit /b 1
    )
)

timeout /t 2 /nobreak >nul

echo Opening DSA Tracker...
start "" "http://localhost:8000"

echo.
echo DSA Tracker is running at:
echo http://localhost:8000
echo.
echo Keep this window open while using the tracker.
echo Close it to stop the server.
echo.

pause
