
#ifndef ANALIZARNOTICIASLINUX_EXTRACTORCAMPOSNOTICIA_H
#define ANALIZARNOTICIASLINUX_EXTRACTORCAMPOSNOTICIA_H


#include <json/json.h>
#include <memory>
#include "NoticiaVisitor.h"
#include "NoticiaInterface.h"
#include "Agrupacion.h"

class ConversorJson : public NoticiaVisitor
{
public:
    Json::Value getCampos(std::shared_ptr<NoticiaInterface> noticia);
    Json::Value getCampos(const Agrupacion& agrupacion);
    Json::Value getCampos(const std::list<Agrupacion> &agrupaciones);
    void visit(Noticia& noticia);
    void visit(Tuit& tuit);
protected:
private:
    Json::Value camposNoticia;
};


#endif //ANALIZARNOTICIASLINUX_EXTRACTORCAMPOSNOTICIA_H
