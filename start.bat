prompt $T $P$_$N$G
pushd %~dp0
SETLOCAL EnableExtensions
SETLOCAL EnableDelayedExpansion

set GYP_MSVS_VERSION=2015

@echo on
if %GYP_MSVS_VERSION% equ 2010 set version=10.0
if %GYP_MSVS_VERSION% equ 2013 set version=12.0
if %GYP_MSVS_VERSION% equ 2015 set version=14.0
ECHO version=%version%

@echo on
for %%d in (
	"%ProgramFiles%"
	"%ProgramW6432%"
	"C:\Program Files"
	"C:\Program Files (x86)"
	"D:\Program Files"
	"D:\Program Files (x86)"
) do (
	if exist "%%~d\Microsoft Visual Studio %version%\Common7\IDE\devenv.exe" SET VCINSTALLDIR=%%~d\Microsoft Visual Studio %version%
)

@echo on

ECHO environment: 
ECHO ======================================================================
ECHO VCINSTALLDIR=%VCINSTALLDIR%
ECHO COVERAGEBINDIR=%COVERAGEBINDIR%
ECHO PYTHONDIR=%PYTHONDIR%
ECHO BROWSER VERSION=%MAJOR_VER%.%MINOR_VER%
ECHO BROWSER STAGE=%STAGE_TEXT%
ECHO ======================================================================
ECHO.

SET VSINSTALLDIR=%VCINSTALLDIR%\Common7\IDE
SET temp=%USERPROFILE%\AppData\Local\Temp

set DevEnvDir=%VSINSTALLDIR%
set MSVCDir=%VCINSTALLDIR%\VC

set workspace=%~dp0
set depot_tools_path=%workspace%..\common\depot_tools
set python_path=%depot_tools_path%\python276_bin

set PATH=%depot_tools_path%;%python_path=%;%MicroSoftSDKDir%\bin;%DevEnvDir%;%MSVCDir%\BIN;%VCINSTALLDIR%\Common7\Tools;%VCINSTALLDIR%\Common7\Tools\bin\prerelease;%VCINSTALLDIR%\Common7\Tools\bin;%PATH%;

@echo off

echo GYP_DEFINES:%GYP_DEFINES%

start devenv.exe .\out\debug\all.sln
exit /b 0