@echo off
call %~dp0devenv.bat build %~dp0Build/layers.txt %*
if not %errorlevel%==0 (
    echo Build failed with error code %errorlevel%.
    exit /b %errorlevel%
)
call %~dp0devenv.bat build %*
if not %errorlevel%==0 (
    echo Build failed with error code %errorlevel%.
    exit /b %errorlevel%
)