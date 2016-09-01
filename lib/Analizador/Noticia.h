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
#include "NoticiaInterface.h"
#include "NoticiaVisitor.h"

class Noticia : public NoticiaInterface {


public:
	Noticia();
	Noticia(std::string titulo, std::vector<std::string> parrafos, std::shared_ptr<PalabrasReservadasInterface> palabrasReservadas);

	void setTitulo(std::string titulo);
	void setParrafos(std::vector<std::string> parrafos);
	void setPalabrasReservadas(std::shared_ptr<PalabrasReservadasInterface> palabrasReservadas);
	void inicializar();

	virtual std::string getTitulo()const;
	virtual std::string getCuerpo()const;
	virtual EntidadComposite getEntidadMasFrecuente() const;
	virtual std::set<std::string> getEntidades()const;
	virtual int getFrecuenciaEntidad(EntidadComposite entidad) const;
	virtual std::shared_ptr<PalabrasReservadasInterface> getPalabrasReservadas()const;
	virtual std::set<std::string> getEntidadesRelevantes()const;
	std::string toString()const;
    void accept(NoticiaVisitor& visitor) { visitor.visit(*this); }

    std::vector<std::string> getParrafos() const { return parrafos; }

private:
	void procesarEntidades();
	void procesarEntidadMasFrecuente();
	bool agregarEntidad(std::string nombre);

	std::string titulo;
    std::vector<std::string> parrafos;
	std::map<std::string, int> entidades;
	std::set<std::string> entidadesRelevantes;
	EntidadComposite entidadMasFrecuente;
	std::shared_ptr<PalabrasReservadasInterface> palabrasReservadas;
};

#endif /* NOTICIA_H_ */
