#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Noticia.h"

TEST(Noticia, givenDatosParaCreacionDeNoticiaConUnaSolaEntidad_whenObtenerDatosDeLaInterfazPublicaDeNoticia_then_DatosCorrectosSonObtenidos)
{
    std::shared_ptr<PalabrasReservadasInterface> palabrasReservadas = std::make_shared<PalabrasReservadas>("dataTests/ES_stopList_test1.txt");
    Noticia n("Título de la noticia", "Ahora viene el cuerpo de la noticia ", palabrasReservadas);
    EXPECT_EQ(n.getCuerpo(), "Ahora viene el cuerpo de la noticia ");
    EXPECT_EQ(n.getTitulo(), "Título de la noticia");
    EXPECT_EQ(n.getPalabrasReservadas()->size(), 4);
    auto entidadesEncontradas = n.getEntidades();
    ASSERT_EQ(entidadesEncontradas.size(), 1);
    EXPECT_EQ(*entidadesEncontradas.begin(), "Ahora");
    EXPECT_EQ(n.getEntidadMasFrecuente(), "Ahora");
    EXPECT_EQ(*n.getEntidadesRelevantes().begin(), "Ahora");
}

TEST(Noticia, givenDatosParaCreacionDeNoticiaConUnaSolaEntidad_whenConstructorSinParametros_y_ObtenerDatosDeLaInterfazPublicaDeNoticia_then_DatosCorrectosSonObtenidos)
{
    Noticia n;
    n.setTitulo("Título de la noticia ");
    n.setCuerpo("Ahora viene el cuerpo de la noticia ");
    std::shared_ptr<PalabrasReservadasInterface> palabrasReservadas = std::make_shared<PalabrasReservadas>("dataTests/ES_stopList_test1.txt");
    n.setPalabrasReservadas(palabrasReservadas);
    n.inicializar();
    EXPECT_EQ(n.getCuerpo(), "Ahora viene el cuerpo de la noticia ");
    EXPECT_EQ(n.getTitulo(), "Título de la noticia ");
    EXPECT_EQ(n.getPalabrasReservadas()->size(), 4);
    auto entidadesEncontradas = n.getEntidades();
    ASSERT_EQ(entidadesEncontradas.size(), 1);
    EXPECT_EQ(*entidadesEncontradas.begin(), "Ahora");
    EXPECT_EQ(n.getEntidadMasFrecuente(), "Ahora");
    EXPECT_EQ(*n.getEntidadesRelevantes().begin(), "Ahora");
}

TEST(Noticia, givenNoticiaConEntidadesSoloPertenecientes_a_laListaDePalabrasReservadas_whenPreguntarPorEntidadesEncontradas_then_CeroSonDevueltas)
{
    std::shared_ptr<PalabrasReservadasInterface> palabrasReservadas = std::make_shared<PalabrasReservadas>("dataTests/ES_stopList_test1.txt");
    Noticia n("Título de la noticia ", "Uno Dos Tres Cuatro ", palabrasReservadas);
    auto entidadesEncontradas = n.getEntidades();
    EXPECT_EQ(entidadesEncontradas.size(), 0);
    n.setCuerpo("Uno Dos Entidad Tres Cuatro ");
    n.inicializar();
    entidadesEncontradas = n.getEntidades();
    ASSERT_EQ(entidadesEncontradas.size(), 1);
    EXPECT_EQ(*entidadesEncontradas.begin(), "Entidad");
    EXPECT_EQ(n.getEntidadMasFrecuente(), "Entidad");
}

TEST(Noticia, givenNoticiaConEntidadesSoloPertenecientes_a_laListaDePalabrasReservadasConFrecuenciaMayorQueUno_whenPreguntarPorEntidadesEncontradas_then_CeroSonDevueltas)
{
    std::shared_ptr<PalabrasReservadasInterface> palabrasReservadas = std::make_shared<PalabrasReservadas>("dataTests/ES_stopList_test1.txt");
    Noticia n("Título de la noticia ", "Cuatro Uno uno Uno Tres Dos Tres Dos Cuatro Uno Cuatro ", palabrasReservadas);
    auto entidadesEncontradas = n.getEntidades();
    EXPECT_EQ(entidadesEncontradas.size(), 0);
}

TEST(Noticia, givenNoticiaConEntidadConFrecuencia3_whenPreguntarPorEntidadesEncontradas_then_UnaConFrecuenci3EsDevuelta)
{
    std::shared_ptr<PalabrasReservadasInterface> palabrasReservadas = std::make_shared<PalabrasReservadas>("dataTests/ES_stopList_test1.txt");
    Noticia n("Título de la noticia ", "Prueba prueba Prueba prueba Prueba ", palabrasReservadas);
    auto entidadesEncontradas = n.getEntidades();
    ASSERT_EQ(entidadesEncontradas.size(), 1);
    EXPECT_EQ(n.getFrecuenciaEntidad(*entidadesEncontradas.begin()), 3);
}

TEST(Noticia, givenNoticiaConEntidadConFrecuencia3yEntidadConFrecuencia2_whenPreguntarPorEntidadMasFrecuente_then_LaDeFrecuencia3EsDevuelta)
{
    std::shared_ptr<PalabrasReservadasInterface> palabrasReservadas = std::make_shared<PalabrasReservadas>("dataTests/ES_stopList_test1.txt");
    Noticia n("Título de la noticia ", "Prueba Pruebo Prueba Pruebo Prueba ", palabrasReservadas);
    auto entidadesEncontradas = n.getEntidades();
    EXPECT_EQ(entidadesEncontradas.size(), 2);
    EXPECT_EQ(n.getEntidadMasFrecuente(), "Prueba");
    EXPECT_EQ(n.getFrecuenciaEntidad("Prueba"), 3);
}

TEST(Noticia, givenNoticiaConDosEntidadesConFrecuencia2_whenPreguntarPorEntidadeMasFrecuente_then_EntidadCompositeConLas2EntidadesEsDevuelto)
{
    std::shared_ptr<PalabrasReservadasInterface> palabrasReservadas = std::make_shared<PalabrasReservadas>("dataTests/ES_stopList_test1.txt");
    Noticia n("Título de la noticia ", "Pruebo Prueba Prueba Pruebo ", palabrasReservadas);
    ASSERT_EQ(n.getEntidades().size(), 2);
    EXPECT_EQ(n.getEntidadMasFrecuente(), "Pruebo");
    EXPECT_EQ(n.getFrecuenciaEntidad("Pruebo"), 2);
    EXPECT_EQ(n.getEntidadMasFrecuente(), "Prueba");
    EXPECT_EQ(n.getFrecuenciaEntidad("Prueba"), 2);
}

TEST(Noticia, givenNoticiaSinEntidadesRelevantes_whenPreguntarPorEntidadesRelevantes_then_NingulaEsDevuelta)
{
    std::shared_ptr<PalabrasReservadasInterface> palabrasReservadas = std::make_shared<PalabrasReservadas>("dataTests/ES_stopList_test1.txt");
    Noticia n("Título de la noticia ", "noticia con entidades no Relevantes ", palabrasReservadas);
    auto entidadesEncontradas = n.getEntidades();
    EXPECT_EQ(entidadesEncontradas.size(), 1);
    EXPECT_EQ(n.getEntidadesRelevantes().size(), 0);
}

TEST(Noticia, givenNoticiaConPalabrasQueNoEmpiezanPorLetras_whenPreguntarPorEntidadesEncontradas_then_NingunaDevuelta)
{
    std::shared_ptr<PalabrasReservadasInterface> palabrasReservadas = std::make_shared<PalabrasReservadas>("dataTests/ES_stopList_test1.txt");
    Noticia n1("Noticia 1 ", ", ' . 1 2 ? ! - [ ] ", palabrasReservadas);
    auto entidades = n1.getEntidades();
    ASSERT_EQ(entidades.size(), 0);
}

TEST(Noticia, givenNoticia_whenObtenerSuRepresentacionComoString_then_LaCadenaCorrectaEsObtenida)
{
    std::shared_ptr<PalabrasReservadasInterface> palabrasReservadas = std::make_shared<PalabrasReservadas>("dataTests/ES_stopList_test.txt");
    std::shared_ptr<Noticia> n1 = std::make_shared<Noticia>("Título ", "cuerpo ", palabrasReservadas);
    auto noticiaString = n1->toString();
    ASSERT_EQ("TITULO: Título \n"
                      "CUERPO: cuerpo \n"
                      "ENTIDADES: \n"
                      "MAS RELEVANTES: \n"
                      "MAS FRECUENTE: ", noticiaString);
}