
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
            this->insert(palabra);
    }
}

bool PalabrasReservadas::has(std::string palabra)
{
    return find(palabra) != end();
}
