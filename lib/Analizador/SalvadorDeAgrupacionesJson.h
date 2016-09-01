
#ifndef ANALIZARNOTICIASLINUX_SALVADORDEAGRUPACIONESJSON_H
#define ANALIZARNOTICIASLINUX_SALVADORDEAGRUPACIONESJSON_H


#include "SalvadorDeAgrupaciones.h"

class SalvadorDeAgrupacionesJson : public SalvadorDeAgrupaciones
{
public:
    void salvar(std::list<Agrupacion>, std::string rutaFichero);
};


#endif //ANALIZARNOTICIASLINUX_SALVADORDEAGRUPACIONESJSON_H
