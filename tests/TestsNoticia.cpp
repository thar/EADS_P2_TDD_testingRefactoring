#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Noticia.h"

TEST(Noticia, givenDatosParaCreacionDeNoticiaConUnaSolaEntidad_whenObtenerDatosDeLaInterfazPublicaDeNoticia_then_DatosCorrectosSonObtenidos)
{
    Noticia n("Título de la noticia", "Ahora viene el cuerpo de la noticia ", "dataTests/ES_stopList_test1.txt");
    EXPECT_EQ(n.getCuerpo(), "Ahora viene el cuerpo de la noticia ");
    EXPECT_EQ(n.getTitulo(), "Título de la noticia");
    auto palabrasReservadas = n.getPalabrasReservadas();
    EXPECT_EQ(palabrasReservadas.size(), 4);
    auto entidadesEncontradas = n.getEntidades();
    ASSERT_EQ(entidadesEncontradas.size(), 1);
    EXPECT_EQ(entidadesEncontradas.front().getEntidadNombrada(), "Ahora");
    EXPECT_EQ(n.getMasFrecuente().getEntidadNombrada(), "Ahora");
    EXPECT_EQ(n.getEntidadesRelevantes().front().getEntidadNombrada(), "Ahora");
}

TEST(Noticia, givenDatosParaCreacionDeNoticiaConUnaSolaEntidad_whenConstructorSinParametros_y_ObtenerDatosDeLaInterfazPublicaDeNoticia_then_DatosCorrectosSonObtenidos)
{
    Noticia n;
    n.setTitulo("Título de la noticia ");
    n.setCuerpo("Ahora viene el cuerpo de la noticia ");
    n.setPalabrasReservadas("dataTests/ES_stopList_test1.txt");
    n.actualizar();
    EXPECT_EQ(n.getCuerpo(), "Ahora viene el cuerpo de la noticia ");
    EXPECT_EQ(n.getTitulo(), "Título de la noticia ");
    auto palabrasReservadas = n.getPalabrasReservadas();
    EXPECT_EQ(palabrasReservadas.size(), 4);
    auto entidadesEncontradas = n.getEntidades();
    ASSERT_EQ(entidadesEncontradas.size(), 1);
    EXPECT_EQ(entidadesEncontradas.front().getEntidadNombrada(), "Ahora");
    EXPECT_EQ(n.getMasFrecuente().getEntidadNombrada(), "Ahora");
    EXPECT_EQ(n.getEntidadesRelevantes().front().getEntidadNombrada(), "Ahora");
}

TEST(Noticia, givenNoticiaConEntidadesSoloPertenecientes_a_laListaDePalabrasReservadas_whenPreguntarPorEntidadesEncontradas_then_CeroSonDevueltas)
{
    Noticia n("Título de la noticia ", "Uno Dos Tres Cuatro ", "dataTests/ES_stopList_test1.txt");
    auto entidadesEncontradas = n.getEntidades();
    EXPECT_EQ(entidadesEncontradas.size(), 0);
    n.setCuerpo("Uno Dos Entidad Tres Cuatro ");
    n.actualizar();
    entidadesEncontradas = n.getEntidades();
    ASSERT_EQ(entidadesEncontradas.size(), 1);
    EXPECT_EQ(entidadesEncontradas.front().getEntidadNombrada(), "Entidad");
    EXPECT_EQ(n.getMasFrecuente().getEntidadNombrada(), "Entidad");
}

TEST(Noticia, givenNoticiaConEntidadesSoloPertenecientes_a_laListaDePalabrasReservadasConFrecuenciaMayorQueUno_whenPreguntarPorEntidadesEncontradas_then_CeroSonDevueltas)
{
    Noticia n("Título de la noticia ", "Cuatro Uno uno Uno Tres Dos Tres Dos Cuatro Uno Cuatro ", "dataTests/ES_stopList_test1.txt");
    auto entidadesEncontradas = n.getEntidades();
    EXPECT_EQ(entidadesEncontradas.size(), 0);
}

TEST(Noticia, givenNoticiaConEntidadConFrecuencia3_whenPreguntarPorEntidadesEncontradas_then_UnaConFrecuenci3EsDevuelta)
{
    Noticia n("Título de la noticia ", "Prueba prueba Prueba prueba Prueba ", "dataTests/ES_stopList_test1.txt");
    auto entidadesEncontradas = n.getEntidades();
    ASSERT_EQ(entidadesEncontradas.size(), 1);
    EXPECT_EQ(entidadesEncontradas.front().getFrecuencia(), 3);
}

TEST(Noticia, givenNoticiaConEntidadConFrecuencia3yEntidadConFrecuencia2_whenPreguntarPorEntidadMasFrecuente_then_LaDeFrecuencia3EsDevuelta)
{
    Noticia n("Título de la noticia ", "Prueba Pruebo Prueba Pruebo Prueba ", "dataTests/ES_stopList_test1.txt");
    auto entidadesEncontradas = n.getEntidades();
    EXPECT_EQ(entidadesEncontradas.size(), 2);
    EXPECT_EQ(n.getMasFrecuente().getEntidadNombrada(), "Prueba");
    EXPECT_EQ(n.getMasFrecuente().getFrecuencia(), 3);
}

TEST(Noticia, givenNoticiaSinEntidadesRelevantes_whenPreguntarPorEntidadesRelevantes_then_NingulaEsDevuelta)
{
    Noticia n("Título de la noticia ", "noticia con entidades no Relevantes ", "dataTests/ES_stopList_test1.txt");
    auto entidadesEncontradas = n.getEntidades();
    EXPECT_EQ(entidadesEncontradas.size(), 1);
    EXPECT_EQ(n.getEntidadesRelevantes().size(), 0);
}

TEST(Noticia, givenDosNoticiasConMismaEntidadMasFrecuente_whenPreguntarPorAgrupables_then_true)
{
    Noticia n1("Título de la noticia ", "noticia con entidades no Relevantes ", "dataTests/ES_stopList_test1.txt");
    Noticia n2("Título Relevante ", "noticia sin entidades ", "dataTests/ES_stopList_test1.txt");
    EXPECT_EQ(n1.esAgrupable(n2), true);
}

TEST(Noticia, givenDosNoticiasConDistintaEntidadMasFrecuentePeroCumpliendoCondicion30Porciento_whenPreguntarPorAgrupables_then_true)
{
    Noticia n1("Noticia 1 ", "Noticia Cinco Seis Siete Ocho Nueve Diez Once Doce Trece Catorce ", "dataTests/ES_stopList_test1.txt");
    Noticia n2("Noticia 2 ", "Esta Noticia Tiene el 30% de las Entidades más Relevantes de la Primera y Muchas Otras Más. Cinco ", "dataTests/ES_stopList_test1.txt");
    ASSERT_EQ(n1.getMasFrecuente().esIgual(n2.getMasFrecuente()), false);
    auto entidadesRelevantes1 = n1.getEntidadesRelevantes();
    EXPECT_EQ(entidadesRelevantes1.size(), 3);
    EXPECT_EQ(n2.esAgrupable(n1), true);
}