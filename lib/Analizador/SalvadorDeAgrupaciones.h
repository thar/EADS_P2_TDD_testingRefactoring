
#ifndef ANALIZARNOTICIASLINUX_SALVADORDEAGRUPACIONES_H
#define ANALIZARNOTICIASLINUX_SALVADORDEAGRUPACIONES_H

#include <list>
#include <string>
#include "Agrupacion.h"

class SalvadorDeAgrupaciones
{
public:
    virtual void salvar(std::list<Agrupacion>, std::string rutaFichero) = 0;
};


#endif //ANALIZARNOTICIASLINUX_SALVADORDEAGRUPACIONES_H
