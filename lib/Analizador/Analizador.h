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
#include <set>
#include "NoticiaInterface.h"
#include "Agrupacion.h"
#include "AgrupadorNoticias.h"
#include "AgrupadorNoticiasInterface.h"

class Analizador {

	std::list<std::shared_ptr<NoticiaInterface>> noticias;
	std::string ruta;
    std::list<Agrupacion> agrupacionEntidadMasFrecuente;


public:
	Analizador();
	Analizador(std::string ruta);

	std::list<std::shared_ptr<NoticiaInterface>> getNoticias() const;
	void setNoticas(std::string ruta);
    void setAgrupador(std::shared_ptr<AgrupadorNoticiasInterface> agrupador);

	std::string agruparNoticias();
	std::string agruparNoticiasGeneral();

	std::string toString()const;

    void addNoticia(std::shared_ptr<NoticiaInterface> n);
    std::list<Agrupacion> getAgrupacionEntidadMasNombrada();
    std::list<Agrupacion> getAgrupacionTematica();
protected:
    std::shared_ptr<AgrupadorNoticiasInterface> getAgrupador();
    void addNoticiaToAgrupacionEntidadMasFrecuente(std::shared_ptr<NoticiaInterface> noticia);
    bool isAgrupacionesAgrupables(Agrupacion& agrupacion1, Agrupacion& agrupacion2);

private:
    std::shared_ptr<AgrupadorNoticiasInterface> agrupador;
};

std::ostream& operator<<(std::ostream& os, const std::list<Agrupacion>& obj);

#endif /* ANALIZADOR_H_ */
