#include <iostream>
#include <cassert>
#include "Jeu.hpp"

int main() {
	Jeu* j = new Jeu("test");

	
	// board, id voiture, orientation true=>vertical, longueur, x, y
	j->addVoiture(j->board, 1, true, 2, 1, 3);
	j->addVoiture(j->board, 2, false, 3, 1, 1);

	// std::cout << "add " << getOrientationVoiture(board, 1) << std::endl;
	// std::cout << "len " << getLenVoiture(board, 2) << std::endl;

	std::cout << "fpos " << j->getFirstX(j->board, 1) << std::endl;
	std::cout << "fpos " << j->getFirstY(j->board, 1) << std::endl;

	j->disp(j->board);

	//j->list_move(j->board, 2);

	j->moveVoiture(j->board, 2, true);
	j->moveVoiture(j->board, 2, true);

	j->disp(j->board);
	
	system("pause");
	return 0;
}