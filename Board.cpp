#include "Board.hpp"

Board::Board(int** plat, Board* pred) {
	this->plat = plat;
	this->pred = pred;
}