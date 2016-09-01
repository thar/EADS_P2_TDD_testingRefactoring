
#ifndef ANALIZARNOTICIASLINUX_PALABRASRESERVADAS_H
#define ANALIZARNOTICIASLINUX_PALABRASRESERVADAS_H

#include <set>
#include <string>
#include "PalabrasReservadasInterface.h"

class PalabrasReservadas : public PalabrasReservadasInterface
{
public:
    PalabrasReservadas() {}
    PalabrasReservadas(std::set<std::string> palabrasReservadas) : palabrasReservadas_(palabrasReservadas) {}
    PalabrasReservadas(const std::string rutaFichero);
    PalabrasReservadas(const char * rutaFichero) : PalabrasReservadas(std::string(rutaFichero)) {}

    bool has(std::string palabra);
    std::set<std::string>::iterator begin() { return palabrasReservadas_.begin(); }
    std::set<std::string>::iterator end() { return palabrasReservadas_.end(); }
    std::set<std::string>::size_type size() { return palabrasReservadas_.size(); }

protected:
private:
    std::set<std::string> palabrasReservadas_;
};


#endif //ANALIZARNOTICIASLINUX_PALABRASRESERVADAS_H
