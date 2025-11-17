#ifndef ET2_H
#define ET2_H

#include <iostream>
#include <string>
#include "cor1.h"
using namespace std;


typedef Cor Pixel;

class Imagem {
private:
    int largura;
    int altura;
    Cor **mapa;

public:
   
    Imagem();
    Imagem(int largura, int altura);
    ~Imagem();

    
    int obterLargura() const;
    int obterAltura() const;

    
    Cor& operator()(int x, int y);
    const Cor& operator()(int x, int y) const;

    
    bool lerPPM(const string& nomeArquivo);
    bool salvarPPM(const string& nomeArquivo) const;
};

#endif


