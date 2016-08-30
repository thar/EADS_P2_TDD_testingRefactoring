/*
 * Noticia.cpp
 *
 *  Created on: 26-dic-2012
 *      Author: Alvaro
 */

#include "Noticia.h"
#include "list"
#include "EntidadNombrada.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <algorithm>

template <typename A, typename B>
std::multimap<B, A> flip_map(std::map<A,B> & src) {

    std::multimap<B,A> dst;

    for(auto it : src)
        dst.insert(std::pair<B, A>(it.second, it.first));

    return dst;
}

Noticia::Noticia() : titulo(""), cuerpo(""), entidades(), palabrasReservadas(), entidadMasFrecuente() {
}

Noticia::Noticia(std::string titulo, std::string cuerpo, std::string ruta) :
        titulo(titulo), cuerpo(cuerpo) {
    this->setPalabrasReservadas(ruta);
    this->setEntidades();
    this->setMasFrecuente();
}

void Noticia::setTitulo(std::string titulo) {
    this->titulo = titulo;
}

void Noticia::setCuerpo(std::string cuerpo) {
    this->cuerpo = cuerpo;
}

void Noticia::setPalabrasReservadas(std::string ruta) {
    std::ifstream file(ruta);
    for(std::string word; file >> word; )
        this->palabrasReservadas.push_back(word);
}

void Noticia::actualizar() {
    this->setEntidades();
    this->setMasFrecuente();
}

std::string Noticia::getTitulo() const {
    return this->titulo;
}

std::string Noticia::getCuerpo() const {
    return this->cuerpo;
}

EntidadNombrada Noticia::getMasFrecuente() const {
    return EntidadNombrada(entidadMasFrecuente, entidades.at(entidadMasFrecuente));
}

std::string Noticia::getEntidadMasFrecuente() const {
    return entidadMasFrecuente;
}

std::list<EntidadNombrada> Noticia::getEntidades() const {
    std::list<EntidadNombrada> l;
    for (auto pair : entidades)
    {
        l.push_back(EntidadNombrada(pair.first, pair.second));
    }
    return l;
}

std::list<std::string> Noticia::getPalabrasReservadas() const {
    return this->palabrasReservadas;
}

std::list<EntidadNombrada> Noticia::getEntidadesRelevantes() const {

    std::list<EntidadNombrada> lista;
    for (auto entidad : this->entidadesRelevantes)
        lista.push_back(EntidadNombrada(entidad, entidades.at(entidad)));

    return lista;
}

bool Noticia::esAgrupable(std::shared_ptr<NoticiaInterface> n) const {

    bool salida = false;

    std::string entidadMasFrecuenteNoticiaEntrada = n->getEntidadMasFrecuente();

    std::stringstream ss;
    ss.str(this->titulo);
    for(std::string word; ss >> word; )
    {
        if (word == entidadMasFrecuenteNoticiaEntrada)
            return true;
    }

    std::list<EntidadNombrada> primero = this->getEntidades();
    std::list<EntidadNombrada> segundo = n->getEntidadesRelevantes();
    std::list<EntidadNombrada> final;
    EntidadNombrada en1;
    EntidadNombrada en2;

    for (std::list<EntidadNombrada>::iterator it1 = primero.begin();
         it1 != primero.end(); it1++) {

        en1 = *it1;
        for (std::list<EntidadNombrada>::iterator it2 = segundo.begin();
             it2 != segundo.end(); it2++) {

            en2 = *it2;
            if (en1.esIgual(en2)) {
                final.push_back(en2);
            }
        }
    }

    if (final.size() >= (segundo.size() / 3)) {
        salida = true;
    }
    return salida;
}

std::string Noticia::toString() const {

    std::string salida;
    salida = "TITULO: " + this->titulo + "\n" + "CUERPO: " + this->cuerpo + "\n"
             + "ENTIDADES: ";

    std::list<EntidadNombrada> lista = this->getEntidades();

    for (std::list<EntidadNombrada>::iterator i = lista.begin();
         i != lista.end(); i++) {
        salida += i->toString();
        salida += " ";
    }

    salida = salida + "\n" + "MAS FRECUENTE: "
             + this->getMasFrecuente().toString();

    return salida;
}

void Noticia::setEntidades() {
    std::stringstream ss;
    ss.str(this->cuerpo);
    for(std::string word; ss >> word; )
    {
        bool entidadAgregada = this->agregarEntidad(word);
        if (entidadAgregada && ss.tellg() <= this->cuerpo.size() / 3)
        {
            this->entidadesRelevantes.push_back(word);
        }
    }
}

void Noticia::setMasFrecuente() {

    if (entidades.size() == 0)
    {
        entidadMasFrecuente = "";
        return;
    }
    std::multimap<int, std::string> reverseEntidades = flip_map(entidades);
    entidadMasFrecuente = reverseEntidades.rbegin()->second;
}

bool Noticia::agregarEntidad(std::string nombre) {
    if (!isalpha(nombre[0])) return false;
    if (islower(nombre[0])) return false;
    std::string copiaNombre = nombre;
    std::transform(copiaNombre.begin(), copiaNombre.end(), copiaNombre.begin(), ::tolower);
    if (std::find(this->palabrasReservadas.begin(), this->palabrasReservadas.end(), copiaNombre) != this->palabrasReservadas.end())
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

