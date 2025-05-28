@echo off

:: Path to the Wrapper exeutable
set "WRAPPER=%~dp0../Wrapper/Source/x64/Debug/Wrapper.exe"

:: Path to shader compiler
set "SHADER_COMPILER=glsLangValidator"

:: Path to temporary log file
set "LOG_FILE=%~dp0temp.log"

echo Compiling shaders...

:: Compile all .vert files
for /R %%f in (*.vert) do (
    %SHADER_COMPILER% -V "%%f" -o "%%f.spv"
)

:: Compile all .frag files
for /R %%f in (*.frag) do (
    %SHADER_COMPILER% -V "%%f" -o "%%f.spv"
)

echo Compiling Defaults.wrap...

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
) else (
    echo Failed to generate Defaults.wrap
    exit /b %ERRORLEVEL%
)