#include <iostream>
#include <cassert>
#include "Board.hpp"
#include "Jeu.hpp"

int main() {
	Jeu* j = new Jeu("test");
	int test = j->board->board;

	std::cout << test;
	system("pause");
	return 0;
}