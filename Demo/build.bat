@echo off
setlocal

for %%I in ("%~dp0.") do set "ROOT=%%~fI"
set "BUILD_DIR=%ROOT%\Output"
set "CONFIG=Debug"
set "CACHE_FILE=%BUILD_DIR%\CMakeCache.txt"
for %%I in ("%ROOT%\..\Engine") do set "ENGINE_DIR=%%~fI"
set "ENGINE_ARTIFACTS_DIR=%ENGINE_DIR%\Output\Artifacts"
set "ENGINE_ALL_BUILD_DIR=%ENGINE_DIR%\Output\Build\All"

if not "%~1"=="" set "CONFIG=%~1"

set "ENGINE_LIB=%ENGINE_ARTIFACTS_DIR%\%CONFIG%\Engine.lib"

if not exist "%ENGINE_LIB%" (
    echo [build] Error: Missing %CONFIG% Engine.lib: "%ENGINE_LIB%"
    echo [build] Build Engine first, then try again.
    exit /b 1
)

if exist "%CACHE_FILE%" (
    set "GEN_INSTANCE="
    for /f "tokens=1,* delims==" %%A in ('findstr /b /c:"CMAKE_GENERATOR_INSTANCE:INTERNAL=" "%CACHE_FILE%"') do set "GEN_INSTANCE=%%B"
    if not "%GEN_INSTANCE%"=="" (
        if not exist "%GEN_INSTANCE%" (
            echo [build] Cached Visual Studio instance no longer exists: "%GEN_INSTANCE%"
            echo [build] Clearing stale CMake cache so generator can be re-detected...
            del /f /q "%CACHE_FILE%" >nul 2>&1
            if exist "%BUILD_DIR%\CMakeFiles" rmdir /s /q "%BUILD_DIR%\CMakeFiles"
        )
    )
)

echo [build] Configuring CMake in "%BUILD_DIR%"...
cmake -S "%ROOT%" -B "%BUILD_DIR%"
if errorlevel 1 (
    echo [build] Configure failed.
    exit /b 1
)

echo [build] Building demo_app (%CONFIG%)...
cmake --build "%BUILD_DIR%" --config "%CONFIG%" --target demo_app --parallel
if errorlevel 1 (
    echo [build] Build failed.
    exit /b 1
)

echo [build] Success.
exit /b 0
