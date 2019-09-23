@echo off
set var=%~dp0
if exist %var%\temp\* rmdir %var%\temp /s /q
echo %var%
mkdir temp
pause