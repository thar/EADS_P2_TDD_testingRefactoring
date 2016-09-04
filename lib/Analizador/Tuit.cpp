
#include "Tuit.h"
#include "LineWordIterator.h"
#include <algorithm>

template <typename A, typename B>
std::multimap<B, A> flip_map(std::map<A,B> & src) {

    std::multimap<B,A> dst;

    for(auto it : src)
        dst.insert(std::pair<B, A>(it.second, it.first));

    return dst;
}

Tuit::Tuit(Json::Value& inputData, std::shared_ptr<PalabrasReservadasInterface> palabrasReservadas) :
palabrasReservadas(palabrasReservadas), tuit(inputData.get("tuit", "" ).asString()),
user(inputData.get("user", "" ).asString()), id(inputData.get("id", -1 ).asInt())
{
    inicializar();
}

void Tuit::procesarEntidades() {
    LineWordIterator lineaIterator(tuit);
    for (auto palabra : lineaIterator)
        this->agregarEntidad(palabra);
}

void Tuit::inicializar() {
    this->procesarEntidades();
    this->procesarEntidadMasFrecuente();
}

std::set<std::string> Tuit::getEntidades() const {
    std::set<std::string> l;
    for (auto pair : entidades)
    {
        l.insert(pair.first);
    }
    return l;
}

int Tuit::getFrecuenciaEntidad(EntidadComposite entidad) const
{
    for (auto e : entidad.getEntidadNombrada())
    {
        auto idx = entidades.find(e);
        if (idx != entidades.end())
            return idx->second;
    }
    return 0;
}

void Tuit::procesarEntidadMasFrecuente() {

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

bool Tuit::agregarEntidad(std::string nombre) {
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

std::string Tuit::toString() const
{
    return "";
}