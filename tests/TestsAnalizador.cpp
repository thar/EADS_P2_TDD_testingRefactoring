#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Analizador.h"

TEST(Analizador, givenCarpetaConUnaNoticia_whenObtenerNumeroDeNoticias_y_titulo_then_UnaNoticiaConTituloCorrectoEsObtenida)
{
    Analizador a1("dataTests");
    auto noticias = a1.getNoticias();
    EXPECT_EQ(noticias.size(), 1);
    EXPECT_EQ(noticias.front()->getTitulo(), " lista de palabras del alfabeto radiofónico");
}

TEST(Analizador, givenCarpetaConUnaNoticia_whenCrearAnalizadorConConstructorVacio_y_establecerCarpetaDeNoticiasDespues_then_UnaNoticiaConTituloCorrectoEsObtenida)
{
    Analizador a1;
    a1.setNoticas("dataTests");
    auto noticias = a1.getNoticias();
    EXPECT_EQ(noticias.size(), 1);
    EXPECT_EQ(noticias.front()->getTitulo(), " lista de palabras del alfabeto radiofónico");
}

TEST(Analizador, givenCarpetaCon4Noticias_whenAgruparNoticiasPorEntidadMasFrecuente_then_DosGruposSonObtenidos)
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

TEST(Analizador, givenCarpetaCon4Noticias_whenAgruparNoticiasPorEntidadMasFrecuente_then_UnGrupoEsObtenido)
{
    Analizador a1("dataTests2");
    auto noticias = a1.getNoticias();
    EXPECT_EQ(noticias.size(), 4);
    EXPECT_EQ(a1.agruparNoticiasGeneral(), "\nCuarta Noticia\n"
            "   *[ titulo de la Cuarta Noticia]\n"
            "   *[ titulo de la Tercera Noticia]\n"
            "   *[ titulo de la Segunda Noticia]\n"
            "   *[ titulo de la Primera Noticia]\n\n");
}