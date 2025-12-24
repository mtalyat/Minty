@echo off
python "%~dp0Tools\Installer\installer.py" %*

if not %ERRORLEVEL%==0 (
    echo Installer script failed with error code %ERRORLEVEL%
    exit /b %ERRORLEVEL%
)

if "%1"=="install" (
    devenv.bat build engine wrapper -c release
    .\Data\update_defaults_wrap.bat
)

exit /b 0