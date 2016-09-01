/*
 * Noticia.cpp
 *
 *  Created on: 26-dic-2012
 *      Author: Alvaro
 */

#include "Noticia.h"
#include "list"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <FileLineIterator.h>
#include <LineWordIterator.h>

template <typename A, typename B>
std::multimap<B, A> flip_map(std::map<A,B> & src) {

    std::multimap<B,A> dst;

    for(auto it : src)
        dst.insert(std::pair<B, A>(it.second, it.first));

    return dst;
}

Noticia::Noticia() : titulo(""), cuerpo(""), entidades(), palabrasReservadas(), entidadMasFrecuente() {
}

Noticia::Noticia(std::string titulo, std::string cuerpo, std::shared_ptr<PalabrasReservadasInterface> palabrasReservadas) :
        titulo(titulo), cuerpo(cuerpo) {
    this->setPalabrasReservadas(palabrasReservadas);
    this->procesarEntidades();
    this->procesarEntidadMasFrecuente();
}

Noticia::Noticia(std::string rutaNoticia, std::shared_ptr<PalabrasReservadasInterface> palabrasReservadas) :
        titulo(""), cuerpo(""), entidades(), palabrasReservadas(), entidadMasFrecuente() {
    FileLineIterator f(rutaNoticia);
    if (f.is_open()) {
        for (auto line : f)
        {
            static int index = 0;
            if (titulo == "") {
                titulo = line;
            } else {
                if (cuerpo == "")
                    cuerpo = line;
                else
                    cuerpo += " " + line;
            }
        }
    }

    this->setPalabrasReservadas(palabrasReservadas);
    this->procesarEntidades();
    this->procesarEntidadMasFrecuente();
}

void Noticia::setTitulo(std::string titulo) {
    this->titulo = titulo;
}

void Noticia::setCuerpo(std::string cuerpo) {
    this->cuerpo = cuerpo;
}

void Noticia::setPalabrasReservadas(std::shared_ptr<PalabrasReservadasInterface> palabrasReservadas) {
    this->palabrasReservadas = palabrasReservadas;
}

void Noticia::inicializar() {
    this->procesarEntidades();
    this->procesarEntidadMasFrecuente();
}

std::string Noticia::getTitulo() const {
    return this->titulo;
}

std::string Noticia::getCuerpo() const {
    return this->cuerpo;
}

EntidadComposite Noticia::getEntidadMasFrecuente() const {
    return entidadMasFrecuente;
}

std::list<std::string> Noticia::getEntidades() const {
    std::list<std::string> l;
    for (auto pair : entidades)
    {
        l.push_back(pair.first);
    }
    return l;
}

int Noticia::getFrecuenciaEntidad(EntidadComposite entidad) const
{
    for (auto e : entidad.getEntidadNombrada())
    {
        auto idx = entidades.find(e);
        if (idx != entidades.end())
            return idx->second;
    }
    return 0;
}

std::shared_ptr<PalabrasReservadasInterface> Noticia::getPalabrasReservadas() const {
    return this->palabrasReservadas;
}

std::list<std::string> Noticia::getEntidadesRelevantes() const {
    return this->entidadesRelevantes;
}

bool Noticia::esAgrupable(std::shared_ptr<NoticiaInterface> n) const {

    EntidadComposite entidadMasFrecuenteNoticiaEntrada = n->getEntidadMasFrecuente();

    LineWordIterator lit(titulo);
    for (auto word : lit)
    {
        if (word == entidadMasFrecuenteNoticiaEntrada)
            return true;
    }

    std::list<std::string> entidadesRelevantesNoticiaExterna = n->getEntidadesRelevantes();
    int cuentaEntidadesRelevantesEncontradas = 0;

    for (auto entidadRelevanteExterna : entidadesRelevantesNoticiaExterna)
    {
        if (entidades.find(entidadRelevanteExterna) != entidades.end())
        {
            ++cuentaEntidadesRelevantesEncontradas;
        }
    }

    return (cuentaEntidadesRelevantesEncontradas >= (entidadesRelevantesNoticiaExterna.size() / 3));
}

std::string Noticia::toString() const {

    std::string salida;
    salida = "TITULO: " + this->titulo + "\n" + "CUERPO: " + this->cuerpo + "\n"
             + "ENTIDADES: ";

    std::list<std::string> lista = this->getEntidades();

    for (std::list<std::string>::iterator i = lista.begin();
         i != lista.end(); i++) {
        salida += *i + " [" + std::to_string(this->getFrecuenciaEntidad(*i)) + "]";
        salida += " ";
    }

    salida = salida + "\n" + "MAS RELEVANTES: ";

    salida = salida + "\n" + "MAS FRECUENTE: "
             + this->getEntidadMasFrecuente().toString();

    return salida;
}

void Noticia::procesarEntidades() {
    LineWordIterator lit(cuerpo);
    for (auto word : lit)
    {
        bool entidadAgregada = this->agregarEntidad(word);
        if (entidadAgregada && lit.getPosition() <= 1./3)
            this->entidadesRelevantes.push_back(word);
    }
}

void Noticia::procesarEntidadMasFrecuente() {

    entidadMasFrecuente = EntidadComposite();
    if (entidades.size() == 0)
    {
        return;
    }
    auto reverseEntidades = flip_map(entidades);
    int mayorFrecuencia = reverseEntidades.rbegin()->first;
    auto ret = reverseEntidades.equal_range(mayorFrecuencia);
    for (auto it=ret.first; it!=ret.second; ++it)
        entidadMasFrecuente += it->second;
}

bool Noticia::agregarEntidad(std::string nombre) {
    if (!isalpha(nombre[0])) return false;
    if (islower(nombre[0])) return false;
    std::string copiaNombre = nombre;
    std::transform(copiaNombre.begin(), copiaNombre.end(), copiaNombre.begin(), ::tolower);
    if (palabrasReservadas->has(copiaNombre))
        return false;
    auto entidad = entidades.find(nombre);
    if (entidad != entidades.end())
    {
        ++entidades[nombre];
        return false;
    }
    else
    {
        entidades.insert(std::pair<std::string, int>(nombre, 1));
        return true;
    }
}

