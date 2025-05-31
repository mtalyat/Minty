@echo off
:: This is the setup script for the Minty game engine.
:: Running this script will configure your system to be
:: able to build the engine source and any other
:: projects that use the engine library.

:: Set the Minty Enviornment Variable
set "TEMP=%~dp0"
setx MINTY_PATH %TEMP%
echo MINTY_PATH set to "%MINTY_PATH%".

pause