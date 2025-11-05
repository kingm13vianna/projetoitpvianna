#ifndef SEQUENCIA_H
#define SEQUENCIA_H

template <typename T>
class Sequencia {
private:
    T* dados;           
    int quantidade;     
    int capacidade;     

    
    void redimensionar(int novaCapacidade);

public:
    
    Sequencia();                            
    Sequencia(int capacidadeInicial);      
    Sequencia(const Sequencia& outra);      
    Sequencia& operator=(const Sequencia& outra); 
    
    
    ~Sequencia();
    
    
    void inserir(const T& elemento);
    void remover();
    T& obter(int indice);
    const T& obter(int indice) const;
    void alterar(int indice, const T& elemento);
    int obterQuantidade() const;
    int obterCapacidade() const;
    bool estaVazia() const;
    
    
    T& operator[](int indice);
    const T& operator[](int indice) const;
};



template <typename T>
Sequencia<T>::Sequencia() : quantidade(0), capacidade(10) {
    dados = new T[capacidade];
}

template <typename T>
Sequencia<T>::Sequencia(int capacidadeInicial) : quantidade(0), capacidade(capacidadeInicial) {
    if (capacidadeInicial <= 0) {
        capacidade = 10;
    }
    dados = new T[capacidade];
}

template <typename T>
Sequencia<T>::Sequencia(const Sequencia& outra) 
    : quantidade(outra.quantidade), capacidade(outra.capacidade) {
    dados = new T[capacidade];
    for (int i = 0; i < quantidade; i++) {
        dados[i] = outra.dados[i];
    }
}

template <typename T>
Sequencia<T>& Sequencia<T>::operator=(const Sequencia& outra) {
    if (this != &outra) {
        delete[] dados;
        quantidade = outra.quantidade;
        capacidade = outra.capacidade;
        dados = new T[capacidade];
        for (int i = 0; i < quantidade; i++) {
            dados[i] = outra.dados[i];
        }
    }
    return *this;
}

template <typename T>
Sequencia<T>::~Sequencia() {
    delete[] dados;
}

template <typename T>
void Sequencia<T>::redimensionar(int novaCapacidade) {
    T* novosDados = new T[novaCapacidade];
    for (int i = 0; i < quantidade; i++) {
        novosDados[i] = dados[i];
    }
    delete[] dados;
    dados = novosDados;
    capacidade = novaCapacidade;
}

template <typename T>
void Sequencia<T>::inserir(const T& elemento) {
    if (quantidade >= capacidade) {
        redimensionar(capacidade * 2); 
    }
    dados[quantidade] = elemento;
    quantidade++;
}

template <typename T>
void Sequencia<T>::remover() {
    if (quantidade > 0) {
        quantidade--;
    }
}

template <typename T>
T& Sequencia<T>::obter(int indice) {
    if (indice < 0 || indice >= quantidade) {
        throw std::out_of_range() ;
    }
    return dados[indice];
}

template <typename T>
const T& Sequencia<T>::obter(int indice) const {
    if (indice < 0 || indice >= quantidade) {
        throw std::out_of_range();
    }
    return dados[indice];
}

template <typename T>
void Sequencia<T>::alterar(int indice, const T& elemento) {
    if (indice < 0 || indice >= quantidade) {
        throw std::out_of_range();
    }
    dados[indice] = elemento;
}

template <typename T>
int Sequencia<T>::obterQuantidade() const {
    return quantidade;
}

template <typename T>
int Sequencia<T>::obterCapacidade() const {
    return capacidade;
}

template <typename T>
bool Sequencia<T>::estaVazia() const {
    return quantidade == 0;
}

template <typename T>
T& Sequencia<T>::operator[](int indice) {
    return obter(indice);
}

template <typename T>
const T& Sequencia<T>::operator[](int indice) const {
    return obter(indice);
}

#endif