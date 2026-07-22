@echo off

set ueVersion=5.3

:: set build configuration to work for UE 5.3
xcopy /y "C:\Users\epicm\AppData\Roaming\Unreal Engine\UnrealBuildTool\BuildConfiguration_UE5.3.xml" "C:\Users\epicm\AppData\Roaming\Unreal Engine\UnrealBuildTool\BuildConfiguration.xml"
call :buildPlugin %ueVersion%
call :copyBuiltFilesToRelease %ueVersion%


:: set build configuration to work for newer engine versions
xcopy /y "C:\Users\epicm\AppData\Roaming\Unreal Engine\UnrealBuildTool\BuildConfiguration_UE5.4Plus.xml" "C:\Users\epicm\AppData\Roaming\Unreal Engine\UnrealBuildTool\BuildConfiguration.xml"
set ueVersion=5.4

call :buildPlugin %ueVersion%
call :copyBuiltFilesToRelease %ueVersion%



set ueVersion=5.6

call :buildPlugin %ueVersion%
call :copyBuiltFilesToRelease %ueVersion%

:: set build configuration back to working for UE 5.3
xcopy /y "C:\Users\epicm\AppData\Roaming\Unreal Engine\UnrealBuildTool\BuildConfiguration_UE5.3.xml" "C:\Users\epicm\AppData\Roaming\Unreal Engine\UnrealBuildTool\BuildConfiguration.xml"
pause
exit

:: function that builds the plugin based on the version given as a parameter
:buildPlugin
set ueVersionToBuild=%~1
echo Starting GG Tutorial System Plugin Build for UE %ueVersionToBuild%
call "D:/Program Files/Epic Games/UE_%ueVersionToBuild%/Engine/Build/BatchFiles/RunUAT.bat" BuildPlugin -plugin="D:/GameSystemProjects/GGameUtils/GGameUtils/Plugins/GGameUtilsTutorialSystem/GGameUtilsTutorialSystem.uplugin" -package="D:/Documents/BuiltPluginsTemp/UE%ueVersionToBuild%"
if %ERRORLEVEL% NEQ 0 (
	ECHO Error with UE %ueVersionToBuild% Plugin build process
 	pause
)
echo Build process finished, see above for results
goto:eof



:: function that copies the files for a plugin version into a release folder, and deletes the uneccessary built files. Takes the version to do this for as a parameter
:copyBuiltFilesToRelease
set ueVersionToCopy=%~1

echo Copying build files to release folder
call RMDIR /s /q "D:/Documents/BuiltPluginsTemp/UE%ueVersionToCopy%Rel"
call xcopy /s /e /y /d /i "D:/Documents/BuiltPluginsTemp/UE%ueVersionToCopy%" "D:/Documents/BuiltPluginsTemp/UE%ueVersionToCopy%Rel"
echo Deleting built files from release folder
call RMDIR /s /q "D:/Documents/BuiltPluginsTemp/UE%ueVersionToCopy%Rel/Intermediate"
call RMDIR /s /q "D:/Documents/BuiltPluginsTemp/UE%ueVersionToCopy%Rel/Binaries"
echo Opening built files,
call start "" "D:/Documents/BuiltPluginsTemp/UE%ueVersionToCopy%Rel"
goto:eof

