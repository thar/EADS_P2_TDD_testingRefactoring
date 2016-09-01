
#include "SalvadorDeAgrupacionesJson.h"
#include <fstream>
#include "ConversorJson.h"

void SalvadorDeAgrupacionesJson::salvar(std::list<Agrupacion> listaAgrupaciones, std::string rutaFichero)
{
    ConversorJson conversor;
    auto valores = conversor.getCampos(listaAgrupaciones);
    std::ofstream ficheroSalida(rutaFichero, std::ofstream::binary);
    ficheroSalida << valores;
}
