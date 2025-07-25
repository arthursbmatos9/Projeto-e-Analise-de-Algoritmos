#pragma once
#include <memory>
#include <vector>
#include <functional>
#include <algorithm>
#include <iostream>
#include "../include/Tree.hpp"
#include "../include/No.hpp"

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
class ZhangShashaCalculator {
private:
    vector<shared_ptr<No<T>>> nos_arvore1;
    vector<shared_ptr<No<T>>> nos_arvore2;
    vector<int> leftmost_arvore1;
    vector<int> leftmost_arvore2;
    vector<int> keyroots_arvore1;
    vector<int> keyroots_arvore2;
    vector<vector<int>> treedist;
    vector<vector<int>> forestdist;

public:
    ZhangShashaCalculator();
    int calcularDistancia(Tree<T>& arvore1, Tree<T>& arvore2);

private:
    void preprocessarArvores(Tree<T>& arvore1, Tree<T>& arvore2);
    void calcularLeftmostLeaves();
    void calcularKeyroots();
    void calcularDistanciaSubarvore(int i, int j);
};

template <typename T>
ZhangShashaCalculator<T>::ZhangShashaCalculator() {}

template <typename T>
int ZhangShashaCalculator<T>::calcularDistancia(Tree<T>& arvore1, Tree<T>& arvore2) {
    preprocessarArvores(arvore1, arvore2);
    calcularLeftmostLeaves();
    calcularKeyroots();

    int n = nos_arvore1.size();
    int m = nos_arvore2.size();

    treedist = vector<vector<int>>(n, vector<int>(m, 0));

    sort(keyroots_arvore1.begin(), keyroots_arvore1.end());
    sort(keyroots_arvore2.begin(), keyroots_arvore2.end());

    for (int i : keyroots_arvore1) {
        for (int j : keyroots_arvore2) {
            calcularDistanciaSubarvore(i, j);
        }
    }

    return treedist[n - 1][m - 1];
}

template <typename T>
void ZhangShashaCalculator<T>::preprocessarArvores(Tree<T>& arvore1, Tree<T>& arvore2) {
    arvore1.estabelecerPais();
    arvore1.numerarPosOrdem();
    arvore2.estabelecerPais();
    arvore2.numerarPosOrdem();

    nos_arvore1 = arvore1.getNodesPostOrder();
    nos_arvore2 = arvore2.getNodesPostOrder();

    leftmost_arvore1.resize(nos_arvore1.size());
    leftmost_arvore2.resize(nos_arvore2.size());
}

template <typename T>
void ZhangShashaCalculator<T>::calcularLeftmostLeaves() {
    for (int i = 0; i < nos_arvore1.size(); ++i) {
        auto no = nos_arvore1[i];
        if (no->isFolha()) {
            leftmost_arvore1[i] = i;
        } else {
            int min_leftmost = nos_arvore1.size();
            for (auto& filho : no->getFilhos()) {
                int filho_idx = -1;
                for (int idx = 0; idx < i; ++idx) {
                    if (nos_arvore1[idx] == filho) {
                        filho_idx = idx;
                        break;
                    }
                }
                min_leftmost = min(min_leftmost, leftmost_arvore1[filho_idx]);
            }
            leftmost_arvore1[i] = min_leftmost;
        }
    }

    for (int i = 0; i < nos_arvore2.size(); ++i) {
        auto no = nos_arvore2[i];
        if (no->isFolha()) {
            leftmost_arvore2[i] = i;
        } else {
            int min_leftmost = nos_arvore2.size();
            for (auto& filho : no->getFilhos()) {
                int filho_idx = -1;
                for (int idx = 0; idx < i; ++idx) {
                    if (nos_arvore2[idx] == filho) {
                        filho_idx = idx;
                        break;
                    }
                }
                min_leftmost = min(min_leftmost, leftmost_arvore2[filho_idx]);
            }
            leftmost_arvore2[i] = min_leftmost;
        }
    }
}

template <typename T>
void ZhangShashaCalculator<T>::calcularKeyroots() {
    for (int k = 0; k < nos_arvore1.size(); ++k) {
        bool is_keyroot = true;
        for (int kp = k + 1; kp < nos_arvore1.size(); ++kp) {
            if (leftmost_arvore1[k] == leftmost_arvore1[kp]) {
                is_keyroot = false;
                break;
            }
        }
        if (is_keyroot) {
            keyroots_arvore1.push_back(k);
        }
    }

    for (int k = 0; k < nos_arvore2.size(); ++k) {
        bool is_keyroot = true;
        for (int kp = k + 1; kp < nos_arvore2.size(); ++kp) {
            if (leftmost_arvore2[k] == leftmost_arvore2[kp]) {
                is_keyroot = false;
                break;
            }
        }
        if (is_keyroot) {
            keyroots_arvore2.push_back(k);
        }
    }
}

template <typename T>
void ZhangShashaCalculator<T>::calcularDistanciaSubarvore(int i, int j) {
    int l_i = leftmost_arvore1[i];
    int l_j = leftmost_arvore2[j];

    int rows = i - l_i + 2;
    int cols = j - l_j + 2;

    forestdist = vector<vector<int>>(rows, vector<int>(cols, 0));

    for (int i1 = l_i; i1 <= i; ++i1) {
        forestdist[i1 - l_i + 1][0] = forestdist[i1 - l_i][0] +
                                     custoDeletar(nos_arvore1[i1]);
    }

    for (int j1 = l_j; j1 <= j; ++j1) {
        forestdist[0][j1 - l_j + 1] = forestdist[0][j1 - l_j] +
                                     custoInserir(nos_arvore2[j1]);
    }

    for (int i1 = l_i; i1 <= i; ++i1) {
        for (int j1 = l_j; j1 <= j; ++j1) {
            int row = i1 - l_i + 1;
            int col = j1 - l_j + 1;

            if (leftmost_arvore1[i1] == l_i && leftmost_arvore2[j1] == l_j) {
                int custo_del = forestdist[row - 1][col] +
                                custoDeletar(nos_arvore1[i1]);
                int custo_ins = forestdist[row][col - 1] +
                                custoInserir(nos_arvore2[j1]);
                int custo_sub = forestdist[row - 1][col - 1] +
                                custoSubstituir(nos_arvore1[i1], nos_arvore2[j1]);

                forestdist[row][col] = min({custo_del, custo_ins, custo_sub});

                treedist[i1][j1] = forestdist[row][col];
            } else {
                int custo_del = forestdist[row - 1][col] +
                                custoDeletar(nos_arvore1[i1]);
                int custo_ins = forestdist[row][col - 1] +
                                custoInserir(nos_arvore2[j1]);

                int custo_tree = forestdist[leftmost_arvore1[i1] - l_i][leftmost_arvore2[j1] - l_j] +
                                 treedist[i1][j1];

                forestdist[row][col] = min({custo_del, custo_ins, custo_tree});
            }
        }
    }
}

template <typename T>
int zhangShashaDistance(Tree<T>& arvore1, Tree<T>& arvore2) {
    ZhangShashaCalculator<T> calculator;
    return calculator.calcularDistancia(arvore1, arvore2);
}
