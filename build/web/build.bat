:: Build Process Script

@echo off
setlocal

set InputSource=source\main_web.cpp
set OutputPath=binary\web\
set OutputName=%OutputPath%dog.html

pushd ..\..
if not exist %OutputPath% mkdir %OutputPath%
emcc %InputSource% -o %OutputName%
popd

endlocal
