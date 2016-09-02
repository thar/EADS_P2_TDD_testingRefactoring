
#include "Tuit.h"
#include "LineWordIterator.h"
#include <algorithm>


Tuit::Tuit(Json::Value& inputData, std::shared_ptr<PalabrasReservadasInterface> palabrasReservadas) :
tuit(inputData.get("tuit", "" ).asString()),
user(inputData.get("user", "" ).asString()), id(inputData.get("id", -1 ).asInt())
{
    this->palabrasReservadas = palabrasReservadas;
    inicializar();
}

void Tuit::procesarEntidades() {
    LineWordIterator lit(getTitulo());
    for (auto word : lit)
        agregarEntidad(word);
}

std::string Tuit::toString() const
{
    return "";
}