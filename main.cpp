#include <iostream>
#include <cassert>
#include "Jeu.hpp"

int main() {
	const char* tmp = "./map.txt";
	Jeu* j = new Jeu(tmp);

	// std::cout << "add " << getOrientationVoiture(board, 1) << std::endl;
	// std::cout << "len " << getLenVoiture(board, 2) << std::endl;
	j->disp(j->board);
	j->list_move(j->board);

	bool res = j->BFS(j->board);
	if (res)
	{
		std::cout << "RESULT ====> "<< std::endl;
		j->dispResult();
		system("pause");
	}
	
	//system("pause");
	return 0;
}