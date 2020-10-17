:: Output Program Execution Script

@echo off
setlocal

pushd ..\..
call build\win32\utility\buildvars.bat
pushd %OutputPath%
%OutputName%.exe
popd
popd

endlocal
