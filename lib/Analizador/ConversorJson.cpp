
#include "ConversorJson.h"
#include "Noticia.h"
#include "Tuit.h"

Json::Value ConversorJson::getCampos(std::shared_ptr<NoticiaInterface> noticia)
{
    camposNoticia = Json::Value();
    noticia->accept(*this);
    return camposNoticia;
}

void ConversorJson::visit(Noticia &noticia)
{
    camposNoticia["titulo"] = noticia.getTitulo();
    camposNoticia["parrafos"] = Json::Value(Json::arrayValue);
    for (const auto parrafo : noticia.getParrafos())
        camposNoticia["parrafos"].append(parrafo);
}

void ConversorJson::visit(Tuit &tuit)
{
    camposNoticia["tuit"] = tuit.getTitulo();
    camposNoticia["user"] = tuit.getUser();
    camposNoticia["id"] = tuit.getId();
}

Json::Value ConversorJson::getCampos(const Agrupacion &agrupacion)
{
    Json::Value elementos = Json::Value(Json::arrayValue);
    for (const auto& noticia : agrupacion)
        elementos.append(getCampos(noticia));

    Json::Value entidades = Json::Value(Json::arrayValue);
    for (const auto& entidad : agrupacion.getEntidades())
        entidades.append(entidad);

    Json::Value agrupacionJson;
    agrupacionJson["titulo"] = agrupacion.getTitulo();
    agrupacionJson["entidades"] = entidades;
    agrupacionJson["elementos"] = elementos;

    return agrupacionJson;
}

Json::Value ConversorJson::getCampos(const std::list<Agrupacion> &agrupaciones)
{
    Json::Value root;
    root["grupos"] = Json::Value(Json::arrayValue);

    for (const auto& agrupacion : agrupaciones)
        root["grupos"].append(getCampos(agrupacion));

    return root;
}