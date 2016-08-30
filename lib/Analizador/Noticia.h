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
#include "EntidadNombrada.h"
#include "NoticiaInterface.h"

class Noticia : public NoticiaInterface {

    std::string titulo;
    std::string cuerpo;
    std::map<std::string, int> entidades;
    std::list<std::string> entidadesRelevantes;
    std::list<std::string> palabrasReservadas;
    std::string entidadMasFrecuente;

public:
	Noticia();
	Noticia(std::string titulo, std::string cuerpo, std::string ruta);

	void setTitulo(std::string titulo);
	void setCuerpo(std::string cuerpo);
	void setPalabrasReservadas(std::string ruta);
	void actualizar();

	std::string getTitulo()const;
	std::string getCuerpo()const;
	EntidadNombrada getMasFrecuente()const;
    std::string getEntidadMasFrecuente() const;
	std::list<EntidadNombrada> getEntidades()const;
	std::list<std::string> getPalabrasReservadas()const;
	std::list<std::string> getEntidadesRelevantes()const;
	bool esAgrupable(std::shared_ptr<NoticiaInterface> n)const;
	std::string toString()const;


private:
	void setEntidades();
	void setMasFrecuente();
	bool agregarEntidad(std::string nombre);
	bool esletra(char c) const;
};

#endif /* NOTICIA_H_ */
