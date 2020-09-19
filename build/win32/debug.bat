:: RemedyBG Debugger Launch Script

@echo off
setlocal

pushd ..\..
call build\win32\utility\buildvars.bat
start remedybg binary\%OutputExecutable%.rdbg
popd

endlocal
