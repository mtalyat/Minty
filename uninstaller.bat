@echo off

:: Remove the Minty environment variable
reg delete HKCU\Environment /F /V MINTY_PATH

echo You may now delete the repository.