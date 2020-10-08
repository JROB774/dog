:: Build Configuration Variables Script

@echo off

set Libraries=                                                              ^
SDL2main.lib SDL2.lib SDL2_mixer.lib opengl32.lib dinput8.lib dxguid.lib    ^
user32.lib gdi32.lib winmm.lib imm32.lib ole32.lib oleaut32.lib shell32.lib ^
version.lib uuid.lib advapi32.lib setupapi.lib dbghelp.lib setargv.obj

:: Can be either "x86" or "amd64"
set Architecture=amd64
:: Can be either "Debug" or "Release"
set BuildMode=Release

set IncludeDirs=-I ..\source\
set LibraryDirs=-libpath:..\library\win32\%Architecture%\

set Defines=

set CompilerFlags=-Zc:__cplusplus -std:c++17 -nologo -W4 -MT -Oi -GR- -EHsc -Z7
set LinkerFlags=-opt:ref -incremental:no

set CompilerWarnings=-wd4100 -wd4505 -wd4189
set LinkerWarnings=-ignore:4099

set ResourceFile=..\resource\resources.rc
set ResourcePath=..\resource\

set InputResource=..\resource\resources.res
set InputSource=..\source\main.cpp

set OutputExecutable=DOG-%Architecture%

if %BuildMode%==Release (
    set CompilerFlags=%CompilerFlags% -WX
    set LinkerFlags=%LinkerFlags% -subsystem:windows
)
if %BuildMode%==Debug (
    set OutputExecutable=%OutputExecutable%-Debug
    set Defines=%Defines% -DBUILD_DEBUG
    set InputResource=
    set LinkerFlags=%LinkerFlags% -subsystem:console
)

if %Architecture%==x86 (
    set CompilerFlags=%CompilerFlags% -arch:IA32
    set LinkerFlags=%LinkerFlags%,5.1
)
