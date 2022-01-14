@echo off

:: This will be different for other people...
set EMSDKLocation=C:\.emsdk

set path=%path%;%~dp0

if not exist %EMSDKLocation% goto no_emscripten
pushd %EMSDKLocation%
call emsdk_env.bat
cls
popd
goto end

:no_emscripten
echo Emscripten could not be found, web builds cannot be made!
