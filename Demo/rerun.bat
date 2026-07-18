@echo off
setlocal

for %%I in ("%~dp0.") do set "ROOT=%%~fI"
set "CONFIG=Debug"

if not "%~1"=="" set "CONFIG=%~1"

call "%ROOT%\build.bat" "%CONFIG%"
if errorlevel 1 (
    echo [rerun] Build step failed.
    exit /b 1
)

call "%ROOT%\run.bat" "%CONFIG%" /nobuild
exit /b %ERRORLEVEL%