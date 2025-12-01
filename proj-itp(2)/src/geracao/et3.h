#ifndef ET3_H
#define ET3_H

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "et2.h"

class MapaAltitudes {
private:
    float** altitudes;
    int tamanho;
    int N;
    
    //privados
    void inicializarMatriz(float valorDefault = 0.0f);
    void liberarMatriz();
    float gerarDeslocamentoAleatorio(float amplitude);
    
    //algoritmo 
protected:
    void etapaDiamond(int x, int y, int passo, float amplitude);
    void etapaSquare(int x, int y, int passo, float amplitude);
    void aplicarDiamondSquarePasso(int passo, float& amplitude, float rugosidade);
    
public:
    //construtores e destrutor
    MapaAltitudes();
    MapaAltitudes(int n);
    MapaAltitudes(const MapaAltitudes& outro); //construtor de copia
    ~MapaAltitudes();


    Imagem* gerarImagem(const Paleta& paleta, bool sombreamento = true, float fatorSombreamento = 0.5f) const;
    
    //pperador de atribuicao
    MapaAltitudes& operator=(const MapaAltitudes& outro);
    
    //metodos publicos
    void gerarMapa(float rugosidade = 0.5f);
    float obterAltitude(int linha, int coluna) const;
    void definirAltitude(int linha, int coluna, float valor);
    int obterNumLinhas() const;
    int obterNumColunas() const;
    int obterN() const;
    
    //litura e escrita
    bool salvarArquivo(const std::string& nomeArquivo) const;
    bool lerArquivo(const std::string& nomeArquivo);
    
    //utilitários
    void imprimir() const;
    void imprimirCompleto() const;
    
    //mtodos para testes
    bool estaInicializado() const;
    float getMaxAltitude() const;
    float getMinAltitude() const;
    
    //para testes avançados - friend class
    friend class TestadorMapaAltitudes;
};

//ckasse auxiliar para testes
class TestadorMapaAltitudes {
public:
    static void testarEtapaDiamond(MapaAltitudes& mapa, int x, int y, int passo, float amplitude);
    static void testarEtapaSquare(MapaAltitudes& mapa, int x, int y, int passo, float amplitude);
    static bool verificarMatrizConstante(const MapaAltitudes& mapa, float valorEsperado, float tolerancia = 0.0001f);
};

#endif