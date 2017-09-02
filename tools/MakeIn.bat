@echo off
setlocal enabledelayedexpansion
set /p num=Please input data number:
set /p max=Please input max number:
set /a num+=0
set /a max+=1
(
echo]!num! !max!
for /l %%a in (1, 1, !num!) do (
    set /a i=!random!%%!max!
    echo]!i!
)
)>in.txt
