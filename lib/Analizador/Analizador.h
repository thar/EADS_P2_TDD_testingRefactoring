/*
 * Analizador.h
 *
 *  Created on: 26-dic-2012
 *      Author: Alvaro
 */

#ifndef ANALIZADOR_H_
#define ANALIZADOR_H_
#include "string"
#include <list>
#include <memory>
#include "NoticiaInterface.h"

class Analizador {

	std::list<std::shared_ptr<NoticiaInterface>> noticias;
	std::string ruta;


public:
	Analizador();
	Analizador(std::string ruta);

	std::list<std::shared_ptr<NoticiaInterface>> getNoticias() const;
	void setNoticas(std::string ruta);

	std::string agruparNoticias();
	std::string agruparNoticiasGeneral();

	std::string toString()const;

    void addNoticia(std::shared_ptr<NoticiaInterface> n);

private:

	std::string rellenarCeros(int n, int size)const;
	void ordenarNoticias();
};

#endif /* ANALIZADOR_H_ */
