/*
 * Main.cpp
 *
 *  Created on: 27-dic-2012
 *      Author: Alvaro
 */

#include <NoticiasBuilder.h>
#include "iostream"
#include "Analizador.h"

int main() {

    std::shared_ptr<PalabrasReservadas> palabrasReservadas = std::make_shared<PalabrasReservadas>("data/ES_stopList.txt");
    std::shared_ptr<NoticiasBuilder> noticiasClasicasBuilder = std::make_shared<NoticiasBuilder>("data/news", palabrasReservadas);

    Analizador a1;
    a1.addNoticias(noticiasClasicasBuilder);

    std::cout << "Título noticias\n\n";
    std::cout << a1.toString();
    std::cout << "\n\n";
    std::cout << "Agrupación 1\n\n";
    std::cout << a1.agruparNoticias();
    std::cout << "\n\n";
    std::cout << "Agrupación 2\n\n";
    std::cout << a1.agruparNoticiasGeneral();

    return 0;
}
