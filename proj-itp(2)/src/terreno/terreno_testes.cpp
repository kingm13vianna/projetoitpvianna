#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../doctest.h"
#include "ter1.h"

TEST_CASE("Testa a criação de um terreno de uma única célula") {
  MapaAltitudes terreno(0); // 2^0 + 1 = 1
  CHECK(terreno.obterNumLinhas() == 1);
  CHECK(terreno.obterNumColunas() == 1);
}

TEST_CASE("Testa a geração aleatória de altitudes") {
  MapaAltitudes terreno(2);
  CHECK(terreno.obterNumLinhas() == 5);
  CHECK(terreno.obterNumColunas() == 5);
}


// Você precisará criar testes adicionais para cobrir os métodos privados da classe.
// Por exemplo, você pode criar testes para os métodos das etapas Square e Diamond
// Você pode torná-los públicos temporariamente para fins de teste ou usar técnicas como "friend testing".