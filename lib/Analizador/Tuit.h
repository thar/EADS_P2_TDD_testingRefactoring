
#ifndef ANALIZARNOTICIASLINUX_TUIT_H
#define ANALIZARNOTICIASLINUX_TUIT_H


#include <json/json.h>
#include "NoticiaInterface.h"

class Tuit : public NoticiaInterface
{
public:
    Tuit(Json::Value& inputData, std::shared_ptr<PalabrasReservadasInterface> palabrasReservadas) {}

    void setTitulo(std::string titulo) {}
    void setCuerpo(std::string cuerpo) {}
    void setPalabrasReservadas(std::shared_ptr<PalabrasReservadasInterface> palabrasReservadas) {}

    virtual std::string getTitulo() const { return "Noticia Entidad Entidad Prueba Tuit"; }
    virtual std::string getCuerpo() const { return ""; }
    virtual EntidadComposite getEntidadMasFrecuente() const { return "Entidad"; }
    virtual std::set<std::string> getEntidades() const {
        std::set<std::string> s;
        s.insert("Noticia");
        s.insert("Entidad");
        s.insert("Prueba");
        s.insert("Tuit");
        return s; }
    virtual int getFrecuenciaEntidad(EntidadComposite entidad) const {
        if (entidad == "Entidad")
            return 2;
        else
            return 1; }
    virtual std::shared_ptr<PalabrasReservadasInterface> getPalabrasReservadas() const { return nullptr; }
    virtual std::set<std::string> getEntidadesRelevantes() const { return std::set<std::string>(); }
    std::string toString() const { return  ""; };
    void accept(NoticiaVisitor& visitor) {  }

protected:
private:
};


#endif //ANALIZARNOTICIASLINUX_TUIT_H
