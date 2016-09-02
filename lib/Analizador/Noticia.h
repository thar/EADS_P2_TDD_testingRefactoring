/*
 * Noticia.h
 *
 *  Created on: 26-dic-2012
 *      Author: Alvaro
 */

#ifndef NOTICIA_H_
#define NOTICIA_H_
#include "string"
#include <list>
#include <map>
#include <vector>
#include "NoticiaLocal.h"
#include "NoticiaVisitor.h"

class Noticia : public NoticiaLocal {


public:
	Noticia();
	Noticia(std::string titulo, std::vector<std::string> parrafos, std::shared_ptr<PalabrasReservadasInterface> palabrasReservadas);

	void setTitulo(std::string titulo);
	void setParrafos(std::vector<std::string> parrafos);

	virtual std::string getTitulo()const;
	virtual std::string getCuerpo()const;

	std::string toString()const;
    void accept(NoticiaVisitor& visitor) { visitor.visit(*this); }

    void procesarEntidades();

    std::vector<std::string> getParrafos() const { return parrafos; }

private:

	std::string titulo;
    std::vector<std::string> parrafos;
};

#endif /* NOTICIA_H_ */
