#include "Board.hpp"

Board::Board(int** plat, Board* pred) {
	this->plat = plat;
	this->pred = pred;
}

Board::~Board() {
	for (int i = 0; i < 6; i++)
	{
		delete[] this->plat[i];
	}

	delete[] plat;
	delete[] pred;
}