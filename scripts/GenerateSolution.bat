@echo off
pushd %~dp0\..\
call tools\bin\premake\windows\premake5.exe vs2022
call tools\bin\premake\windows\premake5.exe export-compile-commands
popd
PAUSE
