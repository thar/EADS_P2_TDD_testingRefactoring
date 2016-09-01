
#ifndef ANALIZARNOTICIASLINUX_NOTICIASBUILDER_H
#define ANALIZARNOTICIASLINUX_NOTICIASBUILDER_H


#include "NoticiasBuilderInterface.h"

class NoticiasBuilder : public NoticiasBuilderInterface
{
public:
    NoticiasBuilder(std::string noticiasPath, std::shared_ptr<PalabrasReservadasInterface> palabrasReservadas);
    std::vector<std::shared_ptr<NoticiaInterface>> getNoticias();

protected:
    void obtenerDatosNoticiasDesdeFichero(std::string& rutaFichero, std::string& titulo, std::string& cuerpo);
private:
    std::string noticiasPath;
    std::shared_ptr<PalabrasReservadasInterface> palabrasReservadas;
};


#endif //ANALIZARNOTICIASLINUX_NOTICIASBUILDER_H
