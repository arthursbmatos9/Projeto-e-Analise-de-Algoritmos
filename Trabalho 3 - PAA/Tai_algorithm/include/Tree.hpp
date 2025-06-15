#pragma once
#include <memory>
#include <vector>
#include <iostream>
#include <algorithm>
#include "No.hpp"

using namespace std;

template <typename T>
class Tree {
private:
    shared_ptr<No<T>> raiz;

    shared_ptr<No<T>> buscar(shared_ptr<No<T>> no, const T& valor);

public:
    Tree();
    Tree(const T& labelRaiz);

    shared_ptr<No<T>> getRaiz();
    bool estaVazia();

    bool adicionarFilho(const T& pai, const T& filho);
    bool removerFilho(const T& pai, const T& filho);

    vector<shared_ptr<No<T>>> getNodesPostOrder();

private:
    void getNodesPostOrder(shared_ptr<No<T>> no, vector<shared_ptr<No<T>>>& temp);
};

template <typename T>
Tree<T>::Tree() {
    raiz = nullptr;
}

template <typename T>
Tree<T>::Tree(const T& labelRaiz) : raiz(make_shared<No<T>>(labelRaiz)) {}

template <typename T>
shared_ptr<No<T>> Tree<T>::getRaiz() {
    return this.raiz;
}

template <typename T>
bool Tree<T>::estaVazia() {
    return this->raiz == nullptr;
}

template <typename T>
shared_ptr<No<T>> Tree<T>::buscar(const shared_ptr<No<T>> no, const T& valor) {
    if(no == nullptr) return nullptr;
    if(no->getLabel() == valor) return no;

    for(const auto filho : no->getFilhos()) {
        auto result = buscar(filho, valor);
        if(result) return result;
    }

    return nullptr;
}

template <typename T>
bool Tree<T>::adicionarFilho(const T& pai, const T& filho) {
    auto no = buscar(raiz, pai);
    if(no == nullptr) return false;
    auto newNo = make_shared<No<T>>(filho);
    no->adicionarFilho(newNo);
    return true;
}

template <typename T>
bool Tree<T>::removerFilho(const T& pai, const T& filho) {
    auto no = buscar(raiz, pai);
    if(no == nullptr) return false;
    no->removerFilho(filho);
    return true;
}

template <typename T>
vector<shared_ptr<No<T>>> Tree<T>::getNodesPostOrder() {
    vector<shared_ptr<No<T>>> temp;
    getNodesPostOrder(raiz, temp);
    return temp;
}

template <typename T>
void Tree<T>::getNodesPostOrder(const shared_ptr<No<T>> no, vector<shared_ptr<No<T>>>& temp) {
    if(no == nullptr) return;   

    for(const auto i : no->getFilhos()) {
        getNodesPostOrder(i, temp);
    }
    temp.push_back(no);
    //cout << no->getLabel() << " " << (no->isFolha() ? "True" : "False") << " - ";
}