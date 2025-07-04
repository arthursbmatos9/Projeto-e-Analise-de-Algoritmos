#include "include/Tree.hpp"
#include "src/ZhangShashaTreeEditDistance.hpp"
#include <iostream>

// CASO PRINCIPAL DO ARTIGO ZHANG-SHASHA (Figura 4)
void criarCasoPrincipalArtigo(Tree<char>& tree1, Tree<char>& tree2) {
    // T₁: f(d(a,c(b)), e)
    tree1 = Tree<char>('f');        
    tree1.adicionarFilho('f', 'd'); // d primeiro filho de f
    tree1.adicionarFilho('f', 'e'); // e segundo filho de f
    tree1.adicionarFilho('d', 'a'); // a primeiro filho de d
    tree1.adicionarFilho('d', 'c'); // c segundo filho de d
    tree1.adicionarFilho('c', 'b'); // b filho de c

    // T₂: f(c(d(a,b)), e)
    tree2 = Tree<char>('f');        
    tree2.adicionarFilho('f', 'c'); // c primeiro filho de f
    tree2.adicionarFilho('f', 'e'); // e segundo filho de f
    tree2.adicionarFilho('c', 'd'); // d filho de c
    tree2.adicionarFilho('d', 'a'); // a primeiro filho de d
    tree2.adicionarFilho('d', 'b'); // b segundo filho de d
}

// TESTE 1: Árvores Idênticas
void criarArvoresIdenticas(Tree<char>& tree1, Tree<char>& tree2) {
    tree1 = Tree<char>('a');
    tree2 = Tree<char>('a');
    // Adiciona 10 filhos de 'a' em ambas as árvores
    for (char c = 'b'; c <= 'k'; ++c) {
        tree1.adicionarFilho('a', c);
        tree2.adicionarFilho('a', c);
    }
}

// TESTE 2: Apenas Raiz
void criarApenaRaiz(Tree<char>& tree1, Tree<char>& tree2) {
    tree1 = Tree<char>('a');
    tree2 = Tree<char>('b');
}

// TESTE 3: String Linear
void criarStringLinear(Tree<char>& tree1, Tree<char>& tree2) {
    tree1 = Tree<char>('a');
    tree1.adicionarFilho('a', 'b');
    tree1.adicionarFilho('b', 'c');
    
    tree2 = Tree<char>('a');
    tree2.adicionarFilho('a', 'd');
    tree2.adicionarFilho('d', 'c');
}

// TESTE 4: Caso Complexo
void criarCasoComplexo(Tree<char>& tree1, Tree<char>& tree2) {
    int n = 1000;
    std::vector<char> labels;
    for (int i = 0; i < n; ++i)
        labels.push_back('0' + (i % 10)); // repetição de números '0' a '9'

    // Criando tree1 com estrutura em árvore binária
    tree1 = Tree<char>(labels[0]);
    for (int i = 1; i < n; ++i) {
        int parent = (i - 1) / 2; // pai na árvore binária
        tree1.adicionarFilho(labels[parent], labels[i]);
    }

    // Criando tree2 reorganizando filhos
    tree2 = Tree<char>(labels[0]);
    for (int i = n - 1; i > 0; --i) {
        int parent = (i - 1) / 2;
        tree2.adicionarFilho(labels[parent], labels[i]);
    }
}

// TESTE 5: Árvores Originais do GUI
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

void testarCasoPrincipalArtigo() {
    std::cout << "\n=== CASO PRINCIPAL DO ARTIGO (Esperado: 2) ===" << std::endl;
    
    Tree<char> tree1, tree2;
    criarCasoPrincipalArtigo(tree1, tree2);
    
    try {
        double distancia = zhangShashaDistance(tree1, tree2);
        std::cout << "Resultado: " << distancia << std::endl;
    } catch (const std::exception& e) {
        std::cout << "ERRO: " << e.what() << std::endl;
    }
}

void testarArvoresIdenticas() {
    std::cout << "\n=== ARVORES IDENTICAS (Esperado: 0) ===" << std::endl;
    
    Tree<char> tree1, tree2;
    criarArvoresIdenticas(tree1, tree2);
    
    try {
        double distancia = zhangShashaDistance(tree1, tree2);
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
        double distancia = zhangShashaDistance(tree1, tree2);
        std::cout << "Resultado: " << distancia << std::endl;
    } catch (const std::exception& e) {
        std::cout << "ERRO: " << e.what() << std::endl;
    }
}

void testarStringLinear() {
    std::cout << "\n=== STRING LINEAR (Esperado: 1) ===" << std::endl;
    
    Tree<char> tree1, tree2;
    criarStringLinear(tree1, tree2);
    
    try {
        double distancia = zhangShashaDistance(tree1, tree2);
        std::cout << "Resultado: " << distancia << std::endl;
    } catch (const std::exception& e) {
        std::cout << "ERRO: " << e.what() << std::endl;
    }
}

void testarCasoComplexo() {
    std::cout << "\n=== CASO COMPLEXO ===" << std::endl;
    
    Tree<char> tree1, tree2;
    criarCasoComplexo(tree1, tree2);
    
    try {
        double distancia = zhangShashaDistance(tree1, tree2);
        std::cout << "Resultado: " << distancia << std::endl;
    } catch (const std::exception& e) {
        std::cout << "ERRO: " << e.what() << std::endl;
    }
}

void testarOriginal() {
    std::cout << "\n=== TESTE ORIGINAL (igual o do gui, tem que dar 4)===" << std::endl;
    
    Tree<int> tree1, tree2;
    criarArvoresParaTeste(tree1, tree2);
    
    try {
        double distancia = zhangShashaDistance(tree1, tree2);
        std::cout << "Resultado: " << distancia << std::endl;
    } catch (const std::exception& e) {
        std::cout << "ERRO: " << e.what() << std::endl;
    }
}


int main() {
    std::cout << "TESTANDO ZHANG-SHASHA" << std::endl;
    
    testarCasoPrincipalArtigo();
    testarArvoresIdenticas();
    testarApenaRaiz();
    testarStringLinear();
    testarCasoComplexo();
    testarOriginal();

    return 0;
}
