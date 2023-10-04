@echo off
pushd %~dp0\..\
call tools\bin\premake\windows\premake5.exe vs2022
popd
PAUSE