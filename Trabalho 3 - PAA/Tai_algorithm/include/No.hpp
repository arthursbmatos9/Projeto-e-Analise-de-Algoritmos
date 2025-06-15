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

public:
    No(const T& label);

    void adicionarFilho(shared_ptr<No<T>> filho);
    void removerFilho(const T& valor);
    const T& getLabel() const;
    const vector<shared_ptr<No<T>>>& getFilhos() const;
    const bool isFolha();
};

template <typename T>
No<T>::No(const T& label) : label(label) {}

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