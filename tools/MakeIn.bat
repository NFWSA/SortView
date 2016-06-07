@echo off
setlocal enabledelayedexpansion
set /p num=Please input data number:
(
echo]!num!
for /l %%a in (1, 1, !num!) do (
    set /a i=!random!%%690+1
    echo]!i!
)
)>in.txt
