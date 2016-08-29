#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "NoticiaMock.h"
#include "Analizador.h"

using namespace testing;

TEST(Analizador, givenCarpetaConUnaNoticia_whenObtenerNumeroDeNoticias_y_titulo_then_UnaNoticiaConTituloCorrectoEsObtenida)
{
    Analizador a1;
    auto noticia = std::make_shared<NoticiaMock>();
    EXPECT_CALL(*noticia, getTitulo()).Times(1).WillRepeatedly(Return("titulo test"));
    a1.addNoticia(noticia);
    auto noticias = a1.getNoticias();
    EXPECT_EQ(noticias.size(), 1);
    EXPECT_EQ(noticias.front()->getTitulo(), "titulo test");
}

TEST(Analizador, givenCarpetaConUnaNoticia_whenCrearAnalizadorConConstructorVacio_y_establecerCarpetaDeNoticiasDespues_then_UnaNoticiaConTituloCorrectoEsObtenida)
{
    Analizador a1;
    a1.setNoticas("dataTests");
    auto noticias = a1.getNoticias();
    EXPECT_EQ(noticias.size(), 1);
    EXPECT_EQ(noticias.front()->getTitulo(), " lista de palabras del alfabeto radiofónico");
}

TEST(Analizador, given4NoticiasCon2EntidadesDiferentes_whenAgruparNoticiasPorEntidadMasFrecuente_then_DosGruposSonObtenidos)
{
    Analizador a1;
    auto noticia1 = std::make_shared<NoticiaMock>();
    auto noticia2 = std::make_shared<NoticiaMock>();
    auto noticia3 = std::make_shared<NoticiaMock>();
    auto noticia4 = std::make_shared<NoticiaMock>();
    EXPECT_CALL(*noticia1, getMasFrecuente()).WillRepeatedly(Return(EntidadNombrada("Entidad1", 1)));
    EXPECT_CALL(*noticia2, getMasFrecuente()).WillRepeatedly(Return(EntidadNombrada("Entidad2", 2)));
    EXPECT_CALL(*noticia3, getMasFrecuente()).WillRepeatedly(Return(EntidadNombrada("Entidad2", 3)));
    EXPECT_CALL(*noticia4, getMasFrecuente()).WillRepeatedly(Return(EntidadNombrada("Entidad2", 1)));
    EXPECT_CALL(*noticia1, getTitulo()).WillRepeatedly(Return("titulo noticia 1"));
    EXPECT_CALL(*noticia2, getTitulo()).WillRepeatedly(Return("titulo noticia 2"));
    EXPECT_CALL(*noticia3, getTitulo()).WillRepeatedly(Return("titulo noticia 3"));
    EXPECT_CALL(*noticia4, getTitulo()).WillRepeatedly(Return("titulo noticia 4"));
    a1.addNoticia(noticia1);
    a1.addNoticia(noticia2);
    a1.addNoticia(noticia3);
    a1.addNoticia(noticia4);
    auto noticias = a1.getNoticias();
    EXPECT_EQ(noticias.size(), 4);
    EXPECT_EQ(a1.agruparNoticias(), "\nEntidad1\n"
            "*[titulo noticia 1]\n"
            "\n"
            "Entidad2\n"
            "*[titulo noticia 2]\n"
            "*[titulo noticia 3]\n"
            "*[titulo noticia 4]\n");
}

TEST(Analizador, given2NoticiasConEntidadesDiferentes_y_soloLaPrimeraAgregableConLaSegunda_whenAgruparNoticiasGeneral_then_UnGrupoEsObtenido)
{
    Analizador a1;
    auto noticia1 = std::make_shared<NoticiaMock>();
    auto noticia2 = std::make_shared<NoticiaMock>();
    EXPECT_CALL(*noticia1, getMasFrecuente()).WillRepeatedly(Return(EntidadNombrada("Entidad1", 2)));
    EXPECT_CALL(*noticia2, getMasFrecuente()).WillRepeatedly(Return(EntidadNombrada("Entidad2", 2)));
    EXPECT_CALL(*noticia1, getTitulo()).WillRepeatedly(Return("titulo noticia 1"));
    EXPECT_CALL(*noticia2, getTitulo()).WillRepeatedly(Return("titulo noticia 2"));
    EXPECT_CALL(*noticia1, esAgrupable(static_cast<std::shared_ptr<NoticiaInterface>>(noticia2))).WillRepeatedly(Return(true));
    EXPECT_CALL(*noticia2, esAgrupable(static_cast<std::shared_ptr<NoticiaInterface>>(noticia1))).WillRepeatedly(Return(false));
    a1.addNoticia(noticia1);
    a1.addNoticia(noticia2);
    EXPECT_EQ(a1.agruparNoticiasGeneral(), "\nEntidad1 Entidad2\n"
            "   *[titulo noticia 1]\n"
            "   *[titulo noticia 2]\n");
}