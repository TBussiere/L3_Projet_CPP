#include "Jeu.hpp"
#include <string>
#include <iostream>
#include <vector>

Jeu::Jeu(std::string path){
	this->whidth = 6;
	this->height = 6;
	this->nbVoiture = 2;

	this->board = new int*[this->whidth];
	for(int i = 0; i < this->whidth; ++i)
		this->board[i] = new int[this->height];

	for (int i = 0; i < whidth; ++i) {
		for (int j = 0; j < height; ++j) {
			this->board[i][j] = 0;
		}
	}
}

void Jeu::addVoiture(int** board, int id, bool verti, int l, int x, int y) {
	// verti: est ce que la voiture est en vertical ou en horizontale
	// id: id de la voiture
	// l: longueur de la voiture
	// x, y: coordonnees de la premiere case de la voiture
	// la voiture remplira l cases a partir de [x][y] avec comme valeur id

	int a = 0;
	int b = 0;

	for (int i = 0; i < l; ++i) {
		this->board[x+a][y+b] = id;
		// std::cout << x+a << "/" << y+b << std::endl;

		if(verti) {
			b++;
		} else {
			a++;
		}
	}
}

bool Jeu::getOrientationVoiture(int** board, int id) {
	// return true si la voiture est en vertical

	for (int i = 0; i < this->height; ++i) {
		for (int j = 0; this->whidth < 6; ++j) {
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

int Jeu::getLenVoiture(int** board, int id) {
	// return la longueur de la voiture
	bool orientation = this->getOrientationVoiture(board, id);

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

int Jeu::getFirstX(int** board, int id) {
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

int Jeu::getFirstY(int** board, int id) {
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

int Jeu::moveVoiture(int** board, int id, bool direction) {
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

std::vector<int> Jeu::list_move(int** board) {
	for (int id = 1; id <= this->nbVoiture; id++) {
		int l = this->getLenVoiture(board, id);
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

void Jeu::disp(int** board){
	std::cout << "===========" << std::endl;
	for (int i = 0; i < whidth; ++i) {
		for (int j = 0; j < height; ++j) {
			std::cout << board[j][i] << " ";
		}
		std::cout << std::endl;
	}
}

void Jeu::BFS(int** board){
	std::vector<int> result = this->list_move(board);
	
	for(int i = 0; i < result.size(); i+=2)
	{
		int ** nboard = new int*[this->whidth];
		for(int i = 0; i < this->whidth; ++i)
			nboard[i] = new int[this->height];

		for(int j = 0; j < this->whidth; j++)
		{
			for(int k = 0; k < this->height; k++)
			{
				nboard[j][k] = board[j][k];
			}
		}

		
	}
}