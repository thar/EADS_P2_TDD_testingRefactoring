#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Analizador.h"

TEST(Analizador, whenDataConUnaNoticiaThenUnaNoticiaEsRecuperadaDelAnalizador)
{
    Analizador a1("dataTests");
    auto noticias = a1.getNoticias();
    EXPECT_EQ(noticias.size(), 1);
    EXPECT_EQ(noticias.front()->getTitulo(), " lista de palabras del alfabeto radiofónico");
}

TEST(Analizador, testConstructorSinParametros)
{
    Analizador a1;
    a1.setNoticas("dataTests");
    auto noticias = a1.getNoticias();
    EXPECT_EQ(noticias.size(), 1);
    EXPECT_EQ(noticias.front()->getTitulo(), " lista de palabras del alfabeto radiofónico");
}

TEST(Analizador, testAgrupacionSimple)
{
    Analizador a1("dataTests2");
    auto noticias = a1.getNoticias();
    EXPECT_EQ(noticias.size(), 4);
    EXPECT_EQ(a1.agruparNoticias(), "\nCuarta\n"
            "*[ titulo de la Cuarta Noticia]\n"
            "\n"
            "Noticia\n"
            "*[ titulo de la Tercera Noticia]\n"
            "*[ titulo de la Segunda Noticia]\n"
            "*[ titulo de la Primera Noticia]\n");
}

TEST(Analizador, testAgrupacionTematico)
{
    Analizador a1("dataTests2");
    auto noticias = a1.getNoticias();
    EXPECT_EQ(noticias.size(), 4);
    EXPECT_EQ(a1.agruparNoticiasGeneral(), "[ titulo de la Cuarta Noticia]\n"
            "   *[ titulo de la Tercera Noticia]\n"
            "   *[ titulo de la Segunda Noticia]\n"
            "   *[ titulo de la Primera Noticia]\n\n");
}