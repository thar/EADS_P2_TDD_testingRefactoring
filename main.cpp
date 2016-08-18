/*
 * Main.cpp
 *
 *  Created on: 27-dic-2012
 *      Author: Alvaro
 */

#include "iostream"
#include "Analizador.h"

int main() {

	Analizador a1("data");

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
