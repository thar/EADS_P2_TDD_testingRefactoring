#include <ConversorJson.h>
#include <Noticia.h>
#include "Tuit.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

TEST(ConversorJson, givenNoticia_whenObtenerCamposJson_then_LosDatosCorrectosSonRetornados)
{
    ConversorJson e;
    std::vector<std::string> parrafos;
    parrafos.push_back("parrafo1");
    parrafos.push_back("parrafo2");
    std::shared_ptr<PalabrasReservadasInterface> palabrasReservadas = std::make_shared<PalabrasReservadas>("data/ES_stopList_test.txt");

    std::shared_ptr<Noticia> n = std::make_shared<Noticia>("titulo", parrafos, palabrasReservadas);
    auto campos = e.getCampos(n);
    EXPECT_EQ(campos["titulo"].asString(), "titulo");
    EXPECT_EQ(campos["parrafos"][0].asString(),"parrafo1");
    EXPECT_EQ(campos["parrafos"][1].asString(),"parrafo2");
}

TEST(ConversorJson, givenTuit_whenObtenerCamposJson_then_LosDatosConLosQueSeCreoSonRetornados)
{
    ConversorJson e;

    Json::Value valores;
    valores["tuit"] = "titulo tuit";
    valores["user"] = "@user";
    valores["id"] = 1;
    std::shared_ptr<PalabrasReservadasInterface> palabrasReservadas = std::make_shared<PalabrasReservadas>("data/ES_stopList_test.txt");

    std::shared_ptr<Tuit> n = std::make_shared<Tuit>(valores, palabrasReservadas);
    auto campos = e.getCampos(n);
    EXPECT_EQ(campos, valores);
}

TEST(ConversorJson, givenAgrupacionConNoticia_y_Tuit_whenObtenerCamposJson_then_LosDatosConLosQueSeCrearonLasNoticiasSonRetornados)
{
    std::vector<std::string> parrafos;
    parrafos.push_back("Noticia de Test para comprobar la Agrupacion pasada a Json");
    parrafos.push_back("es necesario que tenga al menos 2 Párrafos");
    std::string titulo = "Noticia de Test";

    Json::Value noticiaJson;
    noticiaJson["titulo"] = titulo;
    noticiaJson["parrafos"] = Json::Value(Json::arrayValue);
    noticiaJson["parrafos"].append(parrafos[0]);
    noticiaJson["parrafos"].append(parrafos[1]);

    Json::Value tuitJson;
    tuitJson["tuit"] = "Noticia de Test";
    tuitJson["user"] = "@user";
    tuitJson["id"] = 1;

    Json::Value elementos = Json::Value(Json::arrayValue);
    elementos.append(noticiaJson);
    elementos.append(tuitJson);

    Json::Value entidades = Json::Value(Json::arrayValue);
    entidades.append("Agrupacion");
    entidades.append("Json");
    entidades.append("Noticia");
    entidades.append("Párrafos");
    entidades.append("Test");

    Json::Value agrupacion1;
    agrupacion1["titulo"] = "Noticia de Test";
    agrupacion1["entidades"] = entidades;
    agrupacion1["elementos"] = elementos;

    std::shared_ptr<PalabrasReservadasInterface> palabrasReservadas = std::make_shared<PalabrasReservadas>("data/ES_stopList_test.txt");

    std::shared_ptr<Noticia> noticia = std::make_shared<Noticia>(titulo, parrafos, palabrasReservadas);
    std::shared_ptr<Tuit> tuit = std::make_shared<Tuit>(tuitJson, palabrasReservadas);

    Agrupacion agrupacion;
    agrupacion.push_back(noticia);
    agrupacion.push_back(tuit);

    ConversorJson e;
    EXPECT_EQ(e.getCampos(agrupacion), agrupacion1);
}

TEST(ConversorJson, givenUnaListaDeAgrupaciones_whenObtenerCamposJson_then_LosDatosCorrectosSegunLaEspecificacionSonRetornados)
{
    std::vector<std::string> parrafos;
    parrafos.push_back("Noticia de Test para comprobar la Agrupacion pasada a Json");
    parrafos.push_back("es necesario que tenga al menos 2 Párrafos");
    std::string titulo = "Noticia de Test";

    Json::Value noticiaJson;
    noticiaJson["titulo"] = titulo;
    noticiaJson["parrafos"] = Json::Value(Json::arrayValue);
    noticiaJson["parrafos"].append(parrafos[0]);
    noticiaJson["parrafos"].append(parrafos[1]);

    Json::Value tuitJson;
    tuitJson["tuit"] = "Noticia de Test";
    tuitJson["user"] = "@user";
    tuitJson["id"] = 1;

    Json::Value elementos = Json::Value(Json::arrayValue);
    elementos.append(noticiaJson);
    elementos.append(tuitJson);

    Json::Value entidades = Json::Value(Json::arrayValue);
    entidades.append("Agrupacion");
    entidades.append("Json");
    entidades.append("Noticia");
    entidades.append("Párrafos");
    entidades.append("Test");

    Json::Value agrupacion1;
    agrupacion1["titulo"] = "Noticia de Test";
    agrupacion1["entidades"] = entidades;
    agrupacion1["elementos"] = elementos;

    Json::Value root;
    root["grupos"] = Json::Value(Json::arrayValue);
    root["grupos"].append(agrupacion1);

    std::shared_ptr<PalabrasReservadasInterface> palabrasReservadas = std::make_shared<PalabrasReservadas>("data/ES_stopList_test.txt");

    std::shared_ptr<Noticia> noticia = std::make_shared<Noticia>(titulo, parrafos, palabrasReservadas);
    std::shared_ptr<Tuit> tuit = std::make_shared<Tuit>(tuitJson, palabrasReservadas);

    Agrupacion agrupacion;
    agrupacion.push_back(noticia);
    agrupacion.push_back(tuit);

    std::list<Agrupacion> listaAgrupaciones;
    listaAgrupaciones.push_back(agrupacion);

    ConversorJson e;
    EXPECT_EQ(e.getCampos(listaAgrupaciones), root);
}