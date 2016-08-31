/*
 * Analizador.cpp
 *
 *  Created on: 26-dic-2012
 *      Author: Alvaro
 */

#include "Analizador.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <glob.h>
#include <vector>
#include <algorithm>
#include "Noticia.h"

std::vector<std::string> globVector(const std::string& pattern){
    glob_t glob_result;
    glob(pattern.c_str(),GLOB_TILDE,NULL,&glob_result);
    std::vector<std::string> files;
    for(unsigned int i=0;i<glob_result.gl_pathc;++i){
        files.push_back(std::string(glob_result.gl_pathv[i]));
    }
    globfree(&glob_result);
    return files;
}

std::set<std::string> getEntidadesFromAgrupacion(Agrupacion &noticias)
{
    std::set<std::string> e;
    for (auto n : noticias)
    {
        const auto en = n->getEntidadMasFrecuente().getEntidadNombrada();
        e.insert(en.begin(), en.end());
    }
    return e;
}

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

    std::vector<std::string> fileList = globVector(rutaNoticias + "/*");

    for (auto file : fileList)
    {
        std::shared_ptr<NoticiaInterface> noticia = std::make_shared<Noticia>(file, rutaRestricciones);
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
	std::list<std::shared_ptr<NoticiaInterface>> lista = this->noticias;
	std::string salida = "";
	std::shared_ptr<NoticiaInterface> aux;
	for (std::list<std::shared_ptr<NoticiaInterface>>::iterator it = lista.begin(); it != lista.end();
			it++) {
		aux = *it;
		if (salida == "") {
			salida = salida + "Ruta del directorio: " + this->ruta + "\n\n";
		}
		salida = salida + "Titulo: " + aux->getTitulo() + "\n\n";
	}
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
    for (auto &grupo : agrupacionEntidadMasFrecuente)
    {
        for (auto &noticiaDeGrupo : grupo)
        {
            if (noticiaDeGrupo->getEntidadMasFrecuente() == noticia->getEntidadMasFrecuente())
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
    auto entidades1 = getEntidadesFromAgrupacion(agrupacion1);
    auto entidades2 = getEntidadesFromAgrupacion(agrupacion2);
    std::vector<std::string> entidadesComunes;
    set_intersection(entidades1.begin(),entidades1.end(),entidades2.begin(),entidades2.end(), std::back_inserter(entidadesComunes));
    if (entidadesComunes.size() != 0)
        return true;
    for (auto noticia1 : agrupacion1)
    {
        for (auto noticia2 : agrupacion2)
        {
            if (noticia1->esAgrupable(noticia2) || noticia2->esAgrupable(noticia1))
                return true;
        }
    }
    return false;
}

std::ostream& operator<<(std::ostream& os, const std::list<Agrupacion>& obj)
{
    for (auto grupo : obj)
    {
        auto e = getEntidadesFromAgrupacion(grupo);
        for (auto e1 : e)
        {
            os << e1 + " ";
        }
        os << std::endl;
        for (auto noticia : grupo)
        {
            os << "   *[" + noticia->getTitulo() + "]\n";
        }
        os << std::endl;
    }

    return os;
}
