#ifndef GRAPH_UTILS_H
#define GRAPH_UTILS_H

#include "graph.hpp"
#include <chrono>
#include <iostream>
#include <vector>

//metodo para criar um grafo semi euleriano (NÃO EH MAIS CICLICO)
inline Graph generateCycleGraph(int n_vertices) {
    if (n_vertices < 3) {
        std::cout << "Um grafo cíclico requer no mínimo 3 vértices. Usando 3 vértices." << std::endl;
        n_vertices = 3;
    }

    Graph g(n_vertices);

    for (int i = 0; i < n_vertices - 1; i++) {
        g.addEdge(i, i + 1);
    }

    //não fecha o ciclo para formar um semi euleriano
    //g.addEdge(n_vertices - 1, 0);

    std::cout << "Grafo gerado com sucesso!" << std::endl;
    return g;
}


inline void testPerformance(const std::vector<int> &vertices_list) {
    for (int n_vertices : vertices_list) {
        std::cout << "\n=================== Testando grafo com " << n_vertices << " vertices: ===================" << std::endl;
    
        Graph g = generateCycleGraph(n_vertices);
        std::cout << "\n======= Iniciando testes de performance ======="<< std::endl;
    
        //teste com metodo de Tarjan
        std::cout << "Executando metodo de Tarjan..." << std::endl;
        auto start = std::chrono::steady_clock::now();
        auto path_tarjan = g.fleury(true);
        auto end = std::chrono::steady_clock::now();
        auto tarjan_duration =
            std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
        std::cout << "Tempo: " << tarjan_duration.count() << " ms" << std::endl;
        std::cout << "Tamanho do caminho: " << path_tarjan.size() << std::endl;
    
        //teste com metodo Naive
        std::cout << "\nExecutando metodo Naive..." << std::endl;
        start = std::chrono::steady_clock::now();
        auto path_naive = g.fleury(false);
        end = std::chrono::steady_clock::now();
        auto naive_duration =
            std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
        std::cout << "Tempo: " << naive_duration.count() << " ms" << std::endl;
        std::cout << "Tamanho do caminho: " << path_naive.size() << std::endl;
    }
}

#endif 