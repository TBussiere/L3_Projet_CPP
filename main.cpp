#include <iostream>
#include <cassert>
#include "Jeu.hpp"

int main() {
	Jeu* j = new Jeu("./map.txt");

	// std::cout << "add " << getOrientationVoiture(board, 1) << std::endl;
	// std::cout << "len " << getLenVoiture(board, 2) << std::endl;

	j->disp(j->board);

	j->BFS(j->board);

	j->disp(j->board);
	
	system("pause");
	return 0;
}