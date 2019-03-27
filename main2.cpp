#include <iostream>
#include <cassert>
#include <vector>

typedef std::vector<int> int_vec_t;


void addVoiture(int board[6][6], int id, bool verti, int l, int x, int y) {
	// verti: est ce que la voiture est en vertical ou en horizontale
	// id: id de la voiture
	// l: longueur de la voiture
	// x, y: coordonnees de la premiere case de la voiture
	// la voiture remplira l cases a partir de [x][y] avec comme valeur id

	int a = 0;
	int b = 0;

	for (int i = 0; i < l; ++i) {
		board[x+a][y+b] = id;
		// std::cout << x+a << "/" << y+b << std::endl;

		if(verti) {
			b++;
		} else {
			a++;
		}
	}
}

bool getOrientationVoiture(int board[6][6], int id) {
	// return true si la voiture est en vertical

	for (int i = 0; i < 6; ++i) {
		for (int j = 0; j < 6; ++j) {
			if (board[i][j] == id) {
				if(j == 0) {
					return board[i][j+1] == id;
				} else if(j == 5) {
					return board[i][j-1] == id;
				} else {
					return board[i][j+1] == id || board[i][j-1] == id;
				}
			}
		}
	}
	return false;
}

int getLenVoiture(int board[6][6], int id) {
	// return la longueur de la voiture
	bool orientation = getOrientationVoiture(board, id);

	for (int i = 0; i < 6; ++i) {
		for (int j = 0; j < 6; ++j) {
			if (board[i][j] == id) {
				int a = 0;
				int b = 0;
				int len = 0;

				while(board[i+a][j+b] == id) {
				    len++;
				    if (orientation) {
						b++;
					} else {
						a++;
					}
				}

				return len;
			}
		}
	}
	return -1;
}

int getFirstX(int board[6][6], int id) {
	// return la coordonne x de la premiere case appartenant a la voiture

	for (int i = 0; i < 6; ++i) {
		for (int j = 0; j < 6; ++j) {
			if (board[i][j] == id) {
				return i;
			}
		}
	}
	return -1;
}

int getFirstY(int board[6][6], int id) {
	// return la coordonne y de la premiere case appartenant a la voiture

	for (int i = 0; i < 6; ++i) {
		for (int j = 0; j < 6; ++j) {
			if (board[i][j] == id) {
				return j;
			}
		}
	}
	return -1;
}

int moveVoiture(int board[6][6], int id, bool direction) {
	// id: id de la voiture a bouger
	// direction: direction du movement de la voiture
	// 			  le sens depend de l'orientation de la voiture 
	// 			  true  => vers le bas ou la droite
	// 			  false => vers la gauche ou le haut

	// int x = getFirstX(board, id);
	// int y = getFirstY(board, id);
	int l = getLenVoiture(board, id);
	int x, y;
	bool trouve = false;

	// todo
	// a optimiser pour eviter de chercher plusieurs fois les pos des voitures
	// lors de la recherche de la longueur de la voiture, etc.
	for (int i = 0; i < 6; ++i) {
		for (int j = 0; j < 6; ++j) {
			if (board[i][j] == id && !trouve) {
				x = i;
				y = j;
				trouve = true;
			}
		}
	}

	if (getOrientationVoiture(board, id)) { // si vertical
		if(direction) { // vers le bas
			if(y+l < 6 && board[x][y+l] == 0) {
				board[x][y] = 0;
				board[x][y+l] = id;
			}
		} else { // vers le haut
			if(y > 0 && board[x][y-1] == 0) {
				board[x][y-1] = id;
				board[x][y+l-1] = 0;
			}
		}
	} else { // si horizontal
		if(direction) { // vers la droite
			if(x+l < 6 && board[x+l][y] == 0) {
				board[x][y] = 0;
				board[x+l][y] = id;
			}
		} else { // vers la gauche
			if(x > 0 && board[x-1][y] == 0) {
				board[x-1][y] = id;
				board[x+l-1][y] = 0;
			}
		}
	}

	return 0;
}

std::vector<int> list_move(int board[6][6], int nbVoiture) {
	std::vector<int> v_move;
	for (int id = 1; id <= nbVoiture; id++) {
		int l = getLenVoiture(board, id);
		int x, y;
		bool trouve = false;

		// todo
		// a optimiser pour eviter de chercher plusieurs fois les pos des voitures
		// lors de la recherche de la longueur de la voiture, etc.
		for (int i = 0; i < 6; ++i) {
			for (int j = 0; j < 6; ++j) {
				if (board[i][j] == id && !trouve) {
					x = i;
					y = j;
					trouve = true;
				}
			}
		}

		int a = 1;
		int b = -1;
		bool ori = getOrientationVoiture(board, id);

		if (ori) {
			// std::cout << x << "/" << y << "/" << l << std::endl;
			while(board[x][y+l-1+a] == 0 && y+l-1+a < 6) {
				// std::cout << "cout possible + : " << id << "/" << a << std::endl;
				v_move.push_back(id);
				v_move.push_back(a);
				a++;
			}

			while(board[x][y+b] == 0 && y+b >= 0) {
				// std::cout << "cout possible - : " << id << "/" << b << std::endl;
				v_move.push_back(id);
				v_move.push_back(b);
				b--;
			}
			
		} else {
			// std::cout << x << "/" << y << "/" << l << std::endl;
			while(board[x+l-1+a][y] == 0 && x+l-1+a < 6) {
				// std::cout << "cout possible + : " << id << "/" << a << " | " << 9 << std::endl;
				v_move.push_back(id);
				v_move.push_back(a);
				a++;
			}

			// std::cout << "test - : " << id << "/" << b << " | " << x-1+b << std::endl;
			while(board[x+b][y] == 0 && x+b >= 0) {
				// std::cout << "cout possible - : " << id << "/" << b << std::endl;
				v_move.push_back(id);
				v_move.push_back(b);
				b--;
			}
		}
	}

	return v_move;
}

int main() {
	int whidth = 6;
	int height = 6;

	int board[6][6];

	for (int i = 0; i < whidth; ++i) {
		for (int j = 0; j < height; ++j) {
			board[i][j] = 0;
		}
	}
	// board, id voiture, orientation true=>vertical, longueur, x, y
	addVoiture(board, 1, true, 2, 1, 3);
	addVoiture(board, 2, false, 3, 2, 1);

	// std::cout << "add " << getOrientationVoiture(board, 1) << std::endl;
	// std::cout << "len " << getLenVoiture(board, 2) << std::endl;

	// std::cout << "fpos " << getFirstX(board, 1) << std::endl;
	// std::cout << "fpos " << getFirstY(board, 1) << std::endl;

	std::cout << "===========" << std::endl;
	for (int i = 0; i < whidth; ++i) {
		for (int j = 0; j < height; ++j) {
			std::cout << board[j][i] << " ";
		}
		std::cout << std::endl;
	}

	std::vector<int> v_move = list_move(board, 2);
	for (int i = 0; i < v_move.size(); i += 2) {
		std::cout << "cout possible: " << v_move[i] << "/" << v_move[i+1] << std::endl;
	}

	// moveVoiture(board, 2, false);
	// moveVoiture(board, 2, false);
	// moveVoiture(board, 2, false);
	moveVoiture(board, 2, true);
	moveVoiture(board, 2, true);

	std::cout << "===========" << std::endl;
	for (int i = 0; i < whidth; ++i) {
		for (int j = 0; j < height; ++j) {
			std::cout << board[j][i] << " ";
		}
		std::cout << std::endl;
	}

	return 0;
}
