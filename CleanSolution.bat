@echo off
echo Cleaning solution...

rmdir /q /s ".vs"
rmdir /q /s "bin"
rmdir /q /s "bin-int"

echo Solution cleaned!
PAUSE