#include "Board_creator.hpp"
#include "Move.hpp"
#include <iostream>
#include <vector>
#include <fstream>
#include <random>
#include <sstream>
#include <string>
#include <queue>
#include <stack>
#include <unordered_map>
#include <time.h>


// beaucoup des fonctions dans ce fichier sont tres similaires a celles dans la classe Jeu
// elles ont ete adaptees a la creation de board
// deplus par manque de temps je n'ai pas pu les merge avec celles de Jeu 

bool addVoiture(int** board, int id, bool verti, int l, int x, int y, bool verif) {
	// verti: est ce que la voiture est en vertical ou en horizontale
	// id: id de la voiture
	// l: longueur de la voiture
	// x, y: coordonnees de la premiere case de la voiture
	// la voiture remplira les cases a partir de [x][y] avec comme valeur id si il n'y a pas deja de voiture
	// renvoie si la voiture a ete place
	// verif: on verifie si la voiture ajoutee n'ecrase pas une deja existante

	int a = 0;
	int b = 0;

	if(verif) {
		for (int i = 0; i < l; ++i) { // on parcourt une premiere fois pour verifier qu'il n'y a pas deja de voitures a cet emplacement
			if(board[x+a][y+b] !=0) {
				std::cout << "deja pris!!!!!!!!!!!!" << std::endl;
				return false;
			}

			if(verti) { b++; }
			else { a++; }
		}
	}

	a = 0;
	b = 0;

	for (int i = 0; i < l; ++i) {
		board[x+a][y+b] = id;

		if(verti) { b++; }
		else { a++; }
	}

	return true;
}

bool getOrientationVoiture(int** board, int id, int height, int x, int y) {
	// return true si la voiture est en vertical
	if(x < height && x >= 0 && y < height && y >= 0) {
		if (board[x][y] == id) {
			if(y == 0) {
				return board[x][y+1] == id;
			} else if(y == height -1) {
				return board[x][y-1] == id;
			} else {
				return board[x][y+1] == id || board[x][y-1] == id;
			}
		}
	}
	return false;
}

int getLenVoiture(int** board, int id, int height, int x, int y) {
	// return la longueur de la voiture
	if(x < height && x >= 0 && y < height && y >= 0) {
		bool orientation = getOrientationVoiture(board, id, height, x, y);
		if (board[x][y] == id) {
			int a = 0;
			int b = 0;
			int len = 0;

			while(x+a < height && y+b < height && board[x+a][y+b] == id) {
			    len++;
			    if (orientation) { b++; }
			    else { a++; }
			}

			return len;
		}
	}
	return -1;
}

int getFirstX(int** board, int id, int height) {
	// return la coordonne x de la premiere case appartenant a la voiture

	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < height; ++j) {
			if (board[i][j] == id) {
				return i;
			}
		}
	}
	return -1;
}

int getFirstY(int** board, int id, int height) {
	// return la coordonne y de la premiere case appartenant a la voiture

	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < height; ++j) {
			if (board[i][j] == id) {
				return j;
			}
		}
	}
	return -1;
}

int moveVoiture(int** board, int id, bool direction, int height) {
	// id: id de la voiture a bouger
	// direction: direction du movement de la voiture
	// 			  le sens depend de l'orientation de la voiture 
	// 			  true  => vers le bas ou la droite
	// 			  false => vers la gauche ou le haut

	int x, y;
	bool trouve = false;

	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < height; ++j) {
			if (board[i][j] == id && !trouve) {
				x = i;
				y = j;
				trouve = true;
			}
		}
	}

	if(!trouve)
		return 0;

	int l = getLenVoiture(board, id, height, x, y);
	if (getOrientationVoiture(board, id, height, x, y)) { // si vertical
		if(direction) { // vers le bas
			if(y+l < height && board[x][y+l] == 0) {
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
			if(x+l < height && board[x+l][y] == 0) {
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

int get_nb_voiture(int** board, int height) {
	// le nombre de voiture est egale au plus grand id des voitures
	int max = 0;
	int c_id; // current id
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < height; ++j) {
			c_id = board[i][j];
			if (c_id > max) {
				max = c_id;
			}
		}
	}

	return max;
}

std::vector<int> list_move(int** board, int height, int nbVoiture) {
	std::vector<int> v_move;
	for (int id = 1; id <= nbVoiture; id++) {

		int x, y;
		bool trouve = false;

		for (int i = 0; i < height; ++i) {
			for (int j = 0; j < height; ++j) {
				if (board[i][j] == id && !trouve) {
					x = i;
					y = j;
					trouve = true;
				}
			}
		}

		if(!trouve)
			return v_move;

		int l = getLenVoiture(board, id, height, x, y);

		int a = 1;
		int b = -1;
		bool ori = getOrientationVoiture(board, id, height, x, y);

		if (ori) {
			while(y+l-1+a < height && board[x][y+l-1+a] == 0) {
				v_move.push_back(id);
				v_move.push_back(a);
				a++;
			}

			while(y+b >= 0 && board[x][y+b] == 0) {
				v_move.push_back(id);
				v_move.push_back(b);
				b--;
			}
			
		} else {
			while(x+l-1+a < height && board[x+l-1+a][y] == 0) {
				v_move.push_back(id);
				v_move.push_back(a);
				a++;
			}

			while(x+b >= 0 && board[x+b][y] == 0) {
				v_move.push_back(id);
				v_move.push_back(b);
				b--;
			}
		}
	}

	return v_move;
}

void disp(int** board, int height) {
	std::cout << "===========" << std::endl;
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < height; ++j) {
			std::cout << board[j][i] << " ";
		}
		std::cout << std::endl;
	}

}

bool dejaVu(Board* board, int height, int nbv, std::unordered_map<std::string, Board*>& dejaVus) {
	// test si le board a deja ete vu
	// si non ajout dans la list des vus
	std::ostringstream oss;
	int x, y;
	// on construit un string qui correspond au board
	for (int id = 1; id <= nbv; ++id) {
		x = getFirstX(board->plat, id, height);
		y = getFirstY(board->plat, id, height);
		oss << x;
		oss << " ";
		oss << y;
		oss << " ";
		oss << getLenVoiture(board->plat, id, height, x, y);
		oss << " ";
		oss << getOrientationVoiture(board->plat, id, height, x, y);
		oss << " ";
	}
	std::string aTestString = oss.str();

	// on compare le string a tous les string contenu dans dejaVus
	if (dejaVus.find(aTestString) != dejaVus.end()) {
		return true;
	}

	// si le string est nouveau => on l'ajoute
	dejaVus[aTestString] = board;
	return false;
}

bool checkWin(int** board, int winx, int winy) {
	return board[winx][winy] == 1;	
}


std::vector<Move*> list_move_to_moves(std::vector<int> tab) {
	
	std::vector<Move*> resMoves;

	for(int i = 0; i < tab.size(); i+=2)
	{
		Move* tmp = new Move(tab[i],tab[i+1]);
		
		resMoves.push_back(tmp);
	}
	tab.clear();
	return resMoves;
}

// fonction similaire a celle dans Jeu.cpp 
// mais qui a ete adaptee a pour renvoyer uniquement le nombre de coup pour resoudre le board
int BFS(int** board, int height, int winx, int winy) {

	std::unordered_map<std::string, Board*> dejaVus;
    std::queue<Board*> BFSQueue;
    std::stack<Board*> resultBFS;
	std::vector<Board*> boards_results;
	std::vector<Move*> result;

    int nb_voiture = get_nb_voiture(board, height);

    Board* nboard = new Board(board, nullptr);

	BFSQueue.push(nboard);
	dejaVu(nboard, height, nb_voiture, dejaVus);

	while (!BFSQueue.empty()) {
		Board* curentboard = BFSQueue.front();
		BFSQueue.pop();

		result = list_move_to_moves(list_move(curentboard->plat, height, nb_voiture));
		
		for (int i = 0; i < result.size(); i++) {
			//creation du nouveau tableau temporaire
			int ** platTmp = new int*[height];
			for (int j = 0; j < height; j++)
				platTmp[j] = new int[height];

			Board* nboard = new Board(platTmp, curentboard);
			//initialisationBFS
			for (int j = 0; j < height; j++) {
				for (int k = 0; k < height; k++) {
					nboard->plat[j][k] = curentboard->plat[j][k];
				}
			}
			//gestion du avant arriere
			bool avancer = false;
			if (result[i]->nbMoves > 0) {
				avancer = true;
			} else {
				avancer = false;
				result[i]->nbMoves *= -1;
			}
			//applique le Move 
			for (int j = 0; j < result[i]->nbMoves; j++) {
				moveVoiture(nboard->plat, result[i]->carId, avancer, height);
			}
			boards_results.push_back(nboard);
		}
		result.clear();

		for (int i = 0; i < boards_results.size(); i++) {

			if (!dejaVu(boards_results[i], height, nb_voiture, dejaVus)) {
				BFSQueue.push(boards_results[i]);

				if (checkWin(boards_results[i]->plat, winx, winy)) {
					Board* ite = boards_results[i];
					while (ite->pred != nullptr) {
						resultBFS.push(ite);
						ite = ite->pred;
					}
					// std::cout << "================WIN===========: " << std::endl;
					int size = resultBFS.size();
					dejaVus.clear();
					result.clear();
					boards_results.clear();
					while(!resultBFS.empty()) {
						resultBFS.pop();
					}

					while(!BFSQueue.empty()) {
						BFSQueue.pop();
					}
					return size;
				}
			}
		}
		boards_results.clear();
	}

	boards_results.clear();
	dejaVus.clear();
	result.clear();
	while(!resultBFS.empty()) {
		resultBFS.pop();
	}

	while(!BFSQueue.empty()) {
		BFSQueue.pop();
	}
	return -1;
}

std::vector<int> list_pos(int** board, int height) {
	// return toutes les positions ou on peut mettre une voiture
	std::vector<int> v_pos;
	int a, b;
	for (int x = 0; x < height; x++) {
		for (int y = 0; y < height; y++) {

			a = 0;
			b = 0;

			while(y+a < height && board[x][y+a] == 0 && a < 4) {
				if (a > 1) {
					v_pos.push_back(1); // 1 = verti
					v_pos.push_back(a);
					v_pos.push_back(x);
					v_pos.push_back(y);
				}
				a++;
			}

			while(x+b < height && board[x+b][y] == 0 && b < 4) {
				if (b > 1) {
					v_pos.push_back(0); // 0 = hori
					v_pos.push_back(b);
					v_pos.push_back(x);
					v_pos.push_back(y);

				}
				b++;
			}
		}
	}
	return v_pos;
}

// fonction obsolete
void removeVoiture(int** board, int id, int height) {
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < height; ++j) {
			if(board[i][j] == id)
				board[i][j] = 0;
		}
	}
}

// fonction obsolete
void decalage(int** board, int height, int nb_voiture) { // change l'id de toutes les voitures pour que l'on ait bien des voitures numerotes de 1 a nb_voiture
	int remp = 0;
	for (int id = 1; id < nb_voiture; ++id) {
		if (getFirstX(board, id, height) == -1) {
			remp = id;
		}
	}

	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < height; ++j) {
			if(board[i][j] > remp)
				board[i][j] -= 1;
		}
	}
}

void Board_creator(int height, int width, int nb_board_voulues, int nb_coup_min) {
	// cree des boards qui sont affiches a la fin de la fonction
	// on pourrait evantuellement changer la fonction pour renvoyer

	srand((unsigned)time(0));

	std::vector<int> l_pos;
	int ri; // random integer
	bool ori;
	int l, x, y;
	bool remplis;

	int** c_board;
	int winx;
	int winy;
	bool faisable;
	int a;
	int c_id;
	int ** board;

	std::vector<Board*> boards_created; // les boards crees et a renvoyees
	while(nb_board_voulues > boards_created.size()) {
		// on cree aleatoirement un board en inserant un nombre de voiture
		// puis on regarde si il est resolvable en plus de
		// nb_coup_min, sinon on le delete

		board = new int*[width];
		for(int i = 0; i < width; ++i)
			board[i] = new int[height];
		
		for (int i = 0; i < width; ++i) {
			for (int j = 0; j < height; ++j) {
				board[i][j] = 0;
			}
		}

		Board* nboard = new Board(board, nullptr);
		addVoiture(nboard->plat, 1, 1, 2, 0, 0, false);
		remplis = false;

		for (int id = 2; id <= 13 && !remplis; ++id) { // preremplissage aleatoire du board pour accelerer l'arriver
			l_pos = list_pos(nboard->plat, height);            // un nombre de voiture a partir duquel on peut commencer
			if(l_pos.size() > 0) {
				ri = (rand() % (l_pos.size()) / 4);         // a avoir des board non finissables en 1 ou 2 coups
				ori = l_pos[ri*4]; l = l_pos[ri*4 +1]; x = l_pos[ri*4 +2]; y = l_pos[ri*4 +3];
				addVoiture(nboard->plat, id, ori, l, x, y, true);
			} else{
				remplis = true;

			}
		}

		// on retrouve la position sur laquelle deplacee la voiture 1
		winy = height -1; winx = height -1;
		int x = getFirstX(nboard->plat, 1, height);
		int y = getFirstY(nboard->plat, 1, height);

		ori = getOrientationVoiture(nboard->plat, 1, height, x, y);

		if(ori) { winx = x; }
		else    { winy = y; }

		x = getFirstX(nboard->plat, 1, height);
		y = getFirstY(nboard->plat, 1, height);


		c_board = nboard->plat;
		faisable = true;

		// on essaye de voir s'il y a une voiture en travers du chemin
		// en regardant si il y a 2 cases non vides consecutives qui ont le meme id
		a = 0; c_id = 0;

		if(ori) {
			while(y+a+l-1 < height) {
			    if(c_board[x][y+l+a-1] != 0) {
			    	if(c_board[x][y+a+l-1] == c_id) { faisable = false; }
			    	else { c_id = c_board[x][y+a+l-1]; }
				}
				a++;
			}
		} else {
			while(x+a+l-1 < height) {
			    if(c_board[x+a+l-1][y] != 0) {
			    	if(c_board[x+a+l-1][y] == c_id) { faisable = false; }
			    	else { c_id = c_board[x+a+l-1][y]; }
				}
				a++;
			}
		}

		int nb_coups = -1;
		if(faisable){ // on check en combien de coups est resolvable le board
			nb_coups = BFS(nboard->plat, height, winx, winy);
		}
		
		if(nb_coups >= nb_coup_min) { // on regarde si le board est assez complexe
			std::cout << "created: " << nb_coups << std::endl;
			boards_created.push_back(nboard);
		} else { // si il n'est pas assez complexe on le delete
			delete nboard;
		}
	}

	// affichage final des boards crees
	for (int i = 0; i < boards_created.size(); ++i) {
		disp(boards_created[i]->plat, height);
	}
}