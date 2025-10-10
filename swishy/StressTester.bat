@echo off
g++ -std=c++20 -o solution test.cpp
g++ -std=c++20 -o brute brute.cpp
g++ -std=c++20 -o gen gen.cpp

for /l %%x in (1, 1, 1000) do (
    gen > input.in
    solution < input.in > output.out
    brute < input.in > output2.out
    fc output.out output2.out > nul

    if ERRORLEVEL 1 (
        echo INPUT
        type input.in
        echo.
        echo SOLUTION OUTOUT
        type output.out
        echo.
        echo CORRECT OUTPUT
        type output2.out
        echo.
    )
)
echo all tests passed