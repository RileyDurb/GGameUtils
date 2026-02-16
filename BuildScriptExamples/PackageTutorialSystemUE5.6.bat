@echo off
echo Starting GG Tutorial System Plugin Build for UE 5.6

"D:/Program Files/Epic Games/UE_5.6/Engine/Build/BatchFiles/RunUAT.bat" BuildPlugin -plugin="D:/GameSystemProjects/GGameUtils/GGameUtils/Plugins/GGameUtilsTutorialSystem/GGameUtilsTutorialSystem.uplugin" -package="D:/Documents/GGameUtilsTutorialSystem"
echo Build process finished, see above for results
pause