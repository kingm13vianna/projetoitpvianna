#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "et1.h"

using namespace std;

//cor
Cor::Cor() : r(0), g(0), b(0) {}
Cor::Cor(int r_, int g_, int b_) : r(r_), g(g_), b(b_) {}

//paleta
Paleta::Paleta() = default;

Paleta::Paleta(const string& nomeArquivo) {
    ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo: " << nomeArquivo << endl;
        return;
    }

    string linha;
    while (getline(arquivo, linha)) {
        if (linha.empty()) continue;

        //remove '#'
        if (linha[0] == '#') linha = linha.substr(1);

        //converte hexadecimal para decimal
        if (linha.length() == 6) {
            int r = stoi(linha.substr(0, 2), nullptr, 16);
            int g = stoi(linha.substr(2, 2), nullptr, 16);
            int b = stoi(linha.substr(4, 2), nullptr, 16);
            adicionarCor(Cor(r, g, b));
        }
    }
    arquivo.close();
}

void Paleta::adicionarCor(const Cor& cor) {
    cores.push_back(cor);//adiciona dinamicamente
}

int Paleta::obterTamanho() const {
    return static_cast<int>(cores.size());
}

Cor Paleta::obterCor(int indice) const {
    if (indice >= 0 && indice < static_cast<int>(cores.size()))
        return cores[indice];
    return Cor();  //retorna preto se índice inválido
}
