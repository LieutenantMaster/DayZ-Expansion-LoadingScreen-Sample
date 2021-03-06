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
set modBuildDirectory=
set prefixLinkRoot=
set keyDirectory=
set keyName=

for /f "delims=" %%a in ('call ExtractData.bat ../project.cfg ../user.cfg WorkDrive') do (
	set workDrive=%%a
)

for /f "delims=" %%a in ('call ExtractData.bat ../project.cfg ../user.cfg LicensedModName') do (
	set modName=%%a
)

for /f "delims=" %%a in ('call ExtractData.bat ../project.cfg ../user.cfg ModBuildDirectory') do (
	set modBuildDirectory=%%a
)

for /f "delims=" %%a in ('call ExtractData.bat ../project.cfg ../user.cfg PrefixLinkRoot') do (
	set prefixLinkRoot=%%a
)

for /f "delims=" %%a in ('call ExtractData.bat ../project.cfg ../user.cfg KeyDirectory') do (
	set keyDirectory=%%a
)

for /f "delims=" %%a in ('call ExtractData.bat ../project.cfg ../user.cfg KeyName') do (
	set keyName=%%a
)

for /f "delims=" %%a in ('call ExtractData.bat ../project.cfg ../user.cfg ToolsDirectory') do (
	set dayzToolsPath=%%a
)

setlocal enableextensions enabledelayedexpansion

echo KeyDirectory is: "%keyDirectory%"
if "%keyDirectory%"=="" (
	set /a failed=1
	echo KeyDirectory parameter was not set in the project.cfg
)

echo KeyName is: "%keyName%"
if "%keyName%"=="" (
	set /a failed=1
	echo KeyName parameter was not set in the project.cfg
)

echo LicensedModName is: "%modName%"
if "%modName%"=="" (
	set /a failed=1
	echo LicensedModName parameter was not set in the project.cfg
)

echo WorkDrive is: "%workDrive%"
if "%workDrive%"=="" (
	set /a failed=1
	echo WorkDrive parameter was not set in the project.cfg
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

echo Searching for DayZ Tools...
for /F "Tokens=2* skip=2" %%A In ('REG QUERY "HKCU\Software\bohemia interactive\Dayz Tools" /v "Path" 2^>nul') do (set _DAYZTOOLSPATH=%%B)
if not defined _DAYZTOOLSPATH (
	echo DayZ Tools was not set in the registry path, trying default.
	set "_DAYZTOOLSPATH=D:\Program Files (x86)\Steam\steamapps\common\DayZ Tools"
) else (
	echo Found.
)

set _DAYZTOOLSPATH=%_DAYZTOOLSPATH:"=%
set _MIKEDLL=%_MIKEDLL:"=%

if %failed%==1 (
	endlocal

	echo Failed to package the mod.
	goto:eof
)

set pboProject="%_MIKEDLL%\bin\pboProject.exe"
set signFile="%_DAYZTOOLSPATH%\Bin\DsUtils\DSSignFile.exe"

IF exist "%modBuildDirectory%%modName%\" (
	echo Removing folder "%modBuildDirectory%%modName%\"
	rmdir /S /Q "%modBuildDirectory%%modName%\"
)

IF NOT exist "%modBuildDirectory%%modName%\" (
	echo Creating folder "%modBuildDirectory%%modName%\"
	mkdir "%modBuildDirectory%%modName%\"
)

IF NOT exist "%modBuildDirectory%%modName%\Addons\" (
	echo Creating folder "%modBuildDirectory%%modName%\Addons\"
	mkdir "%modBuildDirectory%%modName%\Addons\"
)

IF NOT exist "%modBuildDirectory%%modName%\Keys\" (
	echo Creating folder "%modBuildDirectory%%modName%\Keys\"
	mkdir "%modBuildDirectory%%modName%\Keys\"
)

IF NOT exist "%modBuildDirectory%%modName%\Addons\" (
	echo %modBuildDirectory%%modName%\Addons\ does not exist
	exit
)

echo Copying over "%workDrive%%prefixLinkRoot%\mod_licenced.cpp" to "%modBuildDirectory%%modName%\" and renaming to "mod.cpp"
copy "%workDrive%%prefixLinkRoot%\mod_licenced.cpp" "%modBuildDirectory%%modName%\" > nul
rename "%modBuildDirectory%%modName%\mod_licenced.cpp" "mod.cpp"

echo Copying over "%keyDirectory%\%keyName%.bikey" to "%modBuildDirectory%%modName%\Keys\"
copy "%keyDirectory%%keyName%.bikey" "%modBuildDirectory%%modName%\Keys\" > nul

echo Packaging %modName% PBO's

@echo off

cd /D "%workDrive%%prefixLinkRoot%\"

set compression=-Z

for /R %%D in ( config.cpp ) do (
	echo Checking directory %%~dD%%~pD, searching for config.cpp
	IF EXIST "%%~dD%%~pDconfig.cpp" (
		IF NOT EXIST "%%~dD%%~pDIGNORE" (
			IF EXIST "%%~dD%%~pDLICENSED" (
				IF NOT EXIST "%%~dD%%~pD..\config.cpp" (
					IF NOT EXIST "%%~dD%%~pD..\..\config.cpp" (
						IF NOT EXIST "%%~dD%%~pD..\..\..\config.cpp" (
							IF NOT EXIST "%%~dD%%~pD..\..\..\..\config.cpp" (
								IF NOT EXIST "%%~dD%%~pD..\..\..\..\..\config.cpp" (
									IF NOT EXIST "%%~dD%%~pD..\..\..\..\..\..\config.cpp" (
										IF NOT EXIST "%%~dD%%~pD..\..\..\..\..\..\..\config.cpp" (
											IF NOT EXIST "%%~dD%%~pD..\..\..\..\..\..\..\..\config.cpp" (
												rem echo No parent config.cpp found, building pbo %%D

												set folderToBuild=%%~pD
												
												set pboName=%%~pD
												IF !pboName:~-1!==\ SET pboName=!pboName:~0,-1!
												set pboName=!pboName:\%prefixLinkRoot%\=!
												set pboName=!pboName:\=_!

												set prefixName=%%~pD
												IF !prefixName:~-1!==\ SET prefixName=!prefixName:~0,-1!
												set prefixName=!prefixName:\%prefixLinkRoot%\=!
												set prefixName=%prefixLinkRoot%\!prefixName!

												set sourcePath=%workDrive%!prefixName!

												echo Packing "!pboName!.pbo"

												set currentFolder=
												for %%I in ( !folderToBuild!\config.cpp\.. ) do (
													set "currentFolder=%%~nxI"
												)

												START /w %pboProject% %pboProject% +W -F +Stop -P %compression% -O -E=dayz +R "%workDrive%!prefixName!" "+Mod=%modBuildDirectory%%modName%" "-Key"
												
												if errorlevel 1 (
													echo /////////////////////////////////////////////////////////////
													echo Something went wrong with %%D for !pboName!.pbo - Skipping the pbo packing. Copying the log to %workDrive%%prefixLinkRoot%\Workbench\Logs\
													echo /////////////////////////////////////////////////////////////

													set packingLog="%workDrive%Temp\!currentFolder!.packing.log"
													set binLog="%workDrive%Temp\!currentFolder!.bin.log"

													IF exist !packingLog! (
														copy !packingLog! "%workDrive%%prefixLinkRoot%\Workbench\Logs\" > nul
														rename "%workDrive%%prefixLinkRoot%\Workbench\Logs\!packingLog!" "!pboName!.packing.log"
													)

													IF exist !binLog! (
														copy !binLog! "%workDrive%%prefixLinkRoot%\Workbench\Logs\" > nul
														rename "%workDrive%%prefixLinkRoot%\Workbench\Logs\!binLog!" "!pboName!.bin.log"
													)
												) else (
													cd /D "%modBuildDirectory%%modName%\Addons\"

													echo Renaming PBO to %modBuildDirectory%%modName%\Addons\!pboName!.pbo
													rename "%modBuildDirectory%%modName%\Addons\!currentFolder!.pbo" "!pboName!.pbo"

													%signFile% "%keyDirectory%%keyName%.biprivatekey" "%modBuildDirectory%%modName%\Addons\!pboName!.pbo"
												)

												cd /D "%workDrive%%prefixLinkRoot%\"
											)
										)
									)
								)
							)
						)
					)
				)
			)
		) else (
			echo PBO set to ignore, skipping.
		)
	)
)

goto end

:end
endlocal