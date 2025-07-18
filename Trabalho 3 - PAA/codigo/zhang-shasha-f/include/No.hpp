#pragma once
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

template <typename T>
class No {
private:
    T label;
    vector<shared_ptr<No<T>>> filhos;
    int id_pos_ordem;
    int leftmost_leaf;
    shared_ptr<No<T>> pai;

public:
    No(const T& label);

    void adicionarFilho(shared_ptr<No<T>> filho);
    void removerFilho(const T& valor);
    const T& getLabel() const;
    const vector<shared_ptr<No<T>>>& getFilhos() const;
    const bool isFolha();
    
    //Zhang-Shasha
    void setIdPosOrdem(int id);
    int getIdPosOrdem() const;
    void setLeftmostLeaf(int leaf);
    int getLeftmostLeaf() const;
    void setPai(shared_ptr<No<T>> pai);
    shared_ptr<No<T>> getPai() const;
};

template <typename T>
No<T>::No(const T& label) : label(label), id_pos_ordem(-1), leftmost_leaf(-1), pai(nullptr) {}

template <typename T>
void No<T>::adicionarFilho(shared_ptr<No<T>> filho) {
    filhos.push_back(filho);
}

template <typename T>
void No<T>::removerFilho(const T& valor) {
    for(auto i = filhos.begin(); i != filhos.end(); ++i) {
        if((*i)->getLabel() == valor) {
            filhos.erase(i);
            break;
        }
    }
}

template <typename T>
const T& No<T>::getLabel() const {
    return label;
}

template <typename T>
const vector<shared_ptr<No<T>>>& No<T>::getFilhos() const {
    return filhos;
}

template <typename T>
const bool No<T>::isFolha() {
    return filhos.empty();
}

// Zhang-Shasha

template <typename T>
void No<T>::setIdPosOrdem(int id) {
    id_pos_ordem = id;
}

template <typename T>
int No<T>::getIdPosOrdem() const {
    return id_pos_ordem;
}

template <typename T>
void No<T>::setLeftmostLeaf(int leaf) {
    leftmost_leaf = leaf;
}

template <typename T>
int No<T>::getLeftmostLeaf() const {
    return leftmost_leaf;
}

template <typename T>
void No<T>::setPai(shared_ptr<No<T>> pai) {
    this->pai = pai;
}

template <typename T>
shared_ptr<No<T>> No<T>::getPai() const {
    return pai;
}