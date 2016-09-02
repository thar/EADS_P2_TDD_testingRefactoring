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

Noticia::Noticia() {
}

Noticia::Noticia(std::string titulo, std::vector<std::string> parrafos, std::shared_ptr<PalabrasReservadasInterface> palabrasReservadas) :
        titulo(titulo), parrafos(parrafos) {
    this->palabrasReservadas = palabrasReservadas;
    inicializar();
}

void Noticia::setTitulo(std::string titulo) {
    this->titulo = titulo;
}

void Noticia::setParrafos(std::vector<std::string> parrafos) {
    this->parrafos = parrafos;
}

std::string Noticia::getTitulo() const {
    return this->titulo;
}

std::string Noticia::getCuerpo() const {
    std::string cuerpo;
    if (parrafos.size())
    {
        cuerpo += parrafos[0];
        for (auto it = parrafos.begin() + 1; it != parrafos.end(); ++it)
            cuerpo += std::string("\n") + *it;
    }
    return cuerpo;
}

void Noticia::procesarEntidades() {
    LineWordIterator lit(getCuerpo());
    for (auto word : lit)
    {
        bool entidadAgregada = this->agregarEntidad(word);
        if (entidadAgregada && lit.getPosition() <= 1./3)
            this->entidadesRelevantes.insert(word);
    }
}
//TODO: Hay número mágicos
std::string Noticia::toString() const {

    std::string salida;
    salida = "TITULO: " + this->titulo + "\n" + "CUERPO: " + getCuerpo() + "\n"
             + "ENTIDADES: ";

    std::set<std::string> lista = this->getEntidades();

    for (std::set<std::string>::iterator i = lista.begin();
         i != lista.end(); i++) {
        salida += *i + " [" + std::to_string(this->getFrecuenciaEntidad(*i)) + "]";
        salida += " ";
    }

    salida = salida + "\n" + "MAS RELEVANTES: ";

    salida = salida + "\n" + "MAS FRECUENTE: "
             + this->getEntidadMasFrecuente().toString();

    return salida;
}

