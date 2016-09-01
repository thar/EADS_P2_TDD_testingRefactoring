
#include <pathUtils.h>
#include "NoticiasJsonBuilder.h"
#include "Noticia.h"
#include "json/json.h"
#include <fstream>


NoticiasJsonBuilder::NoticiasJsonBuilder(std::string noticiasPath,
                                 std::shared_ptr<PalabrasReservadasInterface> palabrasReservadas) :
        noticiasPath(noticiasPath), palabrasReservadas(palabrasReservadas)
{

}

std::vector<std::shared_ptr<NoticiaInterface>> NoticiasJsonBuilder::getNoticias()
{
    std::vector<std::shared_ptr<NoticiaInterface>> noticias;

    auto fileList = globVector(noticiasPath + "/*");

    for (auto file : fileList)
    {
        std::string titulo;
        std::vector<std::string> parrafos;
        obtenerDatosNoticiasDesdeFichero(file,titulo, parrafos);
        auto noticia = std::make_shared<Noticia>(titulo, parrafos, palabrasReservadas);
        if (noticia->getTitulo().length() != 0)
            noticias.push_back(noticia);
    }

    return noticias;
}

//TODO: Función con 3 parámetros
void
NoticiasJsonBuilder::obtenerDatosNoticiasDesdeFichero(std::string &rutaFichero, std::string &titulo, std::vector<std::string>& parrafos)
{
    titulo = "";
    parrafos = std::vector<std::string>();

    Json::Value valoresNoticia;
    std::ifstream noticiaFile(rutaFichero, std::ifstream::binary);
    noticiaFile >> valoresNoticia;
    titulo = valoresNoticia["titulo"].asString();
    const Json::Value parrafosJson = valoresNoticia["parrafos"];
    for ( int index = 0; index < parrafosJson.size(); ++index )
    {
        parrafos.push_back(parrafosJson[index].asString());
    }
}