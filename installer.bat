@echo off
:: This is the setup script for the Minty game engine.
:: Running this script will configure your system to be
:: able to build the engine source and any other
:: projects that use the engine library.

:: Set the Minty Enviornment Variable
set "pdir=%~dp0"
setx MINTY_PATH %pdir%
echo MINTY_PATH set to "%pdir%".

:: Import the Minty Project Visual Studio project template
set "VS_PATH=%USERPROFILE%\Documents\Visual Studio 2022"
if not exist "%VS_PATH%\" (
    set "VS_PATH=%USERPROFILE%\Documents\Visual Studio 2019"
)
if exist "%VS_PATH%" (
    xcopy "%pdir%Minty\Template\Minty Project.zip" "%VS_PATH%\Templates\ProjectTemplates\" /Y
    echo Imported the Minty Project project template into Visual Studio.
) else (
    echo Failed to import the Minty Project project template into Visual Studio.
)

pause