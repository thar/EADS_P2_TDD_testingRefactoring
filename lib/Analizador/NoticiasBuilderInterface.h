
#ifndef ANALIZARNOTICIASLINUX_NOTICIASBUILDERINTERFACE_H
#define ANALIZARNOTICIASLINUX_NOTICIASBUILDERINTERFACE_H


#include <vector>
#include "NoticiaInterface.h"

class NoticiasBuilderInterface
{
public:
    virtual std::vector<std::shared_ptr<NoticiaInterface>> getNoticias() = 0;
};


#endif //ANALIZARNOTICIASLINUX_NOTICIASBUILDERINTERFACE_H
