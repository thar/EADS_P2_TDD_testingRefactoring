
#ifndef ANALIZARNOTICIASLINUX_NOTICIAINTERFACE_H
#define ANALIZARNOTICIASLINUX_NOTICIAINTERFACE_H

#include <string>
#include <list>
#include <memory>
#include "EntidadComposite.h"
#include "PalabrasReservadas.h"
#include "NoticiaVisitor.h"

class NoticiaInterface {

public:

    virtual void setTitulo(std::string titulo) {};
    virtual void setCuerpo(std::string cuerpo) {};
    virtual void setPalabrasReservadas(std::shared_ptr<PalabrasReservadasInterface> palabrasReservadas) {};

    virtual std::string getTitulo()const = 0;
    virtual std::string getCuerpo()const = 0;
    virtual std::set<std::string> getEntidades()const = 0;
    virtual EntidadComposite getEntidadMasFrecuente() const = 0;
    virtual int getFrecuenciaEntidad(EntidadComposite entidad) const = 0;
    virtual std::shared_ptr<PalabrasReservadasInterface> getPalabrasReservadas()const = 0;
    virtual std::set<std::string> getEntidadesRelevantes()const = 0;
    virtual bool esAgrupable(std::shared_ptr<NoticiaInterface> n)const = 0;
    virtual std::string toString()const = 0;

    virtual void accept(NoticiaVisitor& visitor) = 0;
};


#endif //ANALIZARNOTICIASLINUX_NOTICIAINTERFACE_H
