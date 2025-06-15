#include "memory"

using namespace std;

template <typename T>
int custoDeletar(shared_ptr<No<T>>& no) {
    return 1; // ou outro custo
}

template <typename T>
int custoInserir(shared_ptr<No<T>>& no) {
    return 1; // ou outro custo
}

template <typename T>
int custoSubstituir(shared_ptr<No<T>>& no1, shared_ptr<No<T>>& no2) {
    return no1->getLabel() == no2->getLabel() ? 0 : 1;
}

template <typename T>
int TED(Tree<T> T1, Tree<T> T2) {
    auto post_T1 = T1.getNodesPostOrder();
    auto post_T2 = T2.getNodesPostOrder();

    int n = post_T1.size();
    int m = post_T2.size();

    vector<vector<int>> D(n, vector<int>(m, 0));

    for (int i = 0; i < n; ++i) {
        auto ni = post_T1[i];
        for (int j = 0; j < m; ++j) {
            auto nj = post_T2[j];

            if (ni->isFolha() && nj->isFolha()) {
                // Para folhas, apenas o custo de substituição
                D[i][j] = custoSubstituir(ni, nj);
            } else {
                int custoSub = custoSubstituir(ni, nj);
                int custoFilhos = 0;

                auto& filhos_i = ni->getFilhos();
                auto& filhos_j = nj->getFilhos();

                // Correspondência simples: assumindo mesma ordem e quantidade
                int minFilhos = min(filhos_i.size(), filhos_j.size());
                
                for (int k = 0; k < minFilhos; ++k) {
                    auto it_i = find(post_T1.begin(), post_T1.end(), filhos_i[k]);
                    auto it_j = find(post_T2.begin(), post_T2.end(), filhos_j[k]);
                    if (it_i != post_T1.end() && it_j != post_T2.end()) {
                        int idx_i = distance(post_T1.begin(), it_i);
                        int idx_j = distance(post_T2.begin(), it_j);
                        custoFilhos += D[idx_i][idx_j];
                    }
                }

                // Custo de nós extras (se houver diferença no número de filhos)
                custoFilhos += abs((int)filhos_i.size() - (int)filhos_j.size());

                D[i][j] = custoSub + custoFilhos;
            }
        }
    }

    return D[n - 1][m - 1];
}