## 1. Como Executar

### Usando o Script `.bat`
1. Abra o terminal na pasta raiz do projeto.
2. Execute o comando:
   ```
   .\executar_algoritmos.bat
   ```

### Usando o Executável
1. Compile o arquivo `executar.cpp`:
   ```
   g++ executar.cpp -o run_all
   ```
2. Execute o programa:
   ```
   .\run_all
   ```

### Compilação Direta
- Para o `distancia_edicao`:
  ```
  g++ distancia_edicao\main.cpp -I distancia_edicao\include -std=c++17 -o tai_exec.exe
  .\tai_exec.exe
  ```
- Para o `zhang-shasha-f`:
  ```
  g++ zhang-shasha-f\main.cpp -I zhang-shasha-f\include -std=c++17 -o zhang_exec.exe
  .\zhang_exec.exe
  ```