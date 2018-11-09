@echo off
for /f "delims=" %%a in ('dir /b *.jpg') do ren "%%a" "#%%a"
for /f "delims=" %%i in ('dir /b *.jpg') do (
call :label "%%i"
)
pause&exit
:label
set /a n=%random%%%102+1
if not defined %n% (
set %n%=%n%
ren "%~1" "%n%.jpg"
) else (
goto :label
)
goto :eof