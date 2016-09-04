
#ifndef ANALIZARNOTICIASLINUX_TUIT_H
#define ANALIZARNOTICIASLINUX_TUIT_H


#include <json/json.h>
#include "NoticiaInterface.h"

class Tuit : public NoticiaInterface
{
public:
    Tuit(Json::Value& inputData, std::shared_ptr<PalabrasReservadasInterface> palabrasReservadas);

    void setTitulo(std::string titulo) {}
    void setCuerpo(std::string cuerpo) {}
    void setPalabrasReservadas(std::shared_ptr<PalabrasReservadasInterface> palabrasReservadas) {}
	void inicializar();

    virtual std::string getTitulo() const { return tuit; }
    virtual std::string getCuerpo() const { return ""; }
    virtual EntidadComposite getEntidadMasFrecuente() const { return entidadMasFrecuente; }
    virtual std::set<std::string> getEntidades() const;
    virtual int getFrecuenciaEntidad(EntidadComposite entidad) const;
    virtual std::shared_ptr<PalabrasReservadasInterface> getPalabrasReservadas() const { return palabrasReservadas; }
    virtual std::set<std::string> getEntidadesRelevantes() const { return entidadesRelevantes; }
    std::string toString() const;
    void accept(NoticiaVisitor& visitor) {  }

    std::string getUser() const { return user; }
    int getId() const { return id; }

protected:
private:
    void procesarEntidades();
	void procesarEntidadMasFrecuente();
	bool agregarEntidad(std::string nombre);

    std::map<std::string, int> entidades;
    std::set<std::string> entidadesRelevantes;
    EntidadComposite entidadMasFrecuente;
    std::shared_ptr<PalabrasReservadasInterface> palabrasReservadas;

    std::string tuit;
    std::string user;
    int id;
};


#endif //ANALIZARNOTICIASLINUX_TUIT_H
