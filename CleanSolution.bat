@echo off
echo Cleaning solution...

rmdir /q /s "Win32"
rmdir /q /s "x64"
rmdir /q /s "Minigin/Win32"
rmdir /q /s "Minigin/x64"
rmdir /q /s ".vs"

echo Solution cleaned!
PAUSE