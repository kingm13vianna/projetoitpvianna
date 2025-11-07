#include "paleta.h"
#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

Paleta::Paleta() {

}

Paleta::Paleta(const string& nomeArquivo) {
    ifstream arquivo(nomeArquivo);

    if (!arquivo.is_open()) {
        return;
    }

    string linha;
    while(getline(arquivo, linha)) { 
        size_t inicio = linha.find_first_not_of(" \t");
        size_t fim = linha.find_last_not_of(" \t");
        
        if (inicio != string::npos && fim != string::npos) {
            linha = linha.substr(inicio, fim - inicio + 1);
        }

        if (linha.length() == 7 && linha[0] == '#') {
            string hexR = linha.substr(1, 2);
            string hexG = linha.substr(3, 2);
            string hexB = linha.substr(5, 2);
            
            Cor cor;
            cor.r = hexParaDecimal(hexR);
            cor.g = hexParaDecimal(hexG);
            cor.b = hexParaDecimal(hexB);
            
            adicionarCor(cor);
        }
    }  
    
    arquivo.close();
}  

void Paleta::adicionarCor(const Cor& cor) {
    cores.push_back(cor);
}

int Paleta::obterTamanho() const {
    return cores.size();
}

Cor Paleta::obterCor(int indice) const {
    if (indice < 0 || indice >= cores.size()) {
        return Cor{0, 0, 0};
    }
    return cores[indice];
}

int Paleta::hexParaDecimal(const string& hex) {
    int resultado = 0;
    int base = 1;
    
    for (int i = hex.length() - 1; i >= 0; i--) {
        char c = hex[i];
        int valor;
        
        if (c >= '0' && c <= '9') {
            valor = c - '0';
        } else if (c >= 'a' && c <= 'f') {
            valor = 10 + (c - 'a');
        } else if (c >= 'A' && c <= 'F') {
            valor = 10 + (c - 'A');
        } else {
            valor = 0;
        }
        
        resultado += valor * base;
        base *= 16;
    }
    
    return resultado;
}