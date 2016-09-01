
#ifndef ANALIZARNOTICIASLINUX_AGRUPADORNOTICIAS_H
#define ANALIZARNOTICIASLINUX_AGRUPADORNOTICIAS_H

#include <memory>
#include "NoticiaVisitor.h"
#include "NoticiaInterface.h"

class AgrupadorNoticias : public NoticiaVisitor
{
public:
    bool isAgregableEntidadMasFrecuente(std::shared_ptr<NoticiaInterface> n1, std::shared_ptr<NoticiaInterface> n2) const;
    bool isAgregable(std::shared_ptr<NoticiaInterface> n1, std::shared_ptr<NoticiaInterface> n2);
    void visit(Noticia& n);
protected:
private:
};


#endif //ANALIZARNOTICIASLINUX_AGRUPADORNOTICIAS_H
