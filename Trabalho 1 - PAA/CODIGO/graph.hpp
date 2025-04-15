#ifndef GRAPH_H
#define GRAPH_H

#include <algorithm>
#include <list>
#include <vector>
#include <utility>

class Graph {
private:
    int V;
    std::vector<std::list<int>> adj;
    int time;

    //funcao auxiliar para DFS
    void DFSUtil(int v, std::vector<bool> &visited) {
        visited[v] = true;
        for (int u : adj[v]) {
            if (!visited[u]) {
                DFSUtil(u, visited);
            }
        }
    }

    //funcao auxiliar para o algoritmo de Tarjan
    void bridgeUtil(int u, std::vector<bool> &visited, std::vector<int> &disc, std::vector<int> &low, std::vector<int> &parent, std::vector<std::pair<int, int>> &bridges) {
        visited[u] = true;
        disc[u] = low[u] = ++time;

        for (int v : adj[u]) {
            if (!visited[v]) {
                parent[v] = u;
                bridgeUtil(v, visited, disc, low, parent, bridges);
                low[u] = std::min(low[u], low[v]);

                if (low[v] > disc[u]) {
                    bridges.push_back({u, v});
                }
            } else if (v != parent[u]) {
                low[u] = std::min(low[u], disc[v]);
            }
        }
    }

public:
    Graph(int vertices) : V(vertices) {
        adj.resize(vertices);
        time = 0;
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void removeEdge(int u, int v) {
        adj[u].remove(v);
        adj[v].remove(u);
    }

    bool isConnected() {
        std::vector<bool> visited(V, false);
        int i;
        for (i = 0; i < V; i++) {
            if (!adj[i].empty()) {
                break;
            }
        }
        if (i == V) {
            return true;
        }
        DFSUtil(i, visited);
        for (i = 0; i < V; i++) {
            if (!visited[i] && !adj[i].empty()) {
                return false;
            }
        }
        return true;
    }

    //método Naive para verificar se uma aresta é ponte
    bool isBridgeNaive(int u, int v) {
        removeEdge(u, v);
        bool connected = isConnected();
        addEdge(u, v);
        return !connected;
    }

    //encontrar todas as pontes usando método Naive
    std::vector<std::pair<int, int>> findBridgesNaive() {
        std::vector<std::pair<int, int>> bridges;
        for (int u = 0; u < V; u++) {
            std::list<int> temp = adj[u];
            for (int v : temp) {
                if (u < v) {
                    if (isBridgeNaive(u, v)) {
                        bridges.push_back({u, v});
                    }
                }
            }
        }
        return bridges;
    }

    //encontrar todas as pontes usando algoritmo de Tarjan
    std::vector<std::pair<int, int>> findBridgesTarjan() {
        std::vector<bool> visited(V, false);
        std::vector<int> disc(V);
        std::vector<int> low(V);
        std::vector<int> parent(V, -1);
        std::vector<std::pair<int, int>> bridges;
        time = 0;

        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                bridgeUtil(i, visited, disc, low, parent, bridges);
            }
        }
        return bridges;
    }

    //algoritmo de Fleury para encontrar caminho euleriano
    std::vector<int> fleury(bool useTarjan = true) {
        std::vector<int> path;
        int oddCount = 0;
        int startVertex = 0;

        //encontra vértice inicial (caso haja algum vertice de grau impar, o caminhamento comeca nele)
        for (int i = 0; i < V; i++) {
            if (adj[i].size() % 2 != 0) {
                oddCount++;
                startVertex = i;
            }
        }

        //não existe caminho euleriano (so pode ter no max 2 vertices de grau impar)
        if (oddCount > 2)
            return path;

        Graph tempGraph = *this;
        int currentVertex = startVertex;

        while (!tempGraph.adj[currentVertex].empty()) {
            std::vector<std::pair<int, int>> bridges;
            if (useTarjan) {
                bridges = tempGraph.findBridgesTarjan();
            } else {
                bridges = tempGraph.findBridgesNaive();
            }

            int nextVertex = -1;
            for (int neighbor : tempGraph.adj[currentVertex]) {
                bool isBridge = false;
                for (auto &bridge : bridges) {
                    if ((bridge.first == currentVertex && bridge.second == neighbor) || (bridge.first == neighbor && bridge.second == currentVertex)) {
                        isBridge = true;
                        break;
                    }
                }
                if (!isBridge || tempGraph.adj[currentVertex].size() == 1) {
                    nextVertex = neighbor;
                    break;
                }
            }

            if (nextVertex == -1) {
                nextVertex = tempGraph.adj[currentVertex].front();
            }

            path.push_back(currentVertex);
            tempGraph.removeEdge(currentVertex, nextVertex);
            currentVertex = nextVertex;
        }
        path.push_back(currentVertex);
        return path;
    }

    int getV() const { 
        return V; 
    }
    
    const std::vector<std::list<int>> &getAdj() const { 
        return adj; 
    }
};

#endif