#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Analizador.h"

TEST(Analizador, whenDataConUnaNoticiaThenUnaNoticiaEsRecuperadaDelAnalizador)
{
    Analizador a1("dataTests");
    auto noticias = a1.getNoticias();
    EXPECT_EQ(noticias.size(), 1);
    EXPECT_EQ(noticias.front().getTitulo(), " lista de palabras del alfabeto radiofónico");
}