#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Noticia.h"
#include "AgrupadorNoticias.h"
#include "NoticiaMock.h"

using namespace testing;

TEST(Agrupador, givenDosNoticiasAgrupablesPorEntidadMasFrecuente_whenPreguntarAlAgregadorSiSonAgregablesPorEntidad_then_trueEsRetornado)
{
    std::shared_ptr<NoticiaTextoMock> n1 = std::make_shared<NoticiaTextoMock>();
    std::shared_ptr<NoticiaTextoMock> n2 = std::make_shared<NoticiaTextoMock>();
    EXPECT_CALL(*n1, getEntidadMasFrecuente()).WillRepeatedly(Return("Entidad1"));
    EXPECT_CALL(*n2, getEntidadMasFrecuente()).WillRepeatedly(Return("Entidad1"));
    AgrupadorNoticias agregadorNoticias;
    EXPECT_EQ(agregadorNoticias.isAgregableEntidadMasFrecuente(static_cast<std::shared_ptr<Noticia>>(n1), static_cast<std::shared_ptr<Noticia>>(n2)), true);
}

TEST(Agrupador, givenDosNoticiasAgrupablesPorEntidadMasFrecuente_whenPreguntarAlAgregadorSiSonAgregablesPorTematica_then_trueEsRetornado)
{
    std::shared_ptr<NoticiaTextoMock> n1 = std::make_shared<NoticiaTextoMock>();
    std::shared_ptr<NoticiaTextoMock> n2 = std::make_shared<NoticiaTextoMock>();
    EXPECT_CALL(*n1, getEntidadMasFrecuente()).WillRepeatedly(Return("Entidad1"));
    EXPECT_CALL(*n2, getEntidadMasFrecuente()).WillRepeatedly(Return("Entidad1"));
    AgrupadorNoticias agregadorNoticias;
    EXPECT_EQ(agregadorNoticias.isAgregable(static_cast<std::shared_ptr<Noticia>>(n1), static_cast<std::shared_ptr<Noticia>>(n2)), true);
}

TEST(Agrupador, givenDosNoticiasSinCompartirEntidadMasFrecuenteEnTitulo_whenPreguntarAlAgregadorSiSonAgregablesPorEntidad_then_falseEsRetornado)
{
    std::shared_ptr<NoticiaTextoMock> n1 = std::make_shared<NoticiaTextoMock>();
    std::shared_ptr<NoticiaTextoMock> n2 = std::make_shared<NoticiaTextoMock>();
    EXPECT_CALL(*n1, getEntidadMasFrecuente()).WillRepeatedly(Return("Entidad1"));
    EXPECT_CALL(*n2, getEntidadMasFrecuente()).WillRepeatedly(Return("Entidad2"));
    AgrupadorNoticias agregadorNoticias;
    ASSERT_EQ(agregadorNoticias.isAgregableEntidadMasFrecuente(static_cast<std::shared_ptr<Noticia>>(n1), static_cast<std::shared_ptr<Noticia>>(n2)), false);
}

TEST(Agrupador, givenDosNoticiasTalesQueCumplenLaCondicionDeTematica_whenPreguntarAlAgregadorSiSonAgregables_then_trueEsRetornado)
{
    std::shared_ptr<NoticiaTextoMock> n1 = std::make_shared<NoticiaTextoMock>();
    std::shared_ptr<NoticiaTextoMock> n2 = std::make_shared<NoticiaTextoMock>();
    EXPECT_CALL(*n1, getEntidadMasFrecuente()).WillRepeatedly(Return("E1"));
    EXPECT_CALL(*n2, getEntidadMasFrecuente()).WillRepeatedly(Return("Entidad2"));
    EXPECT_CALL(*n1, getTitulo()).WillRepeatedly(Return("titulo"));
    EXPECT_CALL(*n2, getTitulo()).WillRepeatedly(Return("E1 y otras palabras")); //noticia 2 tiene la entidadNombrada más grecuente de noticia 1 en su título
    std::set<std::string> entidadesNoticia1;
    std::set<std::string> entidadesNoticia2;
    std::set<std::string> entidadesRelevantesNoticia1;
    std::set<std::string> entidadesRelevantesNoticia2;
    //10 entidades a noticia 1 de las cuales todas son relevantes, y un 30% son entidades de noticia 2
    for (int i = 0; i< 10; i++)
    {
        entidadesNoticia1.insert(std::string("E") + std::to_string(i));
        entidadesRelevantesNoticia1.insert(std::string("E") + std::to_string(i));
        if (i<3)
            entidadesNoticia2.insert(std::string("E") + std::to_string(i));
    }
    EXPECT_CALL(*n1, getEntidades()).WillRepeatedly(Return(entidadesNoticia1));
    EXPECT_CALL(*n2, getEntidades()).WillRepeatedly(Return(entidadesNoticia2));
    EXPECT_CALL(*n1, getEntidadesRelevantes()).WillRepeatedly(Return(entidadesRelevantesNoticia1));
    EXPECT_CALL(*n2, getEntidadesRelevantes()).WillRepeatedly(Return(entidadesRelevantesNoticia2));
    AgrupadorNoticias agregadorNoticias;
    EXPECT_EQ(agregadorNoticias.isAgregable(static_cast<std::shared_ptr<Noticia>>(n1), static_cast<std::shared_ptr<Noticia>>(n2)), true);
    EXPECT_EQ(agregadorNoticias.isAgregable(static_cast<std::shared_ptr<Noticia>>(n2), static_cast<std::shared_ptr<Noticia>>(n1)), true);
}

TEST(Agrupador, givenDosNoticiasTalesQueCumplenLaCondicionDe30porcientoPeroNoTitulo_whenPreguntarAlAgregadorSiSonAgregables_then_trueEsRetornado)
{
    std::shared_ptr<NoticiaTextoMock> n1 = std::make_shared<NoticiaTextoMock>();
    std::shared_ptr<NoticiaTextoMock> n2 = std::make_shared<NoticiaTextoMock>();
    EXPECT_CALL(*n1, getEntidadMasFrecuente()).WillRepeatedly(Return("Entidad1"));
    EXPECT_CALL(*n2, getEntidadMasFrecuente()).WillRepeatedly(Return("Entidad2"));
    EXPECT_CALL(*n1, getTitulo()).WillRepeatedly(Return("titulo"));
    EXPECT_CALL(*n2, getTitulo()).WillRepeatedly(Return("E1 y otras palabras")); //noticia 2 NO tiene la entidadNombrada más grecuente de noticia 1 en su título
    std::set<std::string> entidadesNoticia1;
    std::set<std::string> entidadesNoticia2;
    std::set<std::string> entidadesRelevantesNoticia1;
    std::set<std::string> entidadesRelevantesNoticia2;
    //10 entidades a noticia 1 de las cuales todas son relevantes, y un 30% son entidades de noticia 2
    for (int i = 0; i< 10; i++)
    {
        entidadesNoticia1.insert(std::string("E") + std::to_string(i));
        entidadesRelevantesNoticia1.insert(std::string("E") + std::to_string(i));
        if (i<3)
            entidadesNoticia2.insert(std::string("E") + std::to_string(i));
    }
    EXPECT_CALL(*n1, getEntidades()).WillRepeatedly(Return(entidadesNoticia1));
    EXPECT_CALL(*n2, getEntidades()).WillRepeatedly(Return(entidadesNoticia2));
    EXPECT_CALL(*n1, getEntidadesRelevantes()).WillRepeatedly(Return(entidadesRelevantesNoticia1));
    EXPECT_CALL(*n2, getEntidadesRelevantes()).WillRepeatedly(Return(entidadesRelevantesNoticia2));
    AgrupadorNoticias agregadorNoticias;
    EXPECT_EQ(agregadorNoticias.isAgregable(static_cast<std::shared_ptr<Noticia>>(n1), static_cast<std::shared_ptr<Noticia>>(n2)), false);
    EXPECT_EQ(agregadorNoticias.isAgregable(static_cast<std::shared_ptr<Noticia>>(n2), static_cast<std::shared_ptr<Noticia>>(n1)), false);
}

TEST(Agrupador, givenDosNoticiasTalesQueCumplenLaCondicionDeTituloPeroNoLaDe30porciento_whenPreguntarAlAgregadorSiSonAgregables_then_falseEsRetornado)
{
    std::shared_ptr<NoticiaTextoMock> n1 = std::make_shared<NoticiaTextoMock>();
    std::shared_ptr<NoticiaTextoMock> n2 = std::make_shared<NoticiaTextoMock>();
    EXPECT_CALL(*n1, getEntidadMasFrecuente()).WillRepeatedly(Return("E1"));
    EXPECT_CALL(*n2, getEntidadMasFrecuente()).WillRepeatedly(Return("Entidad2"));
    EXPECT_CALL(*n1, getTitulo()).WillRepeatedly(Return("titulo"));
    EXPECT_CALL(*n2, getTitulo()).WillRepeatedly(Return("E1 y otras palabras")); //noticia 2 tiene la entidadNombrada más grecuente de noticia 1 en su título
    std::set<std::string> entidadesNoticia1;
    std::set<std::string> entidadesNoticia2;
    std::set<std::string> entidadesRelevantesNoticia1;
    std::set<std::string> entidadesRelevantesNoticia2;
    //10 entidades a noticia 1 de las cuales todas son relevantes, y un 20% son entidades de noticia 2
    for (int i = 0; i< 10; i++)
    {
        entidadesNoticia1.insert(std::string("E") + std::to_string(i));
        entidadesRelevantesNoticia1.insert(std::string("E") + std::to_string(i));
        if (i<2)
            entidadesNoticia2.insert(std::string("E") + std::to_string(i));
    }
    EXPECT_CALL(*n1, getEntidades()).WillRepeatedly(Return(entidadesNoticia1));
    EXPECT_CALL(*n2, getEntidades()).WillRepeatedly(Return(entidadesNoticia2));
    EXPECT_CALL(*n1, getEntidadesRelevantes()).WillRepeatedly(Return(entidadesRelevantesNoticia1));
    EXPECT_CALL(*n2, getEntidadesRelevantes()).WillRepeatedly(Return(entidadesRelevantesNoticia2));
    AgrupadorNoticias agregadorNoticias;
    EXPECT_EQ(agregadorNoticias.isAgregable(static_cast<std::shared_ptr<Noticia>>(n1), static_cast<std::shared_ptr<Noticia>>(n2)), false);
    EXPECT_EQ(agregadorNoticias.isAgregable(static_cast<std::shared_ptr<Noticia>>(n2), static_cast<std::shared_ptr<Noticia>>(n1)), false);
}

TEST(Agrupador, givenDosNoticiasTalesQueNoCumplenLaCondicionDeTituloNiLaDe30porciento_whenPreguntarAlAgregadorSiSonAgregables_then_falseEsRetornado)
{
    std::shared_ptr<NoticiaTextoMock> n1 = std::make_shared<NoticiaTextoMock>();
    std::shared_ptr<NoticiaTextoMock> n2 = std::make_shared<NoticiaTextoMock>();
    EXPECT_CALL(*n1, getEntidadMasFrecuente()).WillRepeatedly(Return("Entidad1"));
    EXPECT_CALL(*n2, getEntidadMasFrecuente()).WillRepeatedly(Return("Entidad2"));
    EXPECT_CALL(*n1, getTitulo()).WillRepeatedly(Return("titulo"));
    EXPECT_CALL(*n2, getTitulo()).WillRepeatedly(Return("E1 y otras palabras")); //noticia 2 tiene la entidadNombrada más grecuente de noticia 1 en su título
    std::set<std::string> entidadesNoticia1;
    std::set<std::string> entidadesNoticia2;
    std::set<std::string> entidadesRelevantesNoticia1;
    std::set<std::string> entidadesRelevantesNoticia2;
    //10 entidades a noticia 1 de las cuales todas son relevantes, y un 20% son entidades de noticia 2
    for (int i = 0; i< 10; i++)
    {
        entidadesNoticia1.insert(std::string("E") + std::to_string(i));
        entidadesRelevantesNoticia1.insert(std::string("E") + std::to_string(i));
        if (i<2)
            entidadesNoticia2.insert(std::string("E") + std::to_string(i));
    }
    EXPECT_CALL(*n1, getEntidades()).WillRepeatedly(Return(entidadesNoticia1));
    EXPECT_CALL(*n2, getEntidades()).WillRepeatedly(Return(entidadesNoticia2));
    EXPECT_CALL(*n1, getEntidadesRelevantes()).WillRepeatedly(Return(entidadesRelevantesNoticia1));
    EXPECT_CALL(*n2, getEntidadesRelevantes()).WillRepeatedly(Return(entidadesRelevantesNoticia2));
    AgrupadorNoticias agregadorNoticias;
    EXPECT_EQ(agregadorNoticias.isAgregable(static_cast<std::shared_ptr<Noticia>>(n1), static_cast<std::shared_ptr<Noticia>>(n2)), false);
    EXPECT_EQ(agregadorNoticias.isAgregable(static_cast<std::shared_ptr<Noticia>>(n2), static_cast<std::shared_ptr<Noticia>>(n1)), false);
}

TEST(Agrupador, givenDosTuitsAgrupablesPorEntidadMasFrecuente_whenPreguntarAlAgregadorSiSonAgregablesPorEntidad_then_trueEsRetornado)
{
    std::shared_ptr<TuitMock> n1 = std::make_shared<TuitMock>();
    std::shared_ptr<TuitMock> n2 = std::make_shared<TuitMock>();
    EXPECT_CALL(*n1, getEntidadMasFrecuente()).WillRepeatedly(Return("Entidad1"));
    EXPECT_CALL(*n2, getEntidadMasFrecuente()).WillRepeatedly(Return("Entidad1"));
    AgrupadorNoticias agregadorNoticias;
    EXPECT_EQ(agregadorNoticias.isAgregableEntidadMasFrecuente(static_cast<std::shared_ptr<Tuit>>(n1), static_cast<std::shared_ptr<Tuit>>(n2)), true);
}

TEST(Agrupador, givenDosTuitsNoAgrupablesPorEntidadMasFrecuente_whenPreguntarAlAgregadorSiSonAgregablesPorEntidad_then_falseEsRetornado)
{
    std::shared_ptr<TuitMock> n1 = std::make_shared<TuitMock>();
    std::shared_ptr<TuitMock> n2 = std::make_shared<TuitMock>();
    EXPECT_CALL(*n1, getEntidadMasFrecuente()).WillRepeatedly(Return("Entidad1"));
    EXPECT_CALL(*n2, getEntidadMasFrecuente()).WillRepeatedly(Return("Entidad2"));
    AgrupadorNoticias agregadorNoticias;
    EXPECT_EQ(agregadorNoticias.isAgregableEntidadMasFrecuente(static_cast<std::shared_ptr<Tuit>>(n1), static_cast<std::shared_ptr<Tuit>>(n2)), false);
}

TEST(Agrupador, givenDosTuitsAgrupablesPorEntidadMasFrecuente_whenPreguntarAlAgregadorSiSonAgregablesPorTematica_then_trueEsRetornado)
{
    std::shared_ptr<TuitMock> n1 = std::make_shared<TuitMock>();
    std::shared_ptr<TuitMock> n2 = std::make_shared<TuitMock>();
    EXPECT_CALL(*n1, getEntidadMasFrecuente()).WillRepeatedly(Return("Entidad1"));
    EXPECT_CALL(*n2, getEntidadMasFrecuente()).WillRepeatedly(Return("Entidad1"));
    AgrupadorNoticias agregadorNoticias;
    EXPECT_EQ(agregadorNoticias.isAgregable(static_cast<std::shared_ptr<Tuit>>(n1), static_cast<std::shared_ptr<Tuit>>(n2)), true);
}

TEST(Agrupador, givenDosTuitConDistintaEntidadMasFrecuentePeroCumpliendoCondicionDeAgrupacionTematica_whenPreguntarAlAgregadorSiSonAgregables_then_trueEsRetornado)
{
    std::shared_ptr<TuitMock> n1 = std::make_shared<TuitMock>();
    std::shared_ptr<TuitMock> n2 = std::make_shared<TuitMock>();
    std::set<std::string> entidadesNoticia1;
    std::set<std::string> entidadesNoticia2;
    entidadesNoticia1.insert("E1");
    entidadesNoticia1.insert("E2");
    entidadesNoticia2.insert("E0");
    entidadesNoticia2.insert("E1");
    EXPECT_CALL(*n1, getEntidadMasFrecuente()).WillRepeatedly(Return("Entidad1"));
    EXPECT_CALL(*n2, getEntidadMasFrecuente()).WillRepeatedly(Return("Entidad2"));
    EXPECT_CALL(*n1, getEntidades()).WillRepeatedly(Return(entidadesNoticia1));
    EXPECT_CALL(*n2, getEntidades()).WillRepeatedly(Return(entidadesNoticia2));
    AgrupadorNoticias agregadorNoticias;
    EXPECT_EQ(agregadorNoticias.isAgregable(static_cast<std::shared_ptr<Tuit>>(n1), static_cast<std::shared_ptr<Tuit>>(n2)), true);
}

TEST(Agrupador, givenTuit_y_NoticiaAgrupablesPorEntidadMasFrecuente_whenPreguntarAlAgregadorSiSonAgregablesPorEntidad_then_trueEsRetornado)
{
    std::shared_ptr<TuitMock> n1 = std::make_shared<TuitMock>();
    std::shared_ptr<NoticiaTextoMock> n2 = std::make_shared<NoticiaTextoMock>();
    EXPECT_CALL(*n1, getEntidadMasFrecuente()).WillRepeatedly(Return("Entidad1"));
    EXPECT_CALL(*n2, getEntidadMasFrecuente()).WillRepeatedly(Return("Entidad1"));
    AgrupadorNoticias agregadorNoticias;
    EXPECT_EQ(agregadorNoticias.isAgregableEntidadMasFrecuente(static_cast<std::shared_ptr<Tuit>>(n1), static_cast<std::shared_ptr<Noticia>>(n2)), true);
    EXPECT_EQ(agregadorNoticias.isAgregableEntidadMasFrecuente(static_cast<std::shared_ptr<Noticia>>(n2), static_cast<std::shared_ptr<Tuit>>(n1)), true);
}

TEST(Agrupador, givenTuit_y_NoticiaNoAgrupablesPorEntidadMasFrecuente_whenPreguntarAlAgregadorSiSonAgregablesPorEntidad_then_trueEsRetornado)
{
    std::shared_ptr<TuitMock> n1 = std::make_shared<TuitMock>();
    std::shared_ptr<NoticiaTextoMock> n2 = std::make_shared<NoticiaTextoMock>();
    EXPECT_CALL(*n1, getEntidadMasFrecuente()).WillRepeatedly(Return("Entidad1"));
    EXPECT_CALL(*n2, getEntidadMasFrecuente()).WillRepeatedly(Return("Entidad2"));
    AgrupadorNoticias agregadorNoticias;
    EXPECT_EQ(agregadorNoticias.isAgregableEntidadMasFrecuente(static_cast<std::shared_ptr<Tuit>>(n1), static_cast<std::shared_ptr<Noticia>>(n2)), false);
    EXPECT_EQ(agregadorNoticias.isAgregableEntidadMasFrecuente(static_cast<std::shared_ptr<Noticia>>(n2), static_cast<std::shared_ptr<Tuit>>(n1)), false);
}

TEST(Agrupador, givenTuit_y_NoticiaAgrupablesPorEntidadMasFrecuente_whenPreguntarAlAgregadorSiSonAgregablesPorTematica_then_trueEsRetornado)
{
    std::shared_ptr<TuitMock> n1 = std::make_shared<TuitMock>();
    std::shared_ptr<NoticiaTextoMock> n2 = std::make_shared<NoticiaTextoMock>();
    EXPECT_CALL(*n1, getEntidadMasFrecuente()).WillRepeatedly(Return("Entidad1"));
    EXPECT_CALL(*n2, getEntidadMasFrecuente()).WillRepeatedly(Return("Entidad1"));
    AgrupadorNoticias agregadorNoticias;
    EXPECT_EQ(agregadorNoticias.isAgregable(static_cast<std::shared_ptr<Tuit>>(n1), static_cast<std::shared_ptr<Noticia>>(n2)), true);
    EXPECT_EQ(agregadorNoticias.isAgregable(static_cast<std::shared_ptr<Noticia>>(n2), static_cast<std::shared_ptr<Tuit>>(n1)), true);
}

TEST(Agrupador, givenTuit_y_NoticiaConDistintaEntidadMasFrecuentePeroCumpliendoCondicionDeAgrupacionTematica_whenPreguntarAlAgregadorSiSonAgregables_then_trueEsRetornado)
{
    std::shared_ptr<TuitMock> n1 = std::make_shared<TuitMock>();
    std::shared_ptr<NoticiaTextoMock> n2 = std::make_shared<NoticiaTextoMock>();
    std::set<std::string> entidadesNoticia1;
    std::set<std::string> entidadesNoticia2;
    entidadesNoticia1.insert("E1");
    entidadesNoticia1.insert("E2");
    entidadesNoticia2.insert("E0");
    entidadesNoticia2.insert("E1");
    EXPECT_CALL(*n1, getEntidadMasFrecuente()).WillRepeatedly(Return("Entidad1"));
    EXPECT_CALL(*n2, getEntidadMasFrecuente()).WillRepeatedly(Return("E1"));
    EXPECT_CALL(*n1, getEntidades()).WillRepeatedly(Return(entidadesNoticia1));
    EXPECT_CALL(*n2, getEntidades()).WillRepeatedly(Return(entidadesNoticia2));
    AgrupadorNoticias agregadorNoticias;
    EXPECT_EQ(agregadorNoticias.isAgregable(static_cast<std::shared_ptr<Tuit>>(n1), static_cast<std::shared_ptr<Noticia>>(n2)), true);
    EXPECT_EQ(agregadorNoticias.isAgregable(static_cast<std::shared_ptr<Noticia>>(n2), static_cast<std::shared_ptr<Tuit>>(n1)), true);
}

TEST(Agrupador, givenTuit_y_NoticiaNoAgrupablesPorTematica_whenPreguntarAlAgregadorSiSonAgregables_then_falseEsRetornado)
{
    std::shared_ptr<TuitMock> n1 = std::make_shared<TuitMock>();
    std::shared_ptr<NoticiaTextoMock> n2 = std::make_shared<NoticiaTextoMock>();
    std::set<std::string> entidadesNoticia1;
    std::set<std::string> entidadesNoticia2;
    entidadesNoticia1.insert("E1");
    entidadesNoticia1.insert("E2");
    entidadesNoticia2.insert("E0");
    entidadesNoticia2.insert("E1");
    EXPECT_CALL(*n1, getEntidadMasFrecuente()).WillRepeatedly(Return("Entidad1"));
    EXPECT_CALL(*n2, getEntidadMasFrecuente()).WillRepeatedly(Return("Entidad2"));
    EXPECT_CALL(*n1, getEntidades()).WillRepeatedly(Return(entidadesNoticia1));
    EXPECT_CALL(*n2, getEntidades()).WillRepeatedly(Return(entidadesNoticia2));
    AgrupadorNoticias agregadorNoticias;
    EXPECT_EQ(agregadorNoticias.isAgregable(static_cast<std::shared_ptr<Tuit>>(n1), static_cast<std::shared_ptr<Noticia>>(n2)), false);
    EXPECT_EQ(agregadorNoticias.isAgregable(static_cast<std::shared_ptr<Noticia>>(n2), static_cast<std::shared_ptr<Tuit>>(n1)), false);
}