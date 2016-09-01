/*
 * Analizador.cpp
 *
 *  Created on: 26-dic-2012
 *      Author: Alvaro
 */

#include "Analizador.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Noticia.h"
#include "pathUtils.h"

Analizador::Analizador() : noticias(), ruta("") {
}

Analizador::Analizador(std::string ruta) : noticias(), ruta(ruta) {
    setNoticas(ruta);
}

std::list<std::shared_ptr<NoticiaInterface>> Analizador::getNoticias() const {
	return noticias;
}

void Analizador::setNoticas(std::string ruta) {

    std::string rutaRestricciones = ruta + "/ES_stopList.txt";
    std::string rutaNoticias = ruta + "/news";

    auto palabrasReservadas = std::make_shared<PalabrasReservadas>(rutaRestricciones);

    auto fileList = globVector(rutaNoticias + "/*");

    for (auto file : fileList)
    {
        auto noticia = std::make_shared<Noticia>(file, palabrasReservadas);
        if (noticia->getTitulo().length() != 0)
            addNoticia(noticia);
    }
}

std::string Analizador::agruparNoticias() {
    std::stringstream ss;
    ss << getAgrupacionEntidadMasNombrada();
    return ss.str();
}

std::string Analizador::agruparNoticiasGeneral() {
    std::stringstream ss;
    ss << getAgrupacionTematica();
    return ss.str();
}

std::string Analizador::toString() const {
	auto salida = std::string("Ruta del directorio: ") + ruta + "\n\n";
	for (auto noticia : noticias)
		salida = salida + "Titulo: " + noticia->getTitulo() + "\n\n";
	return salida;
}

void Analizador::addNoticia(std::shared_ptr<NoticiaInterface> n)
{
    noticias.push_back(n);
    addNoticiaToAgrupacionEntidadMasFrecuente(n);
}

std::list<Agrupacion> Analizador::getAgrupacionEntidadMasNombrada()
{
    return agrupacionEntidadMasFrecuente;
}

std::list<Agrupacion> Analizador::getAgrupacionTematica()
{
    std::list<Agrupacion> agrupacionTematica = agrupacionEntidadMasFrecuente;
    for (auto it1 = agrupacionTematica.begin(); it1 != agrupacionTematica.end(); ++it1)
    {
        for (auto it2 = agrupacionTematica.begin(); it2 != agrupacionTematica.end(); ++it2)
        {
            if (it1 != it2 && isAgrupacionesAgrupables(*it1, *it2))
            {
                Agrupacion a;
                it2->swap(a);
                it1->insert(it1->end(), a.begin(), a.end());
                it2 = agrupacionTematica.erase(it2);
            }
        }
    }
    return agrupacionTematica;
}

void Analizador::addNoticiaToAgrupacionEntidadMasFrecuente(std::shared_ptr<NoticiaInterface> noticia)
{
    bool agrupada = false;
    AgrupadorNoticias agrupadorNoticias;
    for (auto &grupo : agrupacionEntidadMasFrecuente)
    {
        for (auto &noticiaDeGrupo : grupo)
        {
            if (agrupadorNoticias.isAgregableEntidadMasFrecuente(noticiaDeGrupo, noticia))
            {
                grupo.push_back(noticia);
                agrupada = true;
                break;
            }
        }
        if (agrupada) break;
    }
    if (!agrupada)
    {
        Agrupacion agrupacion;
        agrupacion.push_back(noticia);
        agrupacionEntidadMasFrecuente.push_back(agrupacion);
    }
}

bool Analizador::isAgrupacionesAgrupables(Agrupacion &agrupacion1, Agrupacion &agrupacion2) const
{
    auto entidades1 = agrupacion1.getEntidades();
    auto entidades2 = agrupacion2.getEntidades();
    std::vector<std::string> entidadesComunes;
    set_intersection(entidades1.begin(),entidades1.end(),entidades2.begin(),entidades2.end(), std::back_inserter(entidadesComunes));
    if (entidadesComunes.size() != 0)
        return true;
    AgrupadorNoticias agrupadorNoticias;
    for (auto noticia1 : agrupacion1)
    {
        for (auto noticia2 : agrupacion2)
        {
            if (agrupadorNoticias.isAgregable(noticia1, noticia2))
                return true;
        }
    }
    return false;
}
