
#include "AgrupadorNoticias.h"

#include "LineWordIterator.h"
#include "Noticia.h"
#include <list>
#include <vector>
#include <algorithm>

bool AgrupadorNoticias::isAgregableEntidadMasFrecuente(std::shared_ptr<NoticiaInterface> n1, std::shared_ptr<NoticiaInterface> n2) const
{
    return true;
}

bool AgrupadorNoticias::isAgregable(std::shared_ptr<NoticiaInterface> n1, std::shared_ptr<NoticiaInterface> n2)
{
    return true;
}

void AgrupadorNoticias::visit(Noticia& n)
{
}