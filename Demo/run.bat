@echo off
setlocal

for %%I in ("%~dp0.") do set "ROOT=%%~fI"
set "BUILD_DIR=%ROOT%\Output"
set "CONFIG=Debug"

if not "%~1"=="" set "CONFIG=%~1"

call "%ROOT%\build.bat" "%CONFIG%"
if errorlevel 1 (
    echo [run] Build step failed.
    exit /b 1
)

set "EXE=%BUILD_DIR%\%CONFIG%\demo_app.exe"
if not exist "%EXE%" (
    set "EXE=%BUILD_DIR%\demo_app.exe"
)

if not exist "%EXE%" (
    echo [run] Could not find demo_app.exe in "%BUILD_DIR%".
    exit /b 1
)

echo [run] Launching "%EXE%"...
"%EXE%"
exit /b %ERRORLEVEL%
