@echo off

echo Compilando e executando Tai_algorithm...
g++ Tai_algorithm\main.cpp -I Tai_algorithm\include -o tai_exec.exe
tai_exec.exe

echo -----------------------------------------------------------------------

echo Compilando e executando Zhang-Shasha-f...
g++ zhang-shasha-f\main.cpp -I zhang-shasha-f\include -o zhang_exec.exe
zhang_exec.exe
