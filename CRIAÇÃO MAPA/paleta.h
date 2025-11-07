#ifndef PALETA_H
#define PALETA_H
#include <string>
#include <vector>

struct Cor {
    int r;
    int g;
    int b;
};

class Paleta {
private:
    std::vector<Cor> cores;
    int hexParaDecimal(const std::string& hex); 

public:
    Paleta();
    Paleta(const std::string& nomeArquivo);
    void adicionarCor(const Cor& cor);
    int obterTamanho() const;
    Cor obterCor(int indice) const;
};

#endif