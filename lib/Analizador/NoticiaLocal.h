
#ifndef ANALIZARNOTICIASLINUX_NOTICIALOCAL_H
#define ANALIZARNOTICIASLINUX_NOTICIALOCAL_H

#include "string"
#include <list>
#include <map>
#include <vector>
#include "NoticiaInterface.h"
#include "NoticiaVisitor.h"

class NoticiaLocal : public NoticiaInterface {


public:

    void setPalabrasReservadas(std::shared_ptr<PalabrasReservadasInterface> palabrasReservadas);
    void inicializar();

    virtual EntidadComposite getEntidadMasFrecuente() const;
    virtual std::set<std::string> getEntidades()const;
    virtual int getFrecuenciaEntidad(EntidadComposite entidad) const;
    virtual std::shared_ptr<PalabrasReservadasInterface> getPalabrasReservadas()const;
    virtual std::set<std::string> getEntidadesRelevantes()const;

    virtual void procesarEntidades() = 0;

protected:
    void procesarEntidadMasFrecuente();
    bool agregarEntidad(std::string nombre);

    std::map<std::string, int> entidades;
    std::set<std::string> entidadesRelevantes;
    EntidadComposite entidadMasFrecuente;
    std::shared_ptr<PalabrasReservadasInterface> palabrasReservadas;
private:
};


#endif //ANALIZARNOTICIASLINUX_NOTICIALOCAL_H
