#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "NoticiaMock.h"
#include "Analizador.h"
#include "AgrupadorNoticiasMock.h"

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
    ASSERT_EQ(noticias.size(), 1);
    EXPECT_EQ(noticias.front()->getTitulo(), "lista de palabras del alfabeto radiofónico");
}

TEST(Analizador, given4NoticiasCon2EntidadesDiferentes_whenAgruparNoticiasPorEntidadMasFrecuente_then_DosGruposSonObtenidos)
{
    Analizador a1;
    auto noticia1 = std::make_shared<NoticiaMock>();
    auto noticia2 = std::make_shared<NoticiaMock>();
    auto noticia3 = std::make_shared<NoticiaMock>();
    auto noticia4 = std::make_shared<NoticiaMock>();
    EXPECT_CALL(*noticia1, getEntidadMasFrecuente()).WillRepeatedly(Return("Entidad1"));
    EXPECT_CALL(*noticia2, getEntidadMasFrecuente()).WillRepeatedly(Return("Entidad2"));
    EXPECT_CALL(*noticia3, getEntidadMasFrecuente()).WillRepeatedly(Return("Entidad2"));
    EXPECT_CALL(*noticia4, getEntidadMasFrecuente()).WillRepeatedly(Return("Entidad2"));
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
    EXPECT_EQ(a1.agruparNoticias(), "Entidad1 \n"
            "   *[titulo noticia 1]\n"
            "\n"
            "Entidad2 \n"
            "   *[titulo noticia 2]\n"
            "   *[titulo noticia 3]\n"
            "   *[titulo noticia 4]\n\n");
}

TEST(Analizador, given2NoticiasSoloAgrupablesPorTematica_whenAgruparNoticiasGeneral_then_UnGrupoEsObtenido)
{
    auto agrupador = std::make_shared<AgrupadorNoticiasMock>();
    Analizador a1;
    a1.setAgrupador(agrupador);
    auto noticia1 = std::make_shared<NoticiaMock>();
    auto noticia2 = std::make_shared<NoticiaMock>();
    EXPECT_CALL(*noticia1, getEntidadMasFrecuente()).WillRepeatedly(Return("Entidad1"));
    EXPECT_CALL(*noticia2, getEntidadMasFrecuente()).WillRepeatedly(Return("Entidad2"));
    EXPECT_CALL(*noticia1, getTitulo()).WillRepeatedly(Return("titulo noticia 1"));
    EXPECT_CALL(*noticia2, getTitulo()).WillRepeatedly(Return("titulo noticia 2"));
    EXPECT_CALL(*agrupador, isAgregableEntidadMasFrecuente(static_cast<std::shared_ptr<NoticiaInterface>>(noticia1), static_cast<std::shared_ptr<NoticiaInterface>>(noticia2))).WillRepeatedly(Return(false));

    EXPECT_CALL(*agrupador, isAgregable(static_cast<std::shared_ptr<NoticiaInterface>>(noticia1), static_cast<std::shared_ptr<NoticiaInterface>>(noticia2))).WillRepeatedly(Return(true));
    a1.addNoticia(noticia1);
    a1.addNoticia(noticia2);
    EXPECT_EQ(a1.agruparNoticiasGeneral(), "Entidad1 Entidad2 \n"
            "   *[titulo noticia 1]\n"
            "   *[titulo noticia 2]\n\n");
    Mock::AllowLeak(noticia1.get());
    Mock::AllowLeak(noticia2.get());
}

TEST(Analizador, given2NoticiasNoAgrupables_whenAgruparNoticiasGeneral_then_DosGruposSonObtenidos)
{
    auto agrupador = std::make_shared<AgrupadorNoticiasMock>();
    Analizador a1;
    a1.setAgrupador(agrupador);
    auto noticia1 = std::make_shared<NoticiaMock>();
    auto noticia2 = std::make_shared<NoticiaMock>();
    EXPECT_CALL(*noticia1, getEntidadMasFrecuente()).WillRepeatedly(Return("Entidad1"));
    EXPECT_CALL(*noticia2, getEntidadMasFrecuente()).WillRepeatedly(Return("Entidad2"));
    EXPECT_CALL(*noticia1, getTitulo()).WillRepeatedly(Return("titulo noticia 1"));
    EXPECT_CALL(*noticia2, getTitulo()).WillRepeatedly(Return("titulo noticia 2"));
    EXPECT_CALL(*agrupador, isAgregableEntidadMasFrecuente(static_cast<std::shared_ptr<NoticiaInterface>>(noticia1), static_cast<std::shared_ptr<NoticiaInterface>>(noticia2))).WillRepeatedly(Return(false));
    EXPECT_CALL(*agrupador, isAgregableEntidadMasFrecuente(static_cast<std::shared_ptr<NoticiaInterface>>(noticia2), static_cast<std::shared_ptr<NoticiaInterface>>(noticia1))).WillRepeatedly(Return(false));
    EXPECT_CALL(*agrupador, isAgregable(static_cast<std::shared_ptr<NoticiaInterface>>(noticia1), static_cast<std::shared_ptr<NoticiaInterface>>(noticia2))).WillRepeatedly(Return(false));
    EXPECT_CALL(*agrupador, isAgregable(static_cast<std::shared_ptr<NoticiaInterface>>(noticia2), static_cast<std::shared_ptr<NoticiaInterface>>(noticia1))).WillRepeatedly(Return(false));
    a1.addNoticia(noticia1);
    a1.addNoticia(noticia2);
    EXPECT_EQ(a1.agruparNoticiasGeneral(), "Entidad1 \n"
            "   *[titulo noticia 1]\n"
            "\nEntidad2 \n"
            "   *[titulo noticia 2]\n\n");
    Mock::AllowLeak(noticia1.get());
    Mock::AllowLeak(noticia2.get());
}

TEST(Analizador, given3NoticiasConEntidadesDiferentes_y_1AgrupableCon3y3Con2_whenAgruparNoticiasGenerasl_then_UnGrupoEsObtenido)
{
    auto agrupador = std::make_shared<AgrupadorNoticiasMock>();
    Analizador a1;
    a1.setAgrupador(agrupador);
    auto noticia1 = std::make_shared<NoticiaMock>();
    auto noticia2 = std::make_shared<NoticiaMock>();
    auto noticia3 = std::make_shared<NoticiaMock>();
    EXPECT_CALL(*noticia1, getEntidadMasFrecuente()).WillRepeatedly(Return("Entidad1"));
    EXPECT_CALL(*noticia2, getEntidadMasFrecuente()).WillRepeatedly(Return("Entidad2"));
    EXPECT_CALL(*noticia3, getEntidadMasFrecuente()).WillRepeatedly(Return("Entidad3"));
    EXPECT_CALL(*noticia1, getTitulo()).WillRepeatedly(Return("titulo noticia 1"));
    EXPECT_CALL(*noticia2, getTitulo()).WillRepeatedly(Return("titulo noticia 2"));
    EXPECT_CALL(*noticia3, getTitulo()).WillRepeatedly(Return("titulo noticia 3"));

    EXPECT_CALL(*agrupador, isAgregableEntidadMasFrecuente(static_cast<std::shared_ptr<NoticiaInterface>>(noticia1), static_cast<std::shared_ptr<NoticiaInterface>>(noticia2))).WillRepeatedly(Return(false));
    EXPECT_CALL(*agrupador, isAgregableEntidadMasFrecuente(static_cast<std::shared_ptr<NoticiaInterface>>(noticia2), static_cast<std::shared_ptr<NoticiaInterface>>(noticia1))).WillRepeatedly(Return(false));
    EXPECT_CALL(*agrupador, isAgregableEntidadMasFrecuente(static_cast<std::shared_ptr<NoticiaInterface>>(noticia1), static_cast<std::shared_ptr<NoticiaInterface>>(noticia3))).WillRepeatedly(Return(false));
    EXPECT_CALL(*agrupador, isAgregableEntidadMasFrecuente(static_cast<std::shared_ptr<NoticiaInterface>>(noticia3), static_cast<std::shared_ptr<NoticiaInterface>>(noticia1))).WillRepeatedly(Return(false));
    EXPECT_CALL(*agrupador, isAgregableEntidadMasFrecuente(static_cast<std::shared_ptr<NoticiaInterface>>(noticia3), static_cast<std::shared_ptr<NoticiaInterface>>(noticia2))).WillRepeatedly(Return(false));
    EXPECT_CALL(*agrupador, isAgregableEntidadMasFrecuente(static_cast<std::shared_ptr<NoticiaInterface>>(noticia2), static_cast<std::shared_ptr<NoticiaInterface>>(noticia3))).WillRepeatedly(Return(false));

    EXPECT_CALL(*agrupador, isAgregable(static_cast<std::shared_ptr<NoticiaInterface>>(noticia1), static_cast<std::shared_ptr<NoticiaInterface>>(noticia2))).WillRepeatedly(Return(false));
    EXPECT_CALL(*agrupador, isAgregable(static_cast<std::shared_ptr<NoticiaInterface>>(noticia2), static_cast<std::shared_ptr<NoticiaInterface>>(noticia1))).WillRepeatedly(Return(false));
    EXPECT_CALL(*agrupador, isAgregable(static_cast<std::shared_ptr<NoticiaInterface>>(noticia1), static_cast<std::shared_ptr<NoticiaInterface>>(noticia3))).WillRepeatedly(Return(true));
    EXPECT_CALL(*agrupador, isAgregable(static_cast<std::shared_ptr<NoticiaInterface>>(noticia3), static_cast<std::shared_ptr<NoticiaInterface>>(noticia1))).WillRepeatedly(Return(true));
    EXPECT_CALL(*agrupador, isAgregable(static_cast<std::shared_ptr<NoticiaInterface>>(noticia3), static_cast<std::shared_ptr<NoticiaInterface>>(noticia2))).WillRepeatedly(Return(true));
    EXPECT_CALL(*agrupador, isAgregable(static_cast<std::shared_ptr<NoticiaInterface>>(noticia2), static_cast<std::shared_ptr<NoticiaInterface>>(noticia3))).WillRepeatedly(Return(true));

    a1.addNoticia(noticia1);
    a1.addNoticia(noticia2);
    a1.addNoticia(noticia3);
    EXPECT_EQ(a1.agruparNoticiasGeneral(), "Entidad1 Entidad2 Entidad3 \n"
            "   *[titulo noticia 1]\n"
            "   *[titulo noticia 3]\n"
            "   *[titulo noticia 2]\n\n");
    Mock::AllowLeak(noticia1.get());
    Mock::AllowLeak(noticia2.get());
    Mock::AllowLeak(noticia3.get());
}