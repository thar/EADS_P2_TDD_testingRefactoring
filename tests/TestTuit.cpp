#include <TuitsJsonBuilder.h>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Tuit.h"


TEST(Tuit, givenDatosJsonParaCreacionDeTuit_whenObtenerDatosDeLaInterfazPublicaDeNoticia_then_DatosCorrectosSonObtenidos)
{
    Json::Value root;
    root["id"] = 1;
    root["usuario"] = "@usuario";
    root["tuit"] = "Noticia Entidad Entidad Prueba Tuit";
    std::shared_ptr<PalabrasReservadasInterface> palabrasReservadas = std::make_shared<PalabrasReservadas>("data/ES_stopList.txt");
    Tuit n(root, palabrasReservadas);
    EXPECT_EQ(n.getTitulo(), "Noticia Entidad Entidad Prueba Tuit");
    EXPECT_EQ(n.getCuerpo(), "");
    EXPECT_EQ(n.getEntidadMasFrecuente(), "Entidad");
    std::set<std::string> s;
    s.insert("Noticia");
    s.insert("Entidad");
    s.insert("Prueba");
    s.insert("Tuit");
    EXPECT_EQ(n.getEntidades(), s);
    EXPECT_EQ(n.getEntidadesRelevantes(), std::set<std::string>());
    EXPECT_EQ(n.getFrecuenciaEntidad("Entidad"),2);
    EXPECT_EQ(n.getFrecuenciaEntidad("Noticia"),1);
    EXPECT_EQ(n.getFrecuenciaEntidad("Prueba"),1);
    EXPECT_EQ(n.getFrecuenciaEntidad("Tuit"),1);
}

TEST(Tuit, givenFicheroConTuits_whenTuitsCreados_a_PartirDeFichero_then_3TuitsSonObtenidosConLosTitulosCorrectos)
{
    std::shared_ptr<PalabrasReservadasInterface> palabrasReservadas = std::make_shared<PalabrasReservadas>("data/ES_stopList_test.txt");
    TuitsJsonBuilder builder("data/tuits.txt", palabrasReservadas);
    auto tuits = builder.getNoticias();
    ASSERT_EQ(tuits.size(), 3);
    EXPECT_EQ(tuits[0]->getTitulo(), "Liberan a los dos sospechosos detenidos por el asesinato de un niño de 11 años en Liverpool");
    EXPECT_EQ(tuits[1]->getTitulo(), "Detienen a seis jóvenes más en relación con el asesinato de el niño de Liverpool");
    EXPECT_EQ(tuits[2]->getTitulo(), "Siguen los interrogatorios a los detenidos por el asesinato de el niño de Liverpool");
}