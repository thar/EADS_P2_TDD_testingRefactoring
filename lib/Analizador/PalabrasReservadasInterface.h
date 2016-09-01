
#ifndef ANALIZARNOTICIASLINUX_PALABRASRESERVADASINTERFACE_H
#define ANALIZARNOTICIASLINUX_PALABRASRESERVADASINTERFACE_H


#include <string>
#include <set>

class PalabrasReservadasInterface
{
public:
    virtual bool has(std::string) = 0;
    virtual std::set<std::string>::iterator begin() = 0;
    virtual std::set<std::string>::iterator end() = 0;
    virtual std::set<std::string>::size_type size() = 0;


};


#endif //ANALIZARNOTICIASLINUX_PALABRASRESERVADASINTERFACE_H
