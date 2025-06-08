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
set "FULL_VS_PATH=%VS_PATH%\Templates\ProjectTemplates\"
if exist "%VS_PATH%" (
    if not exist "%FULL_VS_PATH%" (
        mkdir "%FULL_VS_PATH%"
    )
    xcopy "%pdir%Minty\Template\Minty Project.zip" "%FULL_VS_PATH%" /Y
    echo Imported the Minty Project project template into Visual Studio.
) else (
    echo Failed to import the Minty Project project template into Visual Studio.
)

pause