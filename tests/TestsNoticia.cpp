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
    EXPECT_EQ(entidadesEncontradas.front(), "Ahora");
    EXPECT_EQ(n.getEntidadMasFrecuente(), "Ahora");
    EXPECT_EQ(n.getEntidadesRelevantes().front(), "Ahora");
}

TEST(Noticia, givenDatosParaCreacionDeNoticiaConUnaSolaEntidad_whenConstructorSinParametros_y_ObtenerDatosDeLaInterfazPublicaDeNoticia_then_DatosCorrectosSonObtenidos)
{
    Noticia n;
    n.setTitulo("Título de la noticia ");
    n.setCuerpo("Ahora viene el cuerpo de la noticia ");
    n.setPalabrasReservadas("dataTests/ES_stopList_test1.txt");
    n.inicializar();
    EXPECT_EQ(n.getCuerpo(), "Ahora viene el cuerpo de la noticia ");
    EXPECT_EQ(n.getTitulo(), "Título de la noticia ");
    auto palabrasReservadas = n.getPalabrasReservadas();
    EXPECT_EQ(palabrasReservadas.size(), 4);
    auto entidadesEncontradas = n.getEntidades();
    ASSERT_EQ(entidadesEncontradas.size(), 1);
    EXPECT_EQ(entidadesEncontradas.front(), "Ahora");
    EXPECT_EQ(n.getEntidadMasFrecuente(), "Ahora");
    EXPECT_EQ(n.getEntidadesRelevantes().front(), "Ahora");
}

TEST(Noticia, givenNoticiaConEntidadesSoloPertenecientes_a_laListaDePalabrasReservadas_whenPreguntarPorEntidadesEncontradas_then_CeroSonDevueltas)
{
    Noticia n("Título de la noticia ", "Uno Dos Tres Cuatro ", "dataTests/ES_stopList_test1.txt");
    auto entidadesEncontradas = n.getEntidades();
    EXPECT_EQ(entidadesEncontradas.size(), 0);
    n.setCuerpo("Uno Dos Entidad Tres Cuatro ");
    n.inicializar();
    entidadesEncontradas = n.getEntidades();
    ASSERT_EQ(entidadesEncontradas.size(), 1);
    EXPECT_EQ(entidadesEncontradas.front(), "Entidad");
    EXPECT_EQ(n.getEntidadMasFrecuente(), "Entidad");
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
    EXPECT_EQ(n.getFrecuenciaEntidad(entidadesEncontradas.front()), 3);
}

TEST(Noticia, givenNoticiaConEntidadConFrecuencia3yEntidadConFrecuencia2_whenPreguntarPorEntidadMasFrecuente_then_LaDeFrecuencia3EsDevuelta)
{
    Noticia n("Título de la noticia ", "Prueba Pruebo Prueba Pruebo Prueba ", "dataTests/ES_stopList_test1.txt");
    auto entidadesEncontradas = n.getEntidades();
    EXPECT_EQ(entidadesEncontradas.size(), 2);
    EXPECT_EQ(n.getEntidadMasFrecuente(), "Prueba");
    EXPECT_EQ(n.getFrecuenciaEntidad("Prueba"), 3);
}

TEST(Noticia, givenNoticiaConDosEntidadesConFrecuencia2_whenPreguntarPorEntidadeMasFrecuente_then_EntidadCompositeConLas2EntidadesEsDevuelto)
{
    Noticia n("Título de la noticia ", "Pruebo Prueba Prueba Pruebo ", "dataTests/ES_stopList_test1.txt");
    ASSERT_EQ(n.getEntidades().size(), 2);
    EXPECT_EQ(n.getEntidadMasFrecuente(), "Pruebo");
    EXPECT_EQ(n.getFrecuenciaEntidad("Pruebo"), 2);
    EXPECT_EQ(n.getEntidadMasFrecuente(), "Prueba");
    EXPECT_EQ(n.getFrecuenciaEntidad("Prueba"), 2);
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
    std::shared_ptr<Noticia> n2 = std::make_shared<Noticia>("Título Relevante ", "noticia sin entidades ", "dataTests/ES_stopList_test1.txt");
    EXPECT_EQ(n1.esAgrupable(n2), true);
}

TEST(Noticia, givenDosNoticiasConDistintaEntidadMasFrecuentePeroCumpliendoCondicion30Porciento_whenPreguntarPorAgrupables_then_true)
{
    std::shared_ptr<Noticia> n1 = std::make_shared<Noticia>("Noticia 1 ",
                                                            "Noticia Cinco Seis Siete Ocho Nueve Diez Once Doce Trece Catorce Diez ",
                                                            "dataTests/ES_stopList_test1.txt");
    Noticia n2("Noticia 2 ",
               "Esta Noticia Tiene el 30% de las Entidades más Relevantes de la Primera y Muchas Otras Más. Cinco ",
               "dataTests/ES_stopList_test1.txt");
    ASSERT_NE(n1->getEntidadMasFrecuente(), n2.getEntidadMasFrecuente());
    auto entidadesRelevantes1 = n1->getEntidadesRelevantes();
    EXPECT_EQ(entidadesRelevantes1.size(), 3);
    EXPECT_EQ(n2.esAgrupable(n1), true);
}

TEST(Noticia, givenNoticiaConPalabrasQueNoEmpiezanPorLetras_whenPreguntarPorEntidadesEncontradas_then_NingunaDevuelta)
{
    Noticia n1("Noticia 1 ", ", ' . 1 2 ? ! - [ ] ", "dataTests/ES_stopList_test1.txt");
    auto entidades = n1.getEntidades();
    ASSERT_EQ(entidades.size(), 0);
}

TEST(Noticia, givenNoticia_whenObtenerSuRepresentacionComoString_then_LaCadenaCorrectaEsObtenida)
{
    std::shared_ptr<Noticia> n1 = std::make_shared<Noticia>("Título ", "cuerpo ", "data/ES_stopList.txt");
    auto noticiaString = n1->toString();
    ASSERT_EQ("TITULO: Título \n"
                      "CUERPO: cuerpo \n"
                      "ENTIDADES: \n"
                      "MAS RELEVANTES: \n"
                      "MAS FRECUENTE: ", noticiaString);
}