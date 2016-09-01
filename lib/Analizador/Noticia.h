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

class Noticia : public NoticiaInterface {

    std::string titulo;
    std::string cuerpo;
    std::map<std::string, int> entidades;
    std::list<std::string> entidadesRelevantes;
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

	std::string getTitulo()const;
	std::string getCuerpo()const;
    EntidadComposite getEntidadMasFrecuente() const;
	std::list<std::string> getEntidades()const;
    int getFrecuenciaEntidad(EntidadComposite entidad) const;
    std::shared_ptr<PalabrasReservadasInterface> getPalabrasReservadas()const;
	std::list<std::string> getEntidadesRelevantes()const;
	bool esAgrupable(std::shared_ptr<NoticiaInterface> n)const;
	std::string toString()const;


private:
	void procesarEntidades();
	void procesarEntidadMasFrecuente();
	bool agregarEntidad(std::string nombre);
};

#endif /* NOTICIA_H_ */
