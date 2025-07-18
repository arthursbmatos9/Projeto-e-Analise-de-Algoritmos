#include <iostream>
#include <cstdlib>

int main() {
    std::cout << "Iniciando execução do script BAT no Windows..." << std::endl;

    int result = std::system("executar_algoritmos.bat");

    if (result == 0) {
        std::cout << "Execução concluída com sucesso!" << std::endl;
    } else {
        std::cerr << "Erro ao executar o script. Código de retorno: " << result << std::endl;
    }

    return 0;
}

// g++ executar.cpp -o run_all

// .\run_all