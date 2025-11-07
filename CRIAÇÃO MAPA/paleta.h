#ifndef PALETA_H
#define PALETA_H

#include <string>
#include <vector>
using namespace std;

struct Cor {
    int r;
    int g;
    int b;
};

class Paleta {
private:
    vector<Cor> cores;

public:
    Paleta();
    Paleta(const string& nomeArquivo);
    void adicionarCor(const Cor& cor);
    int obterTamanho() const;
    Cor obterCor(int indice) const;

private:
    int hexParaDecimal(const string& hex);
};

#endif