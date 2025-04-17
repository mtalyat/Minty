@echo off

:: Path to the Wrapper exeutable
set "WRAPPER=%~dp0../Wrapper/Source/x64/Debug/Wrapper.exe"

:: Path to the Defaults directory
%WRAPPER% update %~dp0Defaults

:: Pause to see the results
pause