
#include "AgrupadorNoticias.h"

#include "LineWordIterator.h"
#include "Noticia.h"
#include "Tuit.h"
#include <list>
#include <vector>
#include <algorithm>


bool compare_NoticiaType (const std::pair<NoticiaType, std::shared_ptr<NoticiaInterface>>& first, const std::pair<NoticiaType, std::shared_ptr<NoticiaInterface>>& second)
{
    return first.first < second.first;
}

bool AgrupadorNoticias::isAgregableEntidadMasFrecuente(std::shared_ptr<NoticiaInterface> n1, std::shared_ptr<NoticiaInterface> n2) const
{
    return n1->getEntidadMasFrecuente() == n2->getEntidadMasFrecuente();
}

bool AgrupadorNoticias::isAgregable(std::shared_ptr<NoticiaInterface> n1, std::shared_ptr<NoticiaInterface> n2)
{
    std::list<std::pair<NoticiaType, std::shared_ptr<NoticiaInterface>>> parTipoNoticia;
    n1->accept(*this);
    parTipoNoticia.push_back(std::make_pair(noticiaType_, n1));
    n2->accept(*this);
    parTipoNoticia.push_back(std::make_pair(noticiaType_, n2));
    parTipoNoticia.sort(compare_NoticiaType);
    bool resultado = false;
    switch (parTipoNoticia.front().first)
    {
        case NOTICIA_TEXTO:
            switch (parTipoNoticia.back().first)
            {
                case NOTICIA_TEXTO:
                {
                    Noticia &noticia1Reference = reinterpret_cast<Noticia &>(*parTipoNoticia.front().second);
                    Noticia &noticia2Reference = reinterpret_cast<Noticia &>(*parTipoNoticia.back().second);
                    resultado = isAgregable(noticia1Reference, noticia2Reference);
                    resultado |= isAgregable(noticia2Reference, noticia1Reference);
                }
                    break;
                case TUIT:
                {
                    Noticia &noticia1Reference = reinterpret_cast<Noticia &>(*parTipoNoticia.front().second);
                    Tuit &noticia2Reference = reinterpret_cast<Tuit &>(*parTipoNoticia.back().second);
                    resultado = isAgregable(noticia1Reference, noticia2Reference);
                }
                    break;
            }
            break;
        case TUIT:
            switch (parTipoNoticia.back().first)
            {
                case TUIT:
                {
                    Tuit &noticia1Reference = reinterpret_cast<Tuit &>(*parTipoNoticia.front().second);
                    Tuit &noticia2Reference = reinterpret_cast<Tuit &>(*parTipoNoticia.back().second);
                    resultado = isAgregable(noticia1Reference, noticia2Reference);
                    resultado |= isAgregable(noticia2Reference, noticia1Reference);
                }
                    break;
                default:
                    break;
            }
            break;
    }
    return resultado;
}

void AgrupadorNoticias::visit(Noticia& n)
{
    noticiaType_ = NOTICIA_TEXTO;
}

bool AgrupadorNoticias::isAgregable(Noticia &n1, Noticia &n2) const
{
    if (n1.getEntidadMasFrecuente() == n2.getEntidadMasFrecuente())
        return true;

    auto entidadesN2 = n2.getEntidades();
    auto entidadesRelevantesN1 = n1.getEntidadesRelevantes();

    std::vector<std::string> entidadesComunes;
    set_intersection(entidadesRelevantesN1.begin(),entidadesRelevantesN1.end(),entidadesN2.begin(),entidadesN2.end(), std::back_inserter(entidadesComunes));

    auto valorMinimoDeEntidadesCompartidas = getMinimoNumeroEntidadesParaAgrupacionTematicaNoticiaTexto(n1);
    auto entidadEnTitulo = isEntidadEnTexto(n1.getEntidadMasFrecuente(), n2.getTitulo());
    return entidadEnTitulo && (entidadesComunes.size() >= valorMinimoDeEntidadesCompartidas);
}

//TODO: Número mágico
unsigned long AgrupadorNoticias::getMinimoNumeroEntidadesParaAgrupacionTematicaNoticiaTexto(Noticia& n) const
{
    return (n.getEntidadesRelevantes().size() / 3);
}

bool AgrupadorNoticias::isEntidadEnTexto(const EntidadComposite entidad, const std::string texto) const
{
    LineWordIterator lineaIterator(texto);
    for (auto palabra : lineaIterator)
    {
        if (palabra == entidad)
            return true;
    }
    return false;
}

void AgrupadorNoticias::visit(Tuit &n)
{
    noticiaType_ = TUIT;
}

bool AgrupadorNoticias::isAgregable(Noticia &n1, Tuit &n2) const
{
    if (n1.getEntidadMasFrecuente() == n2.getEntidadMasFrecuente())
        return true;

    const auto entidadesTuit = n2.getEntidades();
    const auto entidadMasFrecuenteN1 = n1.getEntidadMasFrecuente();

    for (const auto entidad : entidadesTuit)
    {
        if (entidad == entidadMasFrecuenteN1)
            return true;
    }

    return false;
}

bool AgrupadorNoticias::isAgregable(Tuit &n1, Tuit &n2) const
{
    if (n1.getEntidadMasFrecuente() == n2.getEntidadMasFrecuente())
        return true;

    auto entidadesN1 = n1.getEntidades();
    auto entidadesN2 = n2.getEntidades();

    std::vector<std::string> entidadesComunes;
    set_intersection(entidadesN1.begin(),entidadesN1.end(),entidadesN2.begin(),entidadesN2.end(), std::back_inserter(entidadesComunes));
    return entidadesComunes.size() > 0;
}
