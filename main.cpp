#include <iostream>
#include <cassert>
#include "Jeu.hpp"
#include "Board_creator.hpp"

int main() {

	// il faut choisir la map parmis celles disponibles dans le dossier
	// la map 1 est celle de base avec le projet
	// la map 2 est resolvable en 3 coups
	// la map 3 est resolvable en 34 coups ??
	// la map 5 est resolvable en 21 coups
	// la map 6 est resolvable en 25 coups
	const char* tmp = "./map5.txt";
	Jeu* j = new Jeu(tmp);
	bool res = j->BFS(j->board);
 	if (res)
	{
 		std::cout << "RESULT ====> "<< std::endl;
 		j->dispResult();
	}

	// hauteur, largeur, nb de board voulus, nb min coups
	// Board_creator(6, 6, 1, 10);

	return 0;
}