@echo off
rem set /p fname="Enter file name: "
rem @title = %fname%
:start
g++ main.cpp order.cpp table.cpp restaurant.cpp -std=c++11 -o main
main
pause
cls
goto start
