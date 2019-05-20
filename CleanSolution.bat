@echo off
echo Cleaning solution...

rmdir /q /s ".vs"
rmdir /q /s "bin"
rmdir /q /s "bin-int"

del /f "Minigin.sln.DotSettings.user"
del /f "Minigin\Minigin.vcxproj.user"
del /f "DigDug\DigDug.vcxproj.user"

echo Solution cleaned!
PAUSE