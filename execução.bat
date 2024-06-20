@echo off
cls
echo Compiling Principal.c and Pilha.c...
gcc Principal.c Pilha.c -o Principal.exe

if errorlevel 1 (
    echo.
    echo Compilation failed.
    pause > nul
    exit /b
)

echo Compilation successful!
echo Executing Principal.exe...
Principal.exe

echo.
echo Press any key to continue...
pause > nul
