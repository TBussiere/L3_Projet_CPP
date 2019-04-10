#ifndef BOARD_HPP
#define BOARD_HPP

class Board {
public:
	int** plat;
	//prédécéseur utile quand la solution est trouvée pour remplir la pile des resultats en O(n) n etant le nombre de coup de la solution
	Board* pred;

	Board(int** plat, Board* pred);
	~Board();
};
#endif
