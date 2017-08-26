@echo off
setlocal enabledelayedexpansion
set /p num=Please input data number:
set /p max=Please input max number:
set /a num+=0
set /a max+=0
(
echo]!num! !max!
for /l %%a in (1, 1, !num!) do (
    set /a i=!random!%%!max!+1
    echo]!i!
)
)>in.txt
