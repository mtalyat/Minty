@echo off
if not defined MINTY_PATH (
  echo Error: MINTY_PATH environment variable is not set. Minty needs to be installed.
  exit /b 1
)
python "%MINTY_PATH%\Tools\Build\devenv.py" %*
exit /b %ERRORLEVEL%