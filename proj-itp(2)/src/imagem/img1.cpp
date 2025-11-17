#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "img1.h"
using namespace std;


Imagem::Imagem() : largura(0), altura(0), mapa(nullptr) {}

Imagem::Imagem(int largura, int altura) : largura(largura), altura(altura) {
    mapa = new Cor*[altura];
    for (int i = 0; i < altura; i++) {
        mapa[i] = new Cor[largura];
    }
}

Imagem::~Imagem() {
    if (mapa) {
        for (int i = 0; i < altura; ++i) {
            delete[] mapa[i];
        }
        delete[] mapa;
    }
}


int Imagem::obterLargura() const { 
    return largura; 
}

int Imagem::obterAltura() const { 
    return altura; 
}


Cor& Imagem::operator()(int x, int y) {
    return mapa[y][x];  
}

const Cor& Imagem::operator()(int x, int y) const {
    return mapa[y][x];
}


bool Imagem::lerPPM(const string& nomeArquivo) {
    ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        return false;
    }

    string formato;
    arquivo >> formato;
    
    if (formato != "P3") {
        return false;
    }

    arquivo >> largura >> altura;
    
    int maxValor;
    arquivo >> maxValor;

   
    mapa = new Cor*[altura];
    for (int i = 0; i < altura; i++) {
        mapa[i] = new Cor[largura];
    }

    
    for (int y = 0; y < altura; y++) {
        for (int x = 0; x < largura; x++) {
            int r, g, b;
            arquivo >> r >> g >> b;
            mapa[y][x] = Cor(r, g, b);
        }
    }

    arquivo.close();
    return true;
}


bool Imagem::salvarPPM(const string& nomeArquivo) const {
    ofstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        return false;
    }

    
    arquivo << "P3\n";
    arquivo << largura << " " << altura << "\n";
    arquivo << "255\n";

    
    for (int y = 0; y < altura; y++) {
        for (int x = 0; x < largura; x++) {
            arquivo << mapa[y][x].r << " " 
                    << mapa[y][x].g << " " 
                    << mapa[y][x].b << "\n";  
        }
    }

    arquivo.close();
    return true;
}