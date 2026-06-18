@echo off
setlocal

for %%I in ("%~dp0.") do set "ROOT=%%~fI"
set "BUILD_DIR=%ROOT%\Output"

echo [clean] Removing build output from "%BUILD_DIR%"...
if exist "%BUILD_DIR%" (
    rmdir /s /q "%BUILD_DIR%"
    if errorlevel 1 (
        echo [clean] Failed to remove "%BUILD_DIR%".
        exit /b 1
    )
    echo [clean] Done.
) else (
    echo [clean] Nothing to clean.
)

exit /b 0
