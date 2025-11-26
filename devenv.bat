@REM @echo off
cls

@rem Parse command line arguments

if /i "%1"=="install" (
  setx MINTY_PATH %~dp0
  
  if not "%ERRORLEVEL%"=="0" (
    echo Failed to set MINTY_PATH environment variable.
    goto end
  )
  
  echo Minty installed successfully.
  goto end
  ) else if /i "%1"=="uninstall" (
  reg delete HKCU\Environment /F /V MINTY_PATH
  
  if not "%ERRORLEVEL%"=="0" (
    echo Failed to remove MINTY_PATH environment variable.
    goto end
  )
  
  echo Minty uninstalled successfully. You may now delete this repository, if you wish.
  goto end
)

if /i "%1"=="build" (
  set "BUILD=1"
  ) else if /i "%1"=="clean" (
  set "CLEAN=1"
  ) else if /i "%1"=="rebuild" (
  set "CLEAN=1"
  set "BUILD=1"
  ) else if /i "%1"=="run" (
  set "RUN=1"
  ) else if /i "%1"=="rerun" (
  set "BUILD=1"
  set "RUN=1"
  ) else if /i "%1"=="all" (
  set "CLEAN=1"
  set "BUILD=1"
  set "RUN=1"
  ) else (
  goto print_usage
)

if /i "%2"=="engine" (
  set "PROJECTS=Engine"
  ) else if /i "%2"=="minty" (
  set "PROJECTS=Engine"
  ) else if /i "%2"=="test" (
  set "PROJECTS=Test"
  ) else if /i "%2"=="all" (
  set "PROJECTS=Engine Test"
  ) else (
  set "PROJECTS=Engine Test"
)

if /i "%3"=="debug" (
  set "CONFIG=Debug"
  ) else if /i "%3"=="release" (
  set "CONFIG=Release"
  ) else if /i "%3"=="trace" (
  set "CONFIG=Debug-Trace"
  ) else (
  set "CONFIG=Debug"
)

if /i "%4"=="x64" (
  set "ARCHITECTURE=x64"
  ) else if /i "%4"=="arm64" (
  set "ARCHITECTURE=ARM64"
  ) else if /i "%4"=="x86" (
  set "ARCHITECTURE=Win32"
  ) else (
  set "ARCHITECTURE=x64"
)

@rem Process each project
for %%P in (%PROJECTS%) do (
  call :process_project "%%P"
  if not "%ERRORLEVEL%"=="0" (
    goto failure
  )
)

goto success

:process_project
set "PROJECT=%~1"
pushd "%~dp0\%PROJECT%\Build"

if defined CLEAN (
  @echo Cleaning %PROJECT%...
  if exist "Output" (
    rmdir /S /Q "Output"
  )
)

if defined BUILD (
  @echo Building %PROJECT%...
  
  @rem Remove previous build's file from bin directory, if they exist
  if exist "Bin\%CONFIG%" (
    del /Q "Bin\%CONFIG%\*.*"
  )
  
  if not exist "Output" (
    mkdir "Output"
  )
  pushd "Output"
  
  rem Generate build files
  cmake .. -A %ARCHITECTURE%
  
  if not "%ERRORLEVEL%"=="0" (
    echo CMake configuration failed!
    popd
    popd
    exit /b 1
  )
  
  rem Build the project
  powershell "cmake --build . --config %CONFIG% 2>&1 | tee build.log"
  
  if not "%ERRORLEVEL%"=="0" (
    echo Build failed!
    popd
    popd
    exit /b 1
  )
  
  if not exist "%CONFIG%" (
    echo Build failed! %CONFIG% not found.
    popd
    popd
    exit /b 1
  )
  
  @rem "Output"
  popd
  
  if not exist "Bin" (
    mkdir "Bin"
  )
  if not exist "Bin\%CONFIG%" (
    mkdir "Bin\%CONFIG%"
  )
  
  rem Copy built binaries into bin directory (check both paths)
  xcopy "Output\%CONFIG%\*" "Bin\%CONFIG%" /E /Y /I 2>&1 > nul
  
  if not "%ERRORLEVEL%"=="0" (
    echo Copying binaries failed!
    popd
    exit /b 1
  )
)

if defined RUN (
  if exist "Bin\%CONFIG%\%PROJECT%.exe" (
    @echo Running %PROJECT%...
    start cmd /k "Bin\%CONFIG%\%PROJECT%.exe"
    ) else (
    echo Executable not found: Bin\%CONFIG%\%PROJECT%.exe
    popd
    exit /b 1
  )
)

@rem "%~dp0\%PROJECT%\Build"
popd
exit /b 0

:print_usage
echo Usage: devenv.bat [build^|clean^|rebuild^|run^|rerun] [minty^|test] [debug^|release] [x64^|x86^|arm64]
goto end

:failure
echo Failure while processing project %PROJECT%.
goto end

:success
echo Success.
goto end

:end

@rem Cleanup
set CONFIG=
set ARCHITECTURE=
set PROJECT=
set PROJECTS=
set BUILD=
set CLEAN=
set RUN=
