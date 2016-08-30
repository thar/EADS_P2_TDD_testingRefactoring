
#ifndef ANALIZARNOTICIASLINUX_NOTICIAINTERFACE_H
#define ANALIZARNOTICIASLINUX_NOTICIAINTERFACE_H

#include <string>
#include <list>
#include <memory>
#include "EntidadNombrada.h"

class NoticiaInterface {

public:

    virtual void setTitulo(std::string titulo) {};
    virtual void setCuerpo(std::string cuerpo) {};
    virtual void setPalabrasReservadas(std::string ruta) {};
    virtual void actualizar() {};

    virtual std::string getTitulo()const = 0;
    virtual std::string getCuerpo()const = 0;
    virtual EntidadNombrada getMasFrecuente()const = 0;
    virtual std::list<EntidadNombrada> getEntidades()const = 0;
    virtual std::string getEntidadMasFrecuente() const = 0;
    virtual std::list<std::string> getPalabrasReservadas()const = 0;
    virtual std::list<std::string> getEntidadesRelevantes()const = 0;
    virtual bool esAgrupable(std::shared_ptr<NoticiaInterface> n)const = 0;
    virtual std::string toString()const = 0;
};


#endif //ANALIZARNOTICIASLINUX_NOTICIAINTERFACE_H
