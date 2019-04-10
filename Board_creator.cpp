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


bool addVoiture(int** board, int id, bool verti, int l, int x, int y, bool verif) {
	// verti: est ce que la voiture est en vertical ou en horizontale
	// id: id de la voiture
	// l: longueur de la voiture
	// x, y: coordonnees de la premiere case de la voiture
	// la voiture remplira les cases a partir de [x][y] avec comme valeur id si il n'y a pas deja de voiture
	// renvoie si la voiture a ete place
	// verif: si on verifie

	int a = 0;
	int b = 0;

	if(verif) {
		for (int i = 0; i < l; ++i) { // on parcourt une premiere fois pour verifier qu'il n'y a pas deja de voitures a cet emplacement
			if(board[x+a][y+b] !=0) {
				std::cout << "deja pris!!!!!!!!!!!!" << std::endl;
				return false;
			}
			// std::cout << x+a << "/" << y+b << std::endl;

			if(verti) {
				b++;
			} else {
				a++;
			}
		}
	}

	a = 0;
	b = 0;

	for (int i = 0; i < l; ++i) {
		board[x+a][y+b] = id;
		// std::cout << x+a << "/" << y+b << std::endl;

		if(verti) {
			b++;
		} else {
			a++;
		}
	}

	return true;
}

bool getOrientationVoiture(int** board, int id, int height) {
	// return true si la voiture est en vertical

	for (int i = 0; i < height; ++i) {
		for (int j = 0;  j < height; ++j) {
			if (board[i][j] == id) {
				if(j == 0) {
					return board[i][j+1] == id;
				} else if(j == height -1) {
					return board[i][j-1] == id;
				} else {
					return board[i][j+1] == id || board[i][j-1] == id;
				}
			}
		}
	}
	return false;
}

int getLenVoiture(int** board, int id, int height) {
	// return la longueur de la voiture
	bool orientation = getOrientationVoiture(board, id, height);

	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < height; ++j) {
			if (board[i][j] == id) {
				int a = 0;
				int b = 0;
				int len = 0;

				while(i+a < height && j+b < height && board[i+a][j+b] == id) {
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

	// int x = getFirstX(board, id);
	// int y = getFirstY(board, id);
	int l = getLenVoiture(board, id, height);
	int x, y;
	bool trouve = false;

	// todo
	// a optimiser pour eviter de chercher plusieurs fois les pos des voitures
	// lors de la recherche de la longueur de la voiture, etc.
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < height; ++j) {
				// std::cout << i << " ||| " << j << std::endl;
			if (board[i][j] == id && !trouve) {
				x = i;
				y = j;
				trouve = true;
			}
		}
	}
	// disp(board, height);
	// std::cout << "x: " << x << " / " << l << std::endl;
	if (getOrientationVoiture(board, id, height)) { // si vertical
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
	// TODO: a deplace : int nb_voiture = get_nb_voiture(board, height);
	for (int id = 1; id <= nbVoiture; id++) {

		int l = getLenVoiture(board, id, height);
		int x, y;
		bool trouve = false;

		// todo
		// a optimiser pour eviter de chercher plusieurs fois les pos des voitures
		// lors de la recherche de la longueur de la voiture, etc.

		for (int i = 0; i < height; ++i) {
			for (int j = 0; j < height; ++j) {
				if (board[i][j] == id && !trouve) {
					x = i;
					y = j;
					trouve = true;
				}
			}
		}

		int a = 1;
		int b = -1;
		bool ori = getOrientationVoiture(board, id, height);

		if (ori) {
			// std::cout << x << "/" << y << "/" << l << std::endl;
			while(y+l-1+a < height && board[x][y+l-1+a] == 0) {
				// std::cout << "cout possible + : " << id << "/" << a << std::endl;
				v_move.push_back(id);
				v_move.push_back(a);
				a++;
			}

			while(y+b >= 0 && board[x][y+b] == 0) {
				// std::cout << "cout possible - : " << id << "/" << b << std::endl;
				v_move.push_back(id);
				v_move.push_back(b);
				b--;
			}
			
		} else {
				// std::cout << "id: " << id << std::endl;
			// std::cout << x << " | " << l << " | " << a << " | " << x+l-1+a << " / " << board[x+l-1+a][y] << std::endl;
			while(x+l-1+a < height && board[x+l-1+a][y] == 0) {
				// std::cout << "cout possible + : " << id << "/" << a << " | " << 9 << std::elist_move_to_movesndl;
				v_move.push_back(id);
				v_move.push_back(a);
				a++;
			}

			// std::cout << "	check: " << id << std::endl;
			// std::cout << "test - : " << id << "/" << b << " | " << x-1+b << std::endl;
			while(x+b >= 0 && board[x+b][y] == 0) {
				// std::cout << "cout possible - : " << id << "/" << b << std::endl;
				v_move.push_back(id);
				v_move.push_back(b);
				b--;
			}
		}
		// if (id == 5) {
		// 	std::cout << "v_move: " << v_move.size() << std::endl;
		// }
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
	// disp(board->plat, height);

	// on construit un string qui correspond au board
	for (int id = 1; id <= nbv; ++id) {
		oss << getFirstX(board->plat, id, height);
		oss << " ";
		oss << getFirstY(board->plat, id, height);
		oss << " ";
		oss << getLenVoiture(board->plat, id, height);
		oss << " ";
		oss << getOrientationVoiture(board->plat, id, height);
		oss << " ";
	}
	std::string aTestString = oss.str();

	// on compare le string a tous les string contenu dans dejaVus
	if (dejaVus.find(aTestString) != dejaVus.end()) {
		// std::cout << "	test: " << oss.str() << std::endl;
		return true;
	}

	// si le string est nouveau => on l'ajoute
	//this->dejaVus.push_back(aTestString);
	dejaVus[aTestString] = board;
	return false;
}

bool checkWin(int** board, int winx, int winy) {
	return board[winx][winy] == 1;	
}

std::vector<Move*> list_move_to_moves(std::vector<int> tab) {
	// TODO: compresser cette fonction avec list_move
	
	std::vector<Move*> resMoves;

	for(int i = 0; i < tab.size(); i+=2)
	{
		Move* tmp = new Move(tab[i],tab[i+1]);
		
		resMoves.push_back(tmp);
	}
	tab.clear();
	return resMoves;
}

int BFS(int** board, int height, int winx, int winy) {

	std::unordered_map<std::string, Board*> dejaVus;
    std::queue<Board*> BFSQueue;
    std::stack<Board*> resultBFS;
	std::vector<Board*> boards_results;
	std::vector<Board*> next_boards_results;
	std::vector<Move*> next_result;
	std::vector<Move*> result;

    int nb_voiture = get_nb_voiture(board, height);

    Board* nboard = new Board(board, nullptr);

	BFSQueue.push(nboard);
	dejaVu(nboard, height, nb_voiture, dejaVus);

	while (!BFSQueue.empty()) {
		Board* curentboard = BFSQueue.front();
		BFSQueue.pop();

		next_result = list_move_to_moves(list_move(curentboard->plat, height, nb_voiture));
		result.swap(next_result);
		// std::cout << "size: " << result.size() << std::endl;
		
		for (int i = 0; i < result.size(); i++) {
			//creation du nouveau tableau temporaire
			int ** platTmp = new int*[height];
			for (int j = 0; j < height; j++)
				platTmp[j] = new int[height];

			Board* nboard = new Board(platTmp, curentboard);
			//initialisation
			for (int j = 0; j < height; j++) {
				for (int k = 0; k < height; k++) {
					nboard->plat[j][k] = curentboard->plat[j][k];
				}
			}
			//gestion du avant arriere
			bool avancer = false;
			if (result[i]->nbMoves > 0) {
				avancer = true;
			}
			else
			{
				avancer = false;
				result[i]->nbMoves *= -1;
			}
			//applique le Move 
			for (int j = 0; j < result[i]->nbMoves; j++)
			{
				moveVoiture(nboard->plat, result[i]->carId, avancer, height);
			}
			next_boards_results.push_back(nboard);
		}
		boards_results.swap(next_boards_results);
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
					// this->disp(boards_results[i]);
					dejaVus.clear();
					return resultBFS.size();
				}
			}
		}
		boards_results.clear();
	}
	dejaVus.clear();
	return -1;
}

std::vector<int> list_pos(int** board, int height) {
	// std::cout << "debut" << std::endl;
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

void removeVoiture(int** board, int id, int height) {
	// std::cout << "	: " << result_moves.size() << std::endl;
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < height; ++j) {
			if(board[i][j] == id)
				board[i][j] = 0;
		}
	}
}

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

	std::unordered_map<std::string, Board*> dejaVus; // contient les board deja parcourus
    std::queue<Board*> queue;

	srand((unsigned)time(0));

	std::vector<int> l_pos;
	int ri; // random integer
	bool ori;
	int l, x, y;
	bool remplis;
	for (int p = 1; p < 50; ++p) {
		int ** board = new int*[width];
		for(int i = 0; i < width; ++i)
			board[i] = new int[height];
		
		for (int i = 0; i < width; ++i) {
			for (int j = 0; j < height; ++j) {
				board[i][j] = 0;
			}
		}

		Board* nboard = new Board(board, nullptr);
		addVoiture(board, 1, 1, 3, 0, 0, false);

		for (int id = 2; id <= nb_coup_min && !remplis; ++id) { // preremplissage aleatoire du board pour accelerer l'arriver
			l_pos = list_pos(board, height);            // un nombre de voiture a partir duquel on peut commencer
			if(l_pos.size() > 0) {
				ri = (rand() % (l_pos.size()) / 4);         // a avoir des board non finissables en 1 ou 2 coups
				ori = l_pos[ri*4]; l = l_pos[ri*4 +1]; x = l_pos[ri*4 +2]; y = l_pos[ri*4 +3];
				addVoiture(board, id, ori, l, x, y, false);
			} else
				remplis = true;

		}

		queue.push(nboard);
		dejaVu(nboard, height, 0, dejaVus);
	}

	std::cout << "	phase 2: " << std::endl;
	std::vector<Board*> boards_created; // les boards crees et a renvoyer
	std::vector<Board*> boards_results; // les boards checker la difficulte
	std::vector<int> result_pos;
	std::vector<Move*> result_moves;
    
	bool trouve = false; // si on a finis de creer des board

	while(!queue.empty() && !trouve && nb_board_voulues > boards_created.size()) {
	    Board* curentboard = queue.front();
		queue.pop();
		// disp(curentboard->plat, height);
		
		int nb_voiture = get_nb_voiture(curentboard->plat, height);
		result_pos = list_pos(curentboard->plat, height);
		std::vector<Move*> result_moves = list_move_to_moves(list_move(curentboard->plat, height, nb_voiture));

		// std::cout << "	result_moves: " << result_moves.size() << std::endl;
		for (int i = 0; i < result_moves.size(); i++) {
			// std::cout << i << std::endl;
			//creation du nouveau tableau temporaire
			int ** platTmp = new int*[height];
			for (int j = 0; j < height; j++)
				platTmp[j] = new int[height];

			Board* nboard = new Board(platTmp, nullptr);

			//initialisation
			for (int j = 0; j < height; j++) {
				for (int k = 0; k < height; k++) {
					nboard->plat[j][k] = curentboard->plat[j][k];
				}
			}

			//gestion du avant arriere
			bool avancer = false;
			if (result_moves[i]->nbMoves > 0)
				avancer = true;
			else {
				avancer = false;
				result_moves[i]->nbMoves *= -1;
			}

			//applique le Move 
			for (int j = 0; j < result_moves[i]->nbMoves; j++) {
				moveVoiture(nboard->plat, result_moves[i]->carId, avancer, height);
			}	
			boards_results.push_back(nboard);
		}
		result_moves.clear();

		// std::cout << "	add: " << result_pos.size() << std::endl;
		for (int i = 0; i+5 < result_pos.size(); i+=4) {
			//creation du nouveau tableau temporaire
			int ** platTmp = new int*[height];
			for (int j = 0; j < height; j++)
				platTmp[j] = new int[height];

			// std::cout << "	check interne: " << platTmp == 0 << std::endl;
			Board* nboard = new Board(platTmp, nullptr);

			//initialisation
			for (int j = 0; j < height; j++) {
				for (int k = 0; k < height; k++) {
					nboard->plat[j][k] = curentboard->plat[j][k];
				}
			}

			ori = result_pos[i];
			l = result_pos[i +1];
			x = result_pos[i +2];
			y = result_pos[i +3];
			// std::cout << "	ori: " << ori << " | l: " << l << " | x: " << x << " | y: " << y << std::endl;

			addVoiture(nboard->plat, nb_voiture+1, ori, l, x, y, false); // TODO : a enlever quand je serais sur que ca marche
				boards_results.push_back(nboard);
		}
		result_pos.clear();

		// std::cout << "	remove: " << nb_voiture << std::endl;
		for (int id = 1; false && id <= nb_voiture; id++) {
			//creation du nouveau tableau temporaire
			int ** platTmp = new int*[height];
			for (int j = 0; j < height; j++)
				platTmp[j] = new int[height];

			Board* nboard = new Board(platTmp, nullptr);

			//initialisation
			for (int j = 0; j < height; j++) {
				for (int k = 0; k < height; k++) {
					nboard->plat[j][k] = curentboard->plat[j][k];
				}
			}
			decalage(nboard->plat, height, nb_voiture);
			removeVoiture(nboard->plat, id, height);
			boards_results.push_back(nboard);
		}

		for (int i = 0; !trouve && i < boards_results.size(); i++) {

			int nbVoiture = get_nb_voiture(boards_results[i]->plat, height);
			if (!dejaVu(boards_results[i], height, nbVoiture, dejaVus)) {
				// std::cout << "	check interne: " << dejaVus.size() << std::endl;

				int winy = height -1; int winx = height -1;
				int ori = getOrientationVoiture(boards_results[i]->plat, 1, height);

				if(ori) { winx = getFirstX(boards_results[i]->plat, 1, height); }
				else    { winy = getFirstY(boards_results[i]->plat, 1, height); }

				x = getFirstX(boards_results[i]->plat, 1, height);
				y = getFirstY(boards_results[i]->plat, 1, height);
				int** c_board = boards_results[i]->plat;
				bool faisable = true;

					// disp(boards_results[i]->plat, height);
				// on essaye de voir s'il y a une voiture en travers du chemin
				if(ori) {
					int a = 0;
					int c_id = 0;
					while(y+a+l < height) {
					    if(c_board[x][y+l+a] != 0) {
					    	if(c_board[x][y+a] == c_id) {
					    		faisable = false;

					    	}
					    	else
								c_id = c_board[x][y+a+l];

						}
						a++;
					}
				} else {
					int a = 0;
					int c_id = 0;
					while(x+a+l < height) {
					    if(c_board[x+a+l][y] != 0) {
					    	if(c_board[x+a+l][y] == c_id) {
					    		faisable = false;
					    	}
					    	else
								c_id = c_board[x+a+l][y];

						}
						a++;
					}
				}

				int nb = -1;
				if(faisable)
					nb = BFS(boards_results[i]->plat, height, winx, winy);
				
				if(nb != -1)
					queue.push(boards_results[i]);
				// std::cout << "	: " << nb << std::endl;
				// disp(boards_results[i]->plat, height);
				
				if(nb >= nb_coup_min) {
					std::cout << "created: " << nb << std::endl;
					// disp(boards_results[i]->plat, height);
					boards_created.push_back(boards_results[i]);
					if(boards_created.size() > nb_board_voulues)
						trouve = true;
				}
			}
		}

		if(queue.size() > 100) { // on reduit la taille de la queue en jetant des boards qui sont surement inutiles
			for (int i = 0; i < queue.size() / 10; ++i) {
				queue.pop();
			}
		}
	}

	for (int i = 0; i < boards_created.size(); ++i) {
		disp(boards_created[i]->plat, height);
	}
}