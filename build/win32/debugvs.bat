:: Visual Studio Debugger Launch Script

@echo off
setlocal

pushd ..\..
call build\win32\utility\findvsdev.bat
call build\win32\utility\buildvars.bat
call %VSDevPath% -no_logo -arch=%Architecture%
devenv %OutputExecutable%.exe
popd

endlocal
