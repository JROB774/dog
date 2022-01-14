@echo off
setlocal

call config.bat

pushd ..\..
if not exist %OutputPath% mkdir %OutputPath%
emcc %InputSource% %IncludeDirs% %Libraries% -std=c++17 --preload-file %AssetPath% -o %OutputName%
popd

endlocal
