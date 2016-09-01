
#ifndef ANALIZARNOTICIASLINUX_NOTICIASJSONBUILDER_H
#define ANALIZARNOTICIASLINUX_NOTICIASJSONBUILDER_H


#include "NoticiasBuilderInterface.h"

class NoticiasJsonBuilder : public NoticiasBuilderInterface
{
public:
    NoticiasJsonBuilder(std::string noticiasPath, std::shared_ptr<PalabrasReservadasInterface> palabrasReservadas);
    std::vector<std::shared_ptr<NoticiaInterface>> getNoticias();

protected:
    void obtenerDatosNoticiasDesdeFichero(std::string& rutaFichero, std::string& titulo, std::vector<std::string>& parrafos);
private:
    std::string noticiasPath;
    std::shared_ptr<PalabrasReservadasInterface> palabrasReservadas;
};


#endif //ANALIZARNOTICIASLINUX_NOTICIASJSONBUILDER_H
