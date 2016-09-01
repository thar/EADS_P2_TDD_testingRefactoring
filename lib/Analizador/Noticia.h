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
#include "NoticiaInterface.h"
#include "NoticiaVisitor.h"

class Noticia : public NoticiaInterface {

    std::string titulo;
    std::string cuerpo;
    std::map<std::string, int> entidades;
    std::set<std::string> entidadesRelevantes;
    EntidadComposite entidadMasFrecuente;
    std::shared_ptr<PalabrasReservadasInterface> palabrasReservadas;

public:
	Noticia();
	Noticia(std::string titulo, std::string cuerpo, std::shared_ptr<PalabrasReservadasInterface> palabrasReservadas);
    Noticia(std::string rutaNoticias, std::shared_ptr<PalabrasReservadasInterface> palabrasReservadas);

	void setTitulo(std::string titulo);
	void setCuerpo(std::string cuerpo);
	void setPalabrasReservadas(std::shared_ptr<PalabrasReservadasInterface> palabrasReservadas);
	void inicializar();

	virtual std::string getTitulo()const;
	virtual std::string getCuerpo()const;
	virtual EntidadComposite getEntidadMasFrecuente() const;
	virtual std::set<std::string> getEntidades()const;
	virtual int getFrecuenciaEntidad(EntidadComposite entidad) const;
	virtual std::shared_ptr<PalabrasReservadasInterface> getPalabrasReservadas()const;
	virtual std::set<std::string> getEntidadesRelevantes()const;
	bool esAgrupable(std::shared_ptr<NoticiaInterface> n)const;
	std::string toString()const;
    void accept(NoticiaVisitor& visitor) { visitor.visit(*this); }


private:
	void procesarEntidades();
	void procesarEntidadMasFrecuente();
	bool agregarEntidad(std::string nombre);
};

#endif /* NOTICIA_H_ */
