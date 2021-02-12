@echo off

cd /D "%~dp0"

set batchDirectory=%cd%

set /a failed=0

if exist ../project.cfg (
	echo Found the project.cfg
) else (
	echo Failed to find the project.cfg file, exitting.
	set /a failed=1
)

if exist ../user.cfg (
	echo Found the user.cfg
) else (
	echo Failed to find the user.cfg file, exitting.
	set /a failed=1
)

if %failed%==1 (
	endlocal

	echo Failed to package the mod.
	goto:eof
)

set githubDirectory=%cd%\
set workbenchDataDirectory=%githubDirectory%Workbench\
set toolsDirectory=%workbenchDataDirectory%Tools\

set workDrive=
set modName=
set modNameLicensed=
set modBuildDirectory=
set prefixLinkRoot=
set versionFileLocation=

for /f "delims=" %%a in ('call ExtractData.bat ../project.cfg ../user.cfg WorkDrive') do (
	set workDrive=%%a
)

for /f "delims=" %%a in ('call ExtractData.bat ../project.cfg ../user.cfg ModName') do (
	set modName=%%a
)

for /f "delims=" %%a in ('call ExtractData.bat ../project.cfg ../user.cfg LicensedModName') do (
	set modNameLicensed=%%a
)

for /f "delims=" %%a in ('call ExtractData.bat ../project.cfg ../user.cfg ModBuildDirectory') do (
	set modBuildDirectory=%%a
)

for /f "delims=" %%a in ('call ExtractData.bat ../project.cfg ../user.cfg PrefixLinkRoot') do (
	set prefixLinkRoot=%%a
)

for /f "delims=" %%a in ('call ExtractData.bat ../project.cfg ../user.cfg VersionFileLocation') do (
    set versionFileLocation=%%a
)

setlocal enableextensions enabledelayedexpansion

echo WorkDrive is: "%workDrive%"
if "%workDrive%"=="" (
	set /a failed=1
	echo WorkDrive parameter was not set in the project.cfg
)

echo ModName is: "%modName%"
if "%modName%"=="" (
	set /a failed=1
	echo ModName parameter was not set in the project.cfg
)

echo LicensedModName is: "%modNameLicensed%"
if "%modNameLicensed%"=="" (
	set /a failed=1
	echo LicensedModName parameter was not set in the project.cfg
)

echo ModBuildDirectory is: "%modBuildDirectory%"
if "%modBuildDirectory%"=="" (
	set /a failed=1
	echo ModBuildDirectory parameter was not set in the project.cfg
)

echo PrefixLinkRoot is: "%prefixLinkRoot%"
if "%prefixLinkRoot%"=="" (
	set /a failed=1
	echo PrefixLinkRoot parameter was not set in the project.cfg
)

echo VersionFileLocation is: "%versionFileLocation%"
if "%versionFileLocation%"=="" (
    set /a failed=1
    echo VersionFileLocation parameter was not set in the project.cfg
)

echo Searching for Mikero Tools...
for /F "Tokens=2* skip=2" %%A In ('REG QUERY "HKCU\SOFTWARE\Mikero\depbo" /v "path" 2^>nul') do (set _MIKEDLL=%%B)
if not defined _MIKEDLL (
	for /F "Tokens=2* skip=2" %%A In ('REG QUERY "HKLM\SOFTWARE\Mikero\depbo" /v "path" 2^>nul') do (set _MIKEDLL=%%B)
	if not defined _MIKEDLL (
		echo Mikero Tools was not set in the registry path, trying default.
		set "_MIKEDLL=C:\Program Files (x86)\Mikero\DePboTools"
	) else (
		echo Found.
	)
) else (
	echo Found.
)

set _MIKEDLL=%_MIKEDLL:"=%

set extractpbodos="%_MIKEDLL%\bin\extractpbodos.exe"
set derap="%_MIKEDLL%\bin\derap.exe"

echo removing DZEXPANSION....
if exist "P:\DZEXPANSION" (rmdir /s/q "P:\DZEXPANSION")
if ERRORLEVEL 1 goto:eof

echo removing DZEXPANSIONLICENSED....
if exist "P:\DZEXPANSIONLICENSED" (rmdir /s/q "P:\DZEXPANSIONLICENSED")
if ERRORLEVEL 1 goto:eof

extractpbodos -p "%modBuildDirectory%%modName%\Addons" P:\DZEXPANSION
extractpbodos -p "%modBuildDirectory%%modNameLicensed%\Addons" P:\DZEXPANSIONLICENSED

set gitDiffDirectory=%1

cd /d %gitDiffDirectory%

git checkout %2
git pull origin %2

rmdir /s/q "%gitDiffDirectory%\DayZExpansion"
del /S /Q "%gitDiffDirectory%\DayZExpansion"

cd /d %workDrive%/DZEXPANSION
for /R %%D in ( config.cpp ) do (
     IF EXIST "%%D" (
        set _CONFIG=%%~fD
        set _PREFIX=%%~pD

        set _PREFIX=!_PREFIX:\DZEXPANSION=!

        mkdir %gitDiffDirectory%\!_PREFIX!

        Powershell -ExecutionPolicy ByPass -command "&'%gitDiffDirectory%\HandleConfig.ps1'" "!_CONFIG!"

        xcopy /Y !_CONFIG! %gitDiffDirectory%\!_PREFIX!
     )
)

cd /d %workDrive%/DZEXPANSIONLICENSED
for /R %%D in ( config.cpp ) do (
     IF EXIST "%%D" (
        set _CONFIG=%%~fD
        set _PREFIX=%%~pD

        set _PREFIX=!_PREFIX:\DZEXPANSIONLICENSED=!

        mkdir %gitDiffDirectory%\!_PREFIX!

        Powershell -ExecutionPolicy ByPass -command "&'%gitDiffDirectory%\HandleConfig.ps1'" "!_CONFIG!"

        xcopy /Y !_CONFIG! %gitDiffDirectory%\!_PREFIX!
     )
)

echo Addons done... Moving onto dta...

xcopy /Y /S /Q "P:\DZEXPANSION\DayZExpansion\Scripts" "%gitDiffDirectory%\DayZExpansion\Scripts\"
xcopy /Y /S /Q "P:\DZEXPANSION\DayZExpansion\GUI" "%gitDiffDirectory%\DayZExpansion\GUI\"

for /f "delims=" %%x in (%workDrive%%versionFileLocation%) do set version=%%x

cd /d %gitDiffDirectory%

echo git add -A
git add -A
echo git commit -m "Updated to version %version%"
git commit -m "Updated to version %version%"
echo git push origin %2
git push origin %2