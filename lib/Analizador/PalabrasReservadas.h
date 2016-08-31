
#ifndef ANALIZARNOTICIASLINUX_PALABRASRESERVADAS_H
#define ANALIZARNOTICIASLINUX_PALABRASRESERVADAS_H

#include <set>
#include <string>

class PalabrasReservadas : public std::set<std::string>
{
public:
    PalabrasReservadas() {}
    PalabrasReservadas(std::set<std::string> palabrasReservadas) : std::set<std::string>(palabrasReservadas) {}
    PalabrasReservadas(const std::string rutaFichero);
    PalabrasReservadas(const char * rutaFichero) : PalabrasReservadas(std::string(rutaFichero)) {}

    bool has(std::string palabra);

protected:
private:
};


#endif //ANALIZARNOTICIASLINUX_PALABRASRESERVADAS_H
