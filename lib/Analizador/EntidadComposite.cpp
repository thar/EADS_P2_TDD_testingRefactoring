/*
 * EntidadNombrada.cpp
 *
 *  Created on: 26-dic-2012
 *      Author: Alvaro
 */
#include <sstream>

#include "EntidadComposite.h"

EntidadComposite::EntidadComposite(const std::string n)
{
}

std::set<std::string> EntidadComposite::getEntidadNombrada() const
{
    return std::set<std::string>();
}

bool operator<(const EntidadComposite& lhs, const EntidadComposite& rhs)
{
    return false;
}

bool operator==(const EntidadComposite& lhs, const EntidadComposite& rhs)
{
    return false;
}