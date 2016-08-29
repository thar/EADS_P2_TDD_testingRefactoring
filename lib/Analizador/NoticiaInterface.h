
#ifndef ANALIZARNOTICIASLINUX_NOTICIAINTERFACE_H
#define ANALIZARNOTICIASLINUX_NOTICIAINTERFACE_H

#include <string>
#include <list>
#include "EntidadNombrada.h"

class NoticiaInterface {

public:

    virtual void setTitulo(std::string titulo) = 0;
    virtual void setCuerpo(std::string cuerpo) = 0;
    virtual void setPalabrasReservadas(std::string ruta) = 0;
    virtual void actualizar() = 0;

    virtual std::string getTitulo()const = 0;
    virtual std::string getCuerpo()const = 0;
    virtual EntidadNombrada getMasFrecuente()const = 0;
    virtual std::list<EntidadNombrada> getEntidades()const = 0;
    virtual std::list<std::string> getPalabrasReservadas()const = 0;
    virtual std::list<EntidadNombrada> getEntidadesRelevantes()const = 0;
    virtual bool esAgrupable(NoticiaInterface& n)const = 0;
    virtual std::string toString()const = 0;
};


#endif //ANALIZARNOTICIASLINUX_NOTICIAINTERFACE_H
