:: Source Code Line Count Launcher Script

@echo off
setlocal

pushd ..\..\tools
python linecount.py -d -r -e ../source/SDL2/ -e ../source/GON/ ../source/
popd

endlocal
