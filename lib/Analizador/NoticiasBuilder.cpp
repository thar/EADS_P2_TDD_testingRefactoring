
#include <pathUtils.h>
#include <FileLineIterator.h>
#include "NoticiasBuilder.h"
#include "Noticia.h"

NoticiasBuilder::NoticiasBuilder(std::string noticiasPath,
                                 std::shared_ptr<PalabrasReservadasInterface> palabrasReservadas) :
noticiasPath(noticiasPath), palabrasReservadas(palabrasReservadas)
{

}

std::vector<std::shared_ptr<NoticiaInterface>> NoticiasBuilder::getNoticias()
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
NoticiasBuilder::obtenerDatosNoticiasDesdeFichero(std::string &rutaFichero, std::string &titulo, std::vector<std::string>& parrafos)
{
    titulo = "";
    parrafos = std::vector<std::string>();
    FileLineIterator f(rutaFichero);
    if (f.is_open()) {
        for (auto line : f)
        {
            if (titulo == "") {
                titulo = line.getLine();
            } else {
                parrafos.push_back(line.getLine());
            }
        }
    }
}
