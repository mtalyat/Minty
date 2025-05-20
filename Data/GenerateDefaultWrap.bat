@echo off

:: Path to the Wrapper exeutable
set "WRAPPER=%~dp0../Wrapper/Source/x64/Debug/Wrapper.exe"

:: Check if Defaults.wrap exists and run the command if it does
if exist "%~dp0Defaults.wrap" (
    :: Path to the Defaults directory
    %WRAPPER% update %~dp0Defaults
) else (
    %WRAPPER% wrap %~dp0Defaults -b Defaults
)

if %ERRORLEVEL% equ 0 (
    :: Copy the generated wrap file to other directories
    copy /Y "%~dp0Defaults.wrap" "%~dp0../Minty/Test/Assets/test.wrap" >nul
)

:: Pause to see the results
pause