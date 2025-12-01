#ifndef COR1_H
#define COR1_H

#include <iostream>
#include <string>
#include <vector>


class Cor {
public:
    int r;
    int g;
    int b;

    Cor();
    Cor(int r, int g, int b);
};

class Paleta {
private:
   std:: vector<Cor>cores;

public:
    Paleta(); //construtor padrão
    Paleta(const std::string& nomeArquivo); //construtor de arquivo

    void adicionarCor(const Cor& cor);
    int obterTamanho() const;
    Cor obterCor(int indice) const;
};

#endif
