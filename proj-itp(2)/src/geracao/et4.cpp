#include "et1.h"
#include "et2.h"
#include "et3.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;


Cor obterCorParaAltitude(float altitude, const Paleta& paleta) {
    int numCores = paleta.obterTamanho();
    if (numCores <= 0) return Cor(0, 0, 0);

    float alt = max(0.0f, min(1.0f, altitude));

    int indice = static_cast<int>(alt * (numCores - 1));

    indice = max(0, min(indice, numCores - 1));

    return paleta.obterCor(indice);
}


Cor aplicarSombreamento(const Cor& corOriginal, float fator) {
    int r = static_cast<int>(corOriginal.r * fator);
    int g = static_cast<int>(corOriginal.g * fator);
    int b = static_cast<int>(corOriginal.b * fator);

    r = max(0, min(255, r));
    g = max(0, min(255, g));
    b = max(0, min(255, b));

    return Cor(r, g, b);
}


Imagem* MapaAltitudes::gerarImagem(const Paleta& paleta, bool sombreamento, float fatorSombreamento) const {
    if (!estaInicializado() || paleta.obterTamanho() == 0) {
        return nullptr;
    }

    int tam = obterNumLinhas();
    Imagem* imagem = new Imagem(tam, tam);

    for (int y = 0; y < tam; y++) {
        for (int x = 0; x < tam; x++) {

            float altitude = obterAltitude(y, x);
            Cor cor = obterCorParaAltitude(altitude, paleta);

            //SOMBREAMENTO 
            if (sombreamento) {
                float soma = 0.0f;
                int count = 0;

                //vizinho acima
                if (y > 0) {
                    soma += obterAltitude(y - 1, x);
                    count++;
                }

                //vizinho à esquerda
                if (x > 0) {
                    soma += obterAltitude(y, x - 1);
                    count++;
                }

                if (count > 0) {
                    float media = soma / count;

                    //se o ponto atual é mais baixo → sombreia
                    if (altitude < media) {
                        cor = aplicarSombreamento(cor, fatorSombreamento);
                    }
                }
            }

            (*imagem)(x, y) = cor;
        }
    }

    return imagem;
}


int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    cout << "=== GERADOR DE IMAGENS DE TERRENO - ETAPA 4 ===\n\n";

    string arquivoPaleta;
    cout << "Digite o nome do arquivo da paleta de cores: ";
    cin >> arquivoPaleta;

    int N;
    cout << "Digite o valor de N (tamanho = 2^N + 1): ";
    cin >> N;

    string arquivoSaida;
    cout << "Digite o nome do arquivo de saida PPM: ";
    cin >> arquivoSaida;

    Paleta paleta(arquivoPaleta);
    if (paleta.obterTamanho() == 0) {
        cerr << "Erro: Nao foi possivel carregar a paleta ou arquivo vazio.\n";
        return 1;
    }

    cout << "\nPaleta carregada com " << paleta.obterTamanho() << " cores.\n";

    cout << "\nCriando mapa de altitudes com N=" << N << "...\n";
    MapaAltitudes mapa(N);

    float rugosidade;
    cout << "Digite a rugosidade (0.1 a 0.9, recomendado 0.5): ";
    cin >> rugosidade;

    string opcaoSombreamento;
    cout << "\nAplicar sombreamento? (s/n): ";
    cin >> opcaoSombreamento;

    bool usarSombreamento = (opcaoSombreamento == "s"|| opcaoSombreamento == "S");
    float fatorSombreamento = 0.5f;

    if (usarSombreamento) {
        cout << "Digite o fator de sombreamento (0.1 a 0.9, padrão 0.5): ";
        cin >> fatorSombreamento;
        fatorSombreamento = max(0.1f, min(0.9f, fatorSombreamento));
    }


    mapa.gerarMapa(rugosidade);

    cout << "Mapa gerado: " << mapa.obterNumLinhas()
         << "x" << mapa.obterNumColunas() << endl;
    cout << "Altitude min: " << mapa.getMinAltitude()
         << ", max: " << mapa.getMaxAltitude() << endl;

    
    cout << "\nGerando imagem...\n";

    Imagem* imagem = mapa.gerarImagem(paleta, usarSombreamento, fatorSombreamento);

    if (!imagem) {
        cerr << "Erro ao gerar imagem!\n";
        return 1;
    }

    if (imagem->salvarPPM(arquivoSaida)) {
        cout << "Imagem salva com sucesso em: " << arquivoSaida << endl;
        cout << "Dimensoes: " << imagem->obterLargura()
             << "x" << imagem->obterAltura() << endl;
    } else {
        cerr << "Erro ao salvar imagem!\n";
        delete imagem;
        return 1;
    }

    delete imagem;

    cout << "\nConcluido!\n";
    return 0;
}
