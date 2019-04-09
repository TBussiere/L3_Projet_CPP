#ifndef BOARD_HPP
#define BOARD_HPP

class Board {
public:
	int** plat;
	Board* pred;

	Board(int** plat, Board* pred);
};

#endif
