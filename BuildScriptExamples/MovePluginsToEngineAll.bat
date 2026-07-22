@echo off

set ueVersion=5.3

call :copyBuiltPluginToEngine %ueVersion%

set ueVersion=5.4

call :copyBuiltPluginToEngine %ueVersion%


set ueVersion=5.5

call :copyBuiltPluginToEngine %ueVersion%

set ueVersion=5.6

call :copyBuiltPluginToEngine %ueVersion%

pause

exit



:: function that copies the files for a plugin version into a release folder, and deletes the uneccessary built files. Takes the version to do this for as a parameter
:copyBuiltPluginToEngine
set ueVersionToCopy=%~1

echo Deleting previous plugin version
call RMDIR /s /q "D:\Program Files\Epic Games\UE_%ueVersionToCopy%\Engine\Plugins\Marketplace\GGameUtilsTutorialSystem"
echo Copying built plugin to engine
call xcopy /s /e /y /d /i "D:/Documents/BuiltPluginsTemp/UE%ueVersionToCopy%" "D:\Program Files\Epic Games\UE_%ueVersionToCopy%\Engine\Plugins\Marketplace\GGameUtilsTutorialSystem"
goto:eof

