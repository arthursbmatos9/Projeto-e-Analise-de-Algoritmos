@echo off

echo Compilando e executando distancia_edicao...
g++ distancia_edicao\main.cpp -I distancia_edicao\include -o tai_exec.exe
tai_exec.exe

echo -----------------------------------------------------------------------

echo Compilando e executando Zhang-Shasha-f...
g++ zhang-shasha-f\main.cpp -I zhang-shasha-f\include -o zhang_exec.exe
zhang_exec.exe
