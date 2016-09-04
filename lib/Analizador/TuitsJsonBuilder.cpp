
#include "TuitsJsonBuilder.h"
#include <fstream>
#include "json/json.h"

TuitsJsonBuilder::TuitsJsonBuilder(std::string pathFicheroTuits, std::shared_ptr<PalabrasReservadasInterface> palabrasReservadas) :
        pathFicheroTuits(pathFicheroTuits), palabrasReservadas(palabrasReservadas)
{
}

std::vector<std::shared_ptr<NoticiaInterface>> TuitsJsonBuilder::getNoticias()
{
    Json::Value root;
    std::ifstream tuitsFile(pathFicheroTuits, std::ifstream::binary);
    tuitsFile >> root;
    if (root.size() > 0)
    {
        std::vector<std::shared_ptr<NoticiaInterface>> tuits(root.size());
        for (int index = 0; index < root.size(); ++index)
            tuits[index] = std::make_shared<Tuit>(root[index], palabrasReservadas);
        return tuits;
    } else
        return std::vector<std::shared_ptr<NoticiaInterface>>();
}
