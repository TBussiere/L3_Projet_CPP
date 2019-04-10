#include <iostream>
#include <cassert>
// #include "Jeu.hpp"
#include "Board_creator.hpp"

int main() {
	// const char* tmp = "./map.txt";
	// Jeu* j = new Jeu(tmp);
	
	// bool res = j->BFS(j->board);
	// if (res)
	// {
	// 	std::cout << "RESULT ====> "<< std::endl;
	// 	j->dispResult();
	// 	// system("pause");
	// }

	Board_creator(6, 6, 1, 9);
		
	// system("pause");
	return 0;
}