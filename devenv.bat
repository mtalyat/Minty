@echo off
python "%~dp0Tools\Build\devenv.py" %*
exit /b %ERRORLEVEL%