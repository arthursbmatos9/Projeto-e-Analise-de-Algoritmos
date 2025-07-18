#include <iostream>
#include <chrono>
#include <vector>
#include "include/Tree.hpp"
#include "src/TreeEditDistance.hpp"

void criarArvoreGrande(Tree<char>& tree, int n) {
    std::vector<char> labels;
    for (int i = 0; i < n; ++i)
        labels.push_back('0' + (i % 10)); 

    tree = Tree<char>(labels[0]);
    for (int i = 1; i < n; ++i) {
        int parent = (i - 1) / 2;
        tree.adicionarFilho(labels[parent], labels[i]);
    }
}

void criarArvoreGrandeDiferente(Tree<char>& tree, int n) {
    std::vector<char> labels;
    for (int i = 0; i < n; ++i)
        labels.push_back('0' + (i % 10));

    tree = Tree<char>(labels[0]);
    for (int i = n - 1; i > 0; --i) {
        int parent = (i - 1) / 2;
        tree.adicionarFilho(labels[parent], labels[i]);
    }
}

void testarEscalabilidade() {
    std::cout << "\n=== ESCALABILIDADE ===\n";

    std::vector<int> tamanhos = {10, 50, 100, 200, 400, 800, 1600};  

    for (int n : tamanhos) {
        Tree<char> tree1, tree2;
        criarArvoreGrande(tree1, n);               
        criarArvoreGrandeDiferente(tree2, n);      

        std::cout << "\nTamanho das árvores: " << n << std::endl;

        auto inicio = std::chrono::high_resolution_clock::now();
        double distancia = TED(tree1, tree2);  
        auto fim = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> duracao = fim - inicio;
        std::cout << "Distância ALGORITIMO DINAMICO " << distancia << std::endl;
        std::cout << "Tempo (s): " << duracao.count() << std::endl;
    }
}

void criarArvoresIdenticas(Tree<char>& tree1, Tree<char>& tree2) {
    tree1 = Tree<char>('a');
    tree2 = Tree<char>('a');
    
    for (char c = 'b'; c <= 'k'; ++c) {
        tree1.adicionarFilho('a', c);
        tree2.adicionarFilho('a', c);
    }
}

void criarApenaRaiz(Tree<char>& tree1, Tree<char>& tree2) {
    tree1 = Tree<char>('a');
    tree2 = Tree<char>('b');
}

void criarCasoComplexo(Tree<char>& tree1, Tree<char>& tree2) {
    int n = 1000;
    std::vector<char> labels;
    for (int i = 0; i < n; ++i)
        labels.push_back('0' + (i % 10)); 

    
    tree1 = Tree<char>(labels[0]);
    for (int i = 1; i < n; ++i) {
        int parent = (i - 1) / 2; 
        tree1.adicionarFilho(labels[parent], labels[i]);
    }

    
    tree2 = Tree<char>(labels[0]);
    for (int i = n - 1; i > 0; --i) {
        int parent = (i - 1) / 2;
        tree2.adicionarFilho(labels[parent], labels[i]);
    }
}

void criarArvoresParaTeste(Tree<int>& tree1, Tree<int>& tree2) {
    
    tree1 = Tree<int>(1);        
    tree1.adicionarFilho(1, 2);  
    tree1.adicionarFilho(1, 3);  
    tree1.adicionarFilho(2, 4);  
    tree1.adicionarFilho(2, 5);  

    
    tree2 = Tree<int>(1);        
    tree2.adicionarFilho(1, 2);  
    tree2.adicionarFilho(1, 6);  
    tree2.adicionarFilho(6, 5);  
}

void testarArvoresIdenticas() {
    std::cout << "\n=== ARVORES IDENTICAS (Esperado: 0) ===" << std::endl;
    
    Tree<char> tree1, tree2;
    criarArvoresIdenticas(tree1, tree2);
    
    try {
        double distancia = TED(tree1, tree2);
        std::cout << "Resultado: " << distancia << std::endl;
    } catch (const std::exception& e) {
        std::cout << "ERRO: " << e.what() << std::endl;
    }
}

void testarApenaRaiz() {
    std::cout << "\n=== APENAS RAIZ (Esperado: 1) ===" << std::endl;
    
    Tree<char> tree1, tree2;
    criarApenaRaiz(tree1, tree2);
    
    try {
        double distancia = TED(tree1, tree2);
        std::cout << "Resultado: " << distancia << std::endl;
    } catch (const std::exception& e) {
        std::cout << "ERRO: " << e.what() << std::endl;
    }
}

void criarStringLinear(Tree<char>& tree1, Tree<char>& tree2) {
    tree1 = Tree<char>('a');
    tree1.adicionarFilho('a', 'b');
    tree1.adicionarFilho('b', 'c');
    
    tree2 = Tree<char>('a');
    tree2.adicionarFilho('a', 'd');
    tree2.adicionarFilho('d', 'c');
}

void testarStringLinear() {
    std::cout << "\n=== STRING LINEAR (Esperado: 1) ===" << std::endl;
    
    Tree<char> tree1, tree2;
    criarStringLinear(tree1, tree2);
    
    try {
        double distancia = TED(tree1, tree2);
        std::cout << "Resultado: " << distancia << std::endl;
    } catch (const std::exception& e) {
        std::cout << "ERRO: " << e.what() << std::endl;
    }
}

void testarArvores_4x5() {

    std::cout << "\n=== TESTE: ÁRVORES COM 4 E 5 VÉRTICES ===" << std::endl;


    std::cout << "1. Árvore 4 nós – ramo profundo\n";
    Tree<char> tree1('a');
    tree1.adicionarFilho('a', 'b');
    tree1.adicionarFilho('b', 'c');
    tree1.adicionarFilho('c', 'd');
    

    
    std::cout << "2. Árvore 5 nós – assimétrica\n";
    Tree<char> tree2('a');
    tree2.adicionarFilho('a', 'b');
    tree2.adicionarFilho('a', 'c');
    tree2.adicionarFilho('c', 'd');
    tree2.adicionarFilho('c', 'e');

    try {
        double distancia = TED(tree1, tree2);
        std::cout << "Distância ALGORITIMO DINAMICO " << distancia << std::endl;
    } catch (const std::exception& e) {
        std::cout << "ERRO: " << e.what() << std::endl;
    }
}

void testarArvores_6x7() {
    std::cout << "\n=== TESTE: ÁRVORES COM 6 E 7 VÉRTICES ===" << std::endl;
    std::cout << "3. Árvore 6 nós – balanceada em largura\n";
    Tree<char> tree3('a');
    tree3.adicionarFilho('a', 'b');
    tree3.adicionarFilho('a', 'c');
    tree3.adicionarFilho('b', 'd');
    tree3.adicionarFilho('c', 'e');
    tree3.adicionarFilho('c', 'f');
    

    
    std::cout << "4. Árvore 7 nós – binária completa\n";
    Tree<char> tree4('a');
    tree4.adicionarFilho('a', 'b');
    tree4.adicionarFilho('a', 'c');
    tree4.adicionarFilho('b', 'd');
    tree4.adicionarFilho('b', 'e');
    tree4.adicionarFilho('c', 'f');
    tree4.adicionarFilho('c', 'g');

    try {
        double distancia = TED(tree3, tree4);
        std::cout << "Distância ALGORITIMO DINAMICO " << distancia << std::endl;
    } catch (const std::exception& e) {
        std::cout << "ERRO: " << e.what() << std::endl;
    }
}

int main() {
    std::cout << "TESTANDO ALGORITMO DINAMICO" << std::endl;
    
    testarArvoresIdenticas();
    testarApenaRaiz();
    testarStringLinear();

    testarEscalabilidade();
    testarArvores_4x5();
    testarArvores_6x7();

    return 0;
}