
#include "PalabrasReservadas.h"

#include "FileLineIterator.h"
#include "LineWordIterator.h"

PalabrasReservadas::PalabrasReservadas(const std::string rutaFichero)
{
    FileLineIterator f(rutaFichero);
    for (auto linea : f)
    {
        LineWordIterator lineaIterator(linea);
        for (auto palabra : lineaIterator)
            palabrasReservadas_.insert(palabra);
    }
}

bool PalabrasReservadas::has(std::string palabra)
{
    return palabrasReservadas_.find(palabra) != palabrasReservadas_.end();
}
