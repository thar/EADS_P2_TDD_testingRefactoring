
#ifndef ANALIZARNOTICIASLINUX_TUITSJSONBUILDER_H
#define ANALIZARNOTICIASLINUX_TUITSJSONBUILDER_H


#include <string>
#include <memory>
#include "PalabrasReservadas.h"
#include "Tuit.h"
#include "NoticiasBuilderInterface.h"

class TuitsJsonBuilder : public NoticiasBuilderInterface
{
public:
    TuitsJsonBuilder(std::string pathFicheroTuits, std::shared_ptr<PalabrasReservadasInterface> palabrasReservadas);
    std::vector<std::shared_ptr<NoticiaInterface>> getNoticias();
protected:
private:
    std::string pathFicheroTuits;
    std::shared_ptr<PalabrasReservadasInterface> palabrasReservadas;
};


#endif //ANALIZARNOTICIASLINUX_TUITSJSONBUILDER_H
