
#include "LineWordIterator.h"
#include <algorithm>
#include "NoticiaLocal.h"

template <typename A, typename B>
std::multimap<B, A> flip_map(std::map<A,B> & src) {

    std::multimap<B,A> dst;

    for(auto it : src)
        dst.insert(std::pair<B, A>(it.second, it.first));

    return dst;
}

void NoticiaLocal::setPalabrasReservadas(std::shared_ptr<PalabrasReservadasInterface> palabrasReservadas) {
    this->palabrasReservadas = palabrasReservadas;
}

void NoticiaLocal::inicializar() {
    procesarEntidades();
    procesarEntidadMasFrecuente();
}

EntidadComposite NoticiaLocal::getEntidadMasFrecuente() const {
    return entidadMasFrecuente;
}

std::set<std::string> NoticiaLocal::getEntidades() const {
    std::set<std::string> l;
    for (auto pair : entidades)
    {
        l.insert(pair.first);
    }
    return l;
}

int NoticiaLocal::getFrecuenciaEntidad(EntidadComposite entidad) const
{
    for (auto e : entidad.getEntidadNombrada())
    {
        auto idx = entidades.find(e);
        if (idx != entidades.end())
            return idx->second;
    }
    return 0;
}

std::shared_ptr<PalabrasReservadasInterface> NoticiaLocal::getPalabrasReservadas() const {
    return this->palabrasReservadas;
}

std::set<std::string> NoticiaLocal::getEntidadesRelevantes() const {
    return this->entidadesRelevantes;
}

void NoticiaLocal::procesarEntidadMasFrecuente() {

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

bool NoticiaLocal::agregarEntidad(std::string nombre) {
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