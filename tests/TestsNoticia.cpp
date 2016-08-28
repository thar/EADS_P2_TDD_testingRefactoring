#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Noticia.h"

TEST(Noticia, testConstructorConParametros)
{
    Noticia n("Título de la noticia", "Ahora viene el cuerpo de la noticia ", "dataTests/ES_stopList_test1.txt");
    ASSERT_EQ(n.getCuerpo(), "Ahora viene el cuerpo de la noticia ");
    ASSERT_EQ(n.getTitulo(), "Título de la noticia");
    auto palabrasReservadas = n.getPalabrasReservadas();
    ASSERT_EQ(palabrasReservadas.size(), 4);
    auto entidadesEncontradas = n.getEntidades();
    ASSERT_EQ(entidadesEncontradas.size(), 1);
    ASSERT_EQ(entidadesEncontradas.front().getEntidadNombrada(), "Ahora");
    ASSERT_EQ(n.getMasFrecuente().getEntidadNombrada(), "Ahora");
    ASSERT_EQ(n.getEntidadesRelevantes().front().getEntidadNombrada(), "Ahora");
}

TEST(Noticia, testConstructorSinParametros)
{
    Noticia n;
    n.setTitulo("Título de la noticia ");
    n.setCuerpo("Ahora viene el cuerpo de la noticia ");
    n.setPalabrasReservadas("dataTests/ES_stopList_test1.txt");
    n.actualizar();
    ASSERT_EQ(n.getCuerpo(), "Ahora viene el cuerpo de la noticia ");
    ASSERT_EQ(n.getTitulo(), "Título de la noticia ");
    auto palabrasReservadas = n.getPalabrasReservadas();
    ASSERT_EQ(palabrasReservadas.size(), 4);
    auto entidadesEncontradas = n.getEntidades();
    ASSERT_EQ(entidadesEncontradas.size(), 1);
    ASSERT_EQ(entidadesEncontradas.front().getEntidadNombrada(), "Ahora");
    ASSERT_EQ(n.getMasFrecuente().getEntidadNombrada(), "Ahora");
    ASSERT_EQ(n.getEntidadesRelevantes().front().getEntidadNombrada(), "Ahora");
}

TEST(Noticia, testCuerpoConPalabrasEnStopList)
{
    Noticia n("Título de la noticia ", "Uno Dos Tres Cuatro ", "dataTests/ES_stopList_test1.txt");
    auto entidadesEncontradas = n.getEntidades();
    ASSERT_EQ(entidadesEncontradas.size(), 0);
    n.setCuerpo("Uno Dos Entidad Tres Cuatro ");
    n.actualizar();
    entidadesEncontradas = n.getEntidades();
    ASSERT_EQ(entidadesEncontradas.size(), 1);
    ASSERT_EQ(entidadesEncontradas.front().getEntidadNombrada(), "Entidad");
    ASSERT_EQ(n.getMasFrecuente().getEntidadNombrada(), "Entidad");
}

TEST(Noticia, testCuerpoConPalabrasEnStopListVariasVeces)
{
    Noticia n("Título de la noticia ", "Cuatro Uno uno Uno Tres Dos Tres Dos Cuatro Uno Cuatro ", "dataTests/ES_stopList_test1.txt");
    auto entidadesEncontradas = n.getEntidades();
    ASSERT_EQ(entidadesEncontradas.size(), 0);
}

TEST(Noticia, testFrecuenciaEntidad)
{
    Noticia n("Título de la noticia ", "Prueba prueba Prueba prueba Prueba ", "dataTests/ES_stopList_test1.txt");
    auto entidadesEncontradas = n.getEntidades();
    ASSERT_EQ(entidadesEncontradas.size(), 1);
    ASSERT_EQ(entidadesEncontradas.front().getFrecuencia(), 3);
}

TEST(Noticia, testEntidadMasNombrada)
{
    Noticia n("Título de la noticia ", "Prueba Pruebo Prueba Pruebo Prueba ", "dataTests/ES_stopList_test1.txt");
    auto entidadesEncontradas = n.getEntidades();
    ASSERT_EQ(entidadesEncontradas.size(), 2);
    ASSERT_EQ(n.getMasFrecuente().getEntidadNombrada(), "Prueba");
    ASSERT_EQ(n.getMasFrecuente().getFrecuencia(), 3);
}

TEST(Noticia, testSinEntidadesRelevantes)
{
    Noticia n("Título de la noticia ", "noticia con entidades no Relevantes ", "dataTests/ES_stopList_test1.txt");
    auto entidadesEncontradas = n.getEntidades();
    ASSERT_EQ(entidadesEncontradas.size(), 1);
    ASSERT_EQ(n.getEntidadesRelevantes().size(), 0);
}

TEST(Noticia, testAgrupacionEntidadMasNombradaTitulo)
{
    Noticia n1("Título de la noticia ", "noticia con entidades no Relevantes ", "dataTests/ES_stopList_test1.txt");
    Noticia n2("Título Relevante ", "noticia sin entidades ", "dataTests/ES_stopList_test1.txt");
    ASSERT_EQ(n1.esAgrupable(n2), true);
}

TEST(Noticia, testAgrupacion30PorCiento)
{
    Noticia n1("Noticia 1 ", "Cinco Seis Siete Ocho Nueve Diez Once Doce Trece Catorce ", "dataTests/ES_stopList_test1.txt");
    Noticia n2("Noticia 2 ", "Esta Noticia Tiene el 30% de las Entidades más Relevantes de la Primera y Muchas Otras Más. Cinco ", "dataTests/ES_stopList_test1.txt");
    auto entidadesRelevantes1 = n1.getEntidadesRelevantes();
    ASSERT_EQ(entidadesRelevantes1.size(), 3);
    ASSERT_EQ(n2.esAgrupable(n1), true);
}