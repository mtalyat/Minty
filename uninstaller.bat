@echo off

:: Remove the Minty environment variable
reg delete HKCU\Environment /F /V MINTY_PATH

:: Un-import the Minty Project Visual Studio project template
set "VS_PATH=%USERPROFILE%\Documents\Visual Studio 2022"
if not exist "%VS_PATH%\" (
    set "VS_PATH=%USERPROFILE%\Documents\Visual Studio 2019"
)
if exist "%VS_PATH%" (
    del /Q "%VS_PATH%\Templates\ProjectTemplates\Minty Project.zip"
    echo Removed the Minty Project project template from Visual Studio.
) else (
    echo Failed to remove the Minty Project project template from Visual Studio.
)

echo You may now delete the repository.