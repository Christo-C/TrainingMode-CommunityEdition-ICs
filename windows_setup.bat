@echo off
setlocal

REM set directory to location of this file. Needed when drag n dropping across directories.
cd /d %~dp0

if not exist "D:/devkitPro/devkitPPC" (
    echo ERROR: devkitPro not found at "D:/devkitPro/devkitPPC"
    echo Please install devkitPro with the GameCube package
    goto end
) else (
    echo found devkitPro
    set "PATH=%PATH%;D:\devkitPro\devkitPPC\bin"
)

D:\devkitPro\msys2\msys2_shell.cmd -use-full-path -msys2 -here
exit 1

:end

REM pause if not run from command line
echo %CMDCMDLINE% | findstr /D:"/c">nul && pause
