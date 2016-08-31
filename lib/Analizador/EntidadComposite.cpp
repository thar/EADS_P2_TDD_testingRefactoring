/*
 * EntidadNombrada.cpp
 *
 *  Created on: 26-dic-2012
 *      Author: Alvaro
 */
#include <sstream>

#include "EntidadComposite.h"

EntidadComposite::EntidadComposite(const std::string n) :
		entidadNombrada() {
    entidadNombrada.insert(n);
}

std::set<std::string> EntidadComposite::getEntidadNombrada() const
{
    return entidadNombrada;
}

bool operator<(const EntidadComposite& lhs, const EntidadComposite& rhs)
{
    return lhs.entidadNombrada < rhs.entidadNombrada;
}

bool operator==(const EntidadComposite& lhs, const EntidadComposite& rhs)
{
    for (auto en : rhs.getEntidadNombrada())
        if (lhs.entidadNombrada.find(en) != lhs.entidadNombrada.end() )
            return true;
    return false;
}