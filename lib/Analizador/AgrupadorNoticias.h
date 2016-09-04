
#ifndef ANALIZARNOTICIASLINUX_AGRUPADORNOTICIAS_H
#define ANALIZARNOTICIASLINUX_AGRUPADORNOTICIAS_H

#include <memory>
#include "NoticiaVisitor.h"
#include "NoticiaInterface.h"
#include "AgrupadorNoticiasInterface.h"

enum NoticiaType
{
    NOTICIA_TEXTO,
};

bool compare_NoticiaType (const std::pair<NoticiaType, std::shared_ptr<NoticiaInterface>>& first, const std::pair<NoticiaType, std::shared_ptr<NoticiaInterface>>& second);

class AgrupadorNoticias : public NoticiaVisitor, public AgrupadorNoticiasInterface
{
public:
    bool isAgregableEntidadMasFrecuente(std::shared_ptr<NoticiaInterface> n1, std::shared_ptr<NoticiaInterface> n2) const;
    bool isAgregable(std::shared_ptr<NoticiaInterface> n1, std::shared_ptr<NoticiaInterface> n2);
    void visit(Noticia& n);
    void visit(Tuit& n);
protected:
    bool isAgregable(Noticia &n1, Noticia &n2) const;
    unsigned long getMinimoNumeroEntidadesParaAgrupacionTematicaNoticiaTexto(Noticia& n) const;
    bool isEntidadEnTexto(const EntidadComposite entidad, const std::string texto) const;
private:
    NoticiaType noticiaType_;
};


#endif //ANALIZARNOTICIASLINUX_AGRUPADORNOTICIAS_H
