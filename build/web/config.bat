@echo off

set AssetPath=assets
set IncludeDirs=-I source\
set Libraries=-s USE_SDL=2 -s USE_SDL_MIXER=2
set InputSource=source\main_web.cpp
set OutputPath=binary\web\
set OutputName=%OutputPath%dog.html
