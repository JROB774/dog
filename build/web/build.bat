:: Build Process Script

@echo off
setlocal

set IncludeDirs=-I source\
set Libraries=-s USE_SDL=2 -s USE_SDL_MIXER=2
set InputSource=source\main_web.cpp
set OutputPath=binary\web\
set OutputName=%OutputPath%dog.html

pushd ..\..
if not exist %OutputPath% mkdir %OutputPath%
emcc %InputSource% %IncludeDirs% %Libraries% -o %OutputName%
popd

endlocal
