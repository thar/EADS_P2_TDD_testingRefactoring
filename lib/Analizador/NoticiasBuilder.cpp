
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
        std::string cuerpo;
        obtenerDatosNoticiasDesdeFichero(file,titulo, cuerpo);
        auto noticia = std::make_shared<Noticia>(titulo, cuerpo, palabrasReservadas);
        if (noticia->getTitulo().length() != 0)
            noticias.push_back(noticia);
    }

    return noticias;
}

void
NoticiasBuilder::obtenerDatosNoticiasDesdeFichero(std::string &rutaFichero, std::string &titulo, std::string &cuerpo)
{
    titulo = "";
    cuerpo = "";
    FileLineIterator f(rutaFichero);
    if (f.is_open()) {
        for (auto line : f)
        {
            static int index = 0;
            if (titulo == "") {
                titulo = line.getLine();
            } else {
                if (cuerpo == "")
                    cuerpo = line.getLine();
                else
                    cuerpo += " " + line.getLine();
            }
        }
    }
}
