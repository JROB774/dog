@echo off
setlocal

call config.bat

pushd ..\..
cd %OutputPath%
start python -m http.server
popd

endlocal
