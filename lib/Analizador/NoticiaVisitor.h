
#ifndef ANALIZARNOTICIASLINUX_NOTICIAVISITOR_H
#define ANALIZARNOTICIASLINUX_NOTICIAVISITOR_H

class Noticia;

class NoticiaVisitor
{
public:
    virtual void visit(Noticia& n) = 0;
};


#endif //ANALIZARNOTICIASLINUX_NOTICIAVISITOR_H
