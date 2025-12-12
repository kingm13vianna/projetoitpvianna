#include "ter1.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;

//construtor padrão
MapaAltitudes::MapaAltitudes() : altitudes(nullptr), tamanho(0), N(0) {
    srand(time(nullptr));
}

//construtor com tamanho
MapaAltitudes::MapaAltitudes(int n) : N(n) {
    srand(time(nullptr));
    tamanho = pow(2, n) + 1;
    inicializarMatriz();
}

//construtor de cópia
MapaAltitudes::MapaAltitudes(const MapaAltitudes& outro) {
    N = outro.N;
    tamanho = outro.tamanho;
    
    if (tamanho > 0 && outro.altitudes != nullptr) {
        altitudes = new float*[tamanho];
        for (int i = 0; i < tamanho; i++) {
            altitudes[i] = new float[tamanho];
            for (int j = 0; j < tamanho; j++) {
                altitudes[i][j] = outro.altitudes[i][j];
            }
        }
    } else {
        altitudes = nullptr;
    }
}

//operador de atribuição
MapaAltitudes& MapaAltitudes::operator=(const MapaAltitudes& outro) {
    if (this != &outro) {
        liberarMatriz();
        
        N = outro.N;
        tamanho = outro.tamanho;
        
        if (tamanho > 0 && outro.altitudes != nullptr) {
            altitudes = new float*[tamanho];
            for (int i = 0; i < tamanho; i++) {
                altitudes[i] = new float[tamanho];
                for (int j = 0; j < tamanho; j++) {
                    altitudes[i][j] = outro.altitudes[i][j];
                }
            }
        } else {
            altitudes = nullptr;
        }
    }
    return *this;
}

//distrutor
MapaAltitudes::~MapaAltitudes() {
    liberarMatriz();
}

//onicializa matriz
void MapaAltitudes::inicializarMatriz(float valorDefault) {
    if (tamanho <= 0) return;
    
    liberarMatriz();
    
    altitudes = new float*[tamanho];
    for (int i = 0; i < tamanho; i++) {
        altitudes[i] = new float[tamanho];
        for (int j = 0; j < tamanho; j++) {
            altitudes[i][j] = valorDefault;
        }
    }
}

//libera memória
void MapaAltitudes::liberarMatriz() {
    if (altitudes) {
        for (int i = 0; i < tamanho; i++) {
            delete[] altitudes[i];
        }
        delete[] altitudes;
        altitudes = nullptr;
    }
}

//gera deslocamento aleatório
float MapaAltitudes::gerarDeslocamentoAleatorio(float amplitude) {
    return ((rand() % 2001) / 1000.0f - 1.0f) * amplitude;
}

//etapa Diamond
void MapaAltitudes::etapaDiamond(int x, int y, int passo, float amplitude) {
    int meio = passo / 2;
    
    //verifica se as coordenadas dos cantos são válidas
    if (y - meio >= 0 && y + meio < tamanho &&
        x - meio >= 0 && x + meio < tamanho) {
        
        float canto1 = altitudes[y - meio][x - meio];
        float canto2 = altitudes[y - meio][x + meio];
        float canto3 = altitudes[y + meio][x - meio];
        float canto4 = altitudes[y + meio][x + meio];
        
        float media = (canto1 + canto2 + canto3 + canto4) / 4.0f;
        altitudes[y][x] = media + gerarDeslocamentoAleatorio(amplitude);
    }
}

//etapa Square
void MapaAltitudes::etapaSquare(int x, int y, int passo, float amplitude) {
    int meio = passo / 2;
    int contador = 0;
    float soma = 0.0f;
    
    //pontos adjacentes
    if (y - meio >= 0) {
        soma += altitudes[y - meio][x];
        contador++;
    }
    if (y + meio < tamanho) {
        soma += altitudes[y + meio][x];
        contador++;
    }
    if (x - meio >= 0) {
        soma += altitudes[y][x - meio];
        contador++;
    }
    if (x + meio < tamanho) {
        soma += altitudes[y][x + meio];
        contador++;
    }
    
    if (contador > 0) {
        float media = soma / contador;
        altitudes[y][x] = media + gerarDeslocamentoAleatorio(amplitude);
    }
}

//aplica um passo completo do algoritmo
void MapaAltitudes::aplicarDiamondSquarePasso(int passo, float amplitude) {
    // etapa Diamond
    for (int y = passo/2; y < tamanho; y += passo) {
        for (int x = passo/2; x < tamanho; x += passo) {
            etapaDiamond(x, y, passo, amplitude);
        }
    }
    
    // etapa Square
    for (int y = 0; y < tamanho; y += passo/2) {
        int inicioX = (y + passo/2) % passo;
        if (passo/2 <= 0) break;  // Evita loop infinito
        for (int x = inicioX; x < tamanho; x += passo) {
            etapaSquare(x, y, passo, amplitude);
        }
    }
    // // Etapa Square - CORREÇÃO CRÍTICA
    // for (int y = 0; y < tamanho; y += passo/2) {
    //     // CUIDADO: passo/2 pode ser 0 se passo < 2
    //     if (passo/2 <= 0) break;  // Evita loop infinito
        
    //     int inicioX = (y % (passo/2 == 0 ? 1 : passo/2)) == 0 ? passo/2 : 0;
    //     for (int x = inicioX; x < tamanho; x += passo) {
    //         if (x < tamanho && y < tamanho) {  // Verificação extra
    //             etapaSquare(x, y, passo, amplitude);
    //         }
    //     }
    // }
    
    //reduz amplitude
    // amplitude *= rugosidade;
}

//hera o mapa completo
void MapaAltitudes::gerarMapa(float rugosidade) {
    if (tamanho <= 1 || rugosidade < 0.0f || rugosidade > 1.0f) return;
    
    //imicializa com zeros
    inicializarMatriz(0.0f);
    
    
    //inicializa cantos com valores aleatórios
    float amplitudeInicial = 1.0f;
    altitudes[0][0] = gerarDeslocamentoAleatorio(amplitudeInicial);
    altitudes[0][tamanho-1] = gerarDeslocamentoAleatorio(amplitudeInicial);
    altitudes[tamanho-1][0] = gerarDeslocamentoAleatorio(amplitudeInicial);
    altitudes[tamanho-1][tamanho-1] = gerarDeslocamentoAleatorio(amplitudeInicial);
    
    float amplitude = amplitudeInicial;
    int passo = tamanho - 1;
    
    //aplica algoritmo iterativamente
    while (passo > 1) {
        aplicarDiamondSquarePasso(passo, amplitude, rugosidade);
        passo /= 2;
    }
    
    //normaliza para [0, 1]
    float minAlt = altitudes[0][0];
    float maxAlt = altitudes[0][0];
    
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            if (altitudes[i][j] < minAlt) minAlt = altitudes[i][j];
            if (altitudes[i][j] > maxAlt) maxAlt = altitudes[i][j];
        }
    }
    
    float range = maxAlt - minAlt;
    if (range > 0.0001f) {
        for (int i = 0; i < tamanho; i++) {
            for (int j = 0; j < tamanho; j++) {
                altitudes[i][j] = (altitudes[i][j] - minAlt) / range;
            }
        }
    }
}

//metodos de acesso
float MapaAltitudes::obterAltitude(int linha, int coluna) const {
    if (linha >= 0 && linha < tamanho && coluna >= 0 && coluna < tamanho) {
        return altitudes[linha][coluna];
    }
    return 0.0f;
}

void MapaAltitudes::definirAltitude(int linha, int coluna, float valor) {
    if (linha >= 0 && linha < tamanho && coluna >= 0 && coluna < tamanho) {
        altitudes[linha][coluna] = valor;
    }
}

int MapaAltitudes::obterNumLinhas() const { return tamanho; }
int MapaAltitudes::obterNumColunas() const { return tamanho; }
int MapaAltitudes::obterN() const { return N; }

//verifica se o mapa está inicializado
bool MapaAltitudes::estaInicializado() const {
    return altitudes != nullptr && tamanho > 0;
}

//obtem altitude máxima
float MapaAltitudes::getMaxAltitude() const {
    if (!estaInicializado()) return 0.0f;
    
    float maxVal = altitudes[0][0];
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            if (altitudes[i][j] > maxVal) maxVal = altitudes[i][j];
        }
    }
    return maxVal;
}

//obtem altitude mínima
float MapaAltitudes::getMinAltitude() const {
    if (!estaInicializado()) return 0.0f;
    
    float minVal = altitudes[0][0];
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            if (altitudes[i][j] < minVal) minVal = altitudes[i][j];
        }
    }
    return minVal;
}

//sava em arquivo
bool MapaAltitudes::salvarArquivo(const string& nomeArquivo) const {
    ofstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        return false;
    }
    
    arquivo << tamanho << endl;
    
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            arquivo << fixed << setprecision(6) << altitudes[i][j];
            if (j < tamanho - 1) arquivo << " ";
        }
        arquivo << endl;
    }
    
    arquivo.close();
    return true;
}

//ler de arquivo
bool MapaAltitudes::lerArquivo(const string& nomeArquivo) {
    ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        return false;
    }
    
    int novoTamanho;
    arquivo >> novoTamanho;
    
    //verifica se é tamanho válido (2^N + 1)
    bool valido = false;
    for (int n = 1; n <= 10; n++) {
        if (novoTamanho == (int)pow(2, n) + 1) {
            valido = true;
            N = n;
            break;
        }
    }
    
    if (!valido) {
        arquivo.close();
        return false;
    }
    
    tamanho = novoTamanho;
    inicializarMatriz();
    
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            arquivo >> altitudes[i][j];
        }
    }
    
    arquivo.close();
    return true;
}

//umprime resumo
void MapaAltitudes::imprimir() const {
    cout << "Mapa " << tamanho << "x" << tamanho << " (N=" << N << ")" << endl;
    cout << "Altitudes: [" << getMinAltitude() << " a " << getMaxAltitude() << "]" << endl;
    
    if (tamanho <= 10) {
        imprimirCompleto();
    } else {
        cout << "Primeiras 5x5 células:" << endl;
        for (int i = 0; i < min(5, tamanho); i++) {
            for (int j = 0; j < min(5, tamanho); j++) {
                cout << fixed << setprecision(3) << altitudes[i][j] << " ";
            }
            cout << endl;
        }
    }
}

//imprime completo
void MapaAltitudes::imprimirCompleto() const {
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            cout << fixed << setprecision(3) << altitudes[i][j] << "\t";
        }
        cout << endl;
    }
}

//metodos da classe TestadorMapaAltitudes
void TestadorMapaAltitudes::testarEtapaDiamond(MapaAltitudes& mapa, int x, int y, int passo, float amplitude) {
    mapa.etapaDiamond(x, y, passo, amplitude);
}

void TestadorMapaAltitudes::testarEtapaSquare(MapaAltitudes& mapa, int x, int y, int passo, float amplitude) {
    mapa.etapaSquare(x, y, passo, amplitude);
}

bool TestadorMapaAltitudes::verificarMatrizConstante(const MapaAltitudes& mapa, float valorEsperado, float tolerancia) {
    if (!mapa.estaInicializado()) return false;
    
    for (int i = 0; i < mapa.tamanho; i++) {
        for (int j = 0; j < mapa.tamanho; j++) {
            if (fabs(mapa.altitudes[i][j] - valorEsperado) > tolerancia) {
                return false;
            }
        }
    }
    return true;
}