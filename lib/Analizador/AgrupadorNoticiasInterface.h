
#ifndef ANALIZARNOTICIASLINUX_AGRUPADORNOTICIASINTERFACE_H
#define ANALIZARNOTICIASLINUX_AGRUPADORNOTICIASINTERFACE_H


#include "NoticiaInterface.h"

class AgrupadorNoticiasInterface
{
public:
    virtual bool isAgregableEntidadMasFrecuente(std::shared_ptr<NoticiaInterface> n1, std::shared_ptr<NoticiaInterface> n2) const = 0;
    virtual bool isAgregable(std::shared_ptr<NoticiaInterface> n1, std::shared_ptr<NoticiaInterface> n2) = 0;
};


#endif //ANALIZARNOTICIASLINUX_AGRUPADORNOTICIASINTERFACE_H
