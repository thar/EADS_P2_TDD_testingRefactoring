
#ifndef ANALIZARNOTICIASLINUX_TUIT_H
#define ANALIZARNOTICIASLINUX_TUIT_H


#include <json/json.h>
#include "NoticiaLocal.h"

class Tuit : public NoticiaLocal
{
public:
	Tuit() {};
    Tuit(Json::Value& inputData, std::shared_ptr<PalabrasReservadasInterface> palabrasReservadas);

    void setTitulo(std::string titulo) {}
    void setParrafos(std::vector<std::string> parrafos) {}

    virtual std::string getTitulo() const { return tuit; }
    std::string getCuerpo() const { return ""; }
    std::string toString() const;
    void accept(NoticiaVisitor& visitor) { visitor.visit(*this); }

	void procesarEntidades();

    std::string getUser() const { return user; }
    int getId() const { return id; }

protected:
private:

    std::string tuit;
    std::string user;
    int id;
};


#endif //ANALIZARNOTICIASLINUX_TUIT_H
