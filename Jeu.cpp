#include "Jeu.hpp"
#include "Move.hpp"
#include "Board.hpp"
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>

Jeu::Jeu(const char* path) {
	//creation du tableau a 2 dimention temporaire
	int** plat = new int*[this->whidth];
	for (int i = 0; i < this->whidth; ++i)
		plat[i] = new int[this->height];
	//le remplir de 0 qui une case libre
	for (int i = 0; i < whidth; ++i) {
		for (int j = 0; j < height; ++j) {
			plat[i][j] = 0;
		}
	}
	//initialise le board
	this->board = new Board(plat, nullptr);
	//initialisation des tailles (fix)
	this->whidth = 6;
	this->height = 6;
	this->nbVoiture = 0;

	//Lecture du fichier map
	try
	{
		//le stream
		std::ifstream myfile;
		//on l'ouvre
		myfile.open(path);
		int a, b, c, d;
		//on lit la sorti
		myfile >> this->winx >> this->winy;
		int id = 1;
		//on le rempli avec le reste
		while (myfile >> a >> b >> c >> d)
		{
			std::cout << id << " | " << a << std::endl;
			bool verti = (d == 1);

			// board, id voiture, orientation true=>vertical, longueur, x, y
			this->addVoiture(board, id++, verti, c, a, b);
			this->nbVoiture++;
		}
		//fermeture du fichier
		myfile.close();

	}
	catch (const std::exception& e)
	{
		//si il ya un erreur on l'a print
		std::cerr << e.what() << '\n';
	}
}
//deleteur de la class jeu
Jeu::~Jeu() {
	delete board;
	//clear appele le destructeur
	this->dejaVus.clear();
	if (!BFSQueue.empty())
	{
		while (!BFSQueue.empty())
		{
			//pop appele le destructeur
			BFSQueue.pop();
		}
	}
	if (!resultBFS.empty())
	{
		while (!resultBFS.empty())
		{
			resultBFS.pop();
		}
	}
}

void Jeu::addVoiture(Board* board, int id, bool verti, int l, int x, int y) {
	// verti: est ce que la voiture est en vertical ou en horizontale
	// id: id de la voiture
	// l: longueur de la voiture
	// x, y: coordonnees de la premiere case de la voiture
	// la voiture remplira l cases a partir de [x][y] avec comme valeur id

	int a = 0;
	int b = 0;

	for (int i = 0; i < l; ++i) {
		this->board->plat[x + a][y + b] = id;
		if (verti) {
			b++;
		}
		else {
			a++;
		}
	}
}

bool Jeu::getOrientationVoiture(Board* board, int id) {
	// return true si la voiture est en vertical

	for (int i = 0; i < this->height; ++i) {
		for (int j = 0; j < this->whidth; ++j) {
			if (board->plat[i][j] == id) {
				if (j == 0) {
					return board->plat[i][j + 1] == id;
				}
				else if (j == this->whidth - 1) {
					return board->plat[i][j - 1] == id;
				}
				else {
					return board->plat[i][j + 1] == id || board->plat[i][j - 1] == id;
				}
			}
		}
	}
	return false;
}

int Jeu::getLenVoiture(Board* board, int id) {
	// return la longueur de la voiture
	bool orientation = this->getOrientationVoiture(board, id);

	for (int i = 0; i < this->whidth; ++i) {
		for (int j = 0; j < this->height; ++j) {
			if (board->plat[i][j] == id) {
				int a = 0;
				int b = 0;
				int len = 0;

				while (i + a < 6 && j + b < 6 && board->plat[i + a][j + b] == id) {
					len++;
					if (orientation) {
						b++;
					}
					else {
						a++;
					}
				}

				return len;
			}
		}
	}
	return -1;
}

int Jeu::getFirstX(Board* board, int id) {
	// return la coordonne x de la premiere case appartenant a la voiture

	for (int i = 0; i < 6; ++i) {
		for (int j = 0; j < 6; ++j) {
			if (board->plat[i][j] == id) {
				return i;
			}
		}
	}
	return -1;
}

int Jeu::getFirstY(Board* board, int id) {
	// return la coordonne y de la premiere case appartenant a la voiture

	for (int i = 0; i < 6; ++i) {
		for (int j = 0; j < 6; ++j) {
			if (board->plat[i][j] == id) {
				return j;
			}
		}
	}
	return -1;
}

int Jeu::moveVoiture(Board* board, int id, bool direction) {
	// id: id de la voiture a bouger
	// direction: direction du movement de la voiture
	// 			  le sens depend de l'orientation de la voiture 
	// 			  true  => vers le bas ou la droite
	// 			  false => vers la gauche ou le haut

	int l = getLenVoiture(board, id);
	int x, y;
	bool trouve = false;

	for (int i = 0; i < 6; ++i) {
		for (int j = 0; j < 6; ++j) {
			if (board->plat[i][j] == id && !trouve) {
				x = i;
				y = j;
				trouve = true;
			}
		}
	}

	if (getOrientationVoiture(board, id)) { // si vertical
		if (direction) { // vers le bas
			if (y + l < 6 && board->plat[x][y + l] == 0) {
				board->plat[x][y] = 0;
				board->plat[x][y + l] = id;
			}
		}
		else { // vers le haut
			if (y > 0 && board->plat[x][y - 1] == 0) {
				board->plat[x][y - 1] = id;
				board->plat[x][y + l - 1] = 0;
			}
		}
	}
	else { // si horizontal
		if (direction) { // vers la droite
			if (x + l < 6 && board->plat[x + l][y] == 0) {
				board->plat[x][y] = 0;
				board->plat[x + l][y] = id;
			}
		}
		else { // vers la gauche
			if (x > 0 && board->plat[x - 1][y] == 0) {
				board->plat[x - 1][y] = id;
				board->plat[x + l - 1][y] = 0;
			}
		}
	}

	return 0;
}

std::vector<int> Jeu::list_move(Board* board) {
	std::vector<int> v_move;
	for (int id = 1; id <= this->nbVoiture; id++) {
		int l = this->getLenVoiture(board, id);
		int x, y;
		bool trouve = false;


		for (int i = 0; i < 6; ++i) {
			for (int j = 0; j < 6; ++j) {
				if (board->plat[i][j] == id && !trouve) {
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
			while (y + l - 1 + a < 6 && board->plat[x][y + l - 1 + a] == 0) {
				v_move.push_back(id);
				v_move.push_back(a);
				a++;
			}

			while (y + b >= 0 && board->plat[x][y + b] == 0) {
				v_move.push_back(id);
				v_move.push_back(b);
				b--;
			}

		}
		else {
			while (x + l - 1 + a < 6 && board->plat[x + l - 1 + a][y] == 0) {
				v_move.push_back(id);
				v_move.push_back(a);
				a++;
			}

			while (x + b >= 0 && board->plat[x + b][y] == 0) {
				v_move.push_back(id);
				v_move.push_back(b);
				b--;
			}
		}
	}

	return v_move;
}

void Jeu::disp(Board* board) {
	std::cout << "===========" << std::endl;
	for (int i = 0; i < whidth; ++i) {
		for (int j = 0; j < height; ++j) {
			std::cout << board->plat[j][i] << " ";
		}
		std::cout << std::endl;
	}
}

void Jeu::dispResult() {
	std::stack<Board*> copyResultBFS = this->resultBFS;

	while (!copyResultBFS.empty()) {
		this->disp(copyResultBFS.top());
		copyResultBFS.pop();
	}
}

bool Jeu::BFS(Board* board) {

	this->BFSQueue.push(board);
	this->dejaVu(board);

	while (!this->BFSQueue.empty())
	{
		Board* curentboard = this->BFSQueue.front();
		this->BFSQueue.pop();


		std::vector<Move*> result = this->list_move_to_moves(this->list_move(curentboard));
		std::vector<Board*> boards_results;
		for (int i = 0; i < result.size(); i++)
		{
			//creation du nouveau tableau temporaire
			int ** platTmp = new int*[this->whidth];
			for (int j = 0; j < this->whidth; j++)
				platTmp[j] = new int[this->height];

			Board* nboard = new Board(platTmp,curentboard);
			//initialisation
			for (int j = 0; j < this->whidth; j++)
			{
				for (int k = 0; k < this->height; k++)
				{
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
				this->moveVoiture(nboard, result[i]->carId, avancer);
			}
			boards_results.push_back(nboard);
		}

		for (int i = 0; i < boards_results.size(); i++)
		{
			if (!this->dejaVu(boards_results[i])) {
				this->BFSQueue.push(boards_results[i]);
				//system("pause");
				if (this->checkWin(boards_results[i])) {
					std::cout << "================WIN===========: " << std::endl;
					Board* ite = boards_results[i];
					while (ite->pred != nullptr)
					{
						this->resultBFS.push(ite);
						ite = ite->pred;
					}
					return true;
				}
			}
		}
	}
	return false;
}

bool Jeu::dejaVu(Board* board) {
	// test si le board a deja ete vu
	// si non ajout dans la list des vus
	int nbv = this->nbVoiture;


	std::ostringstream oss;

	// on construit un string qui correspond au board
	for (int id = 1; id <= nbv; ++id) {
		oss << this->getFirstX(board, id);
		oss << " ";
		oss << this->getFirstY(board, id);
		oss << " ";
		oss << this->getLenVoiture(board, id);
		oss << " ";
		oss << this->getOrientationVoiture(board, id);
		oss << " ";
	}
	std::string aTestString = oss.str();
	oss.clear();
	// on compare le string a tous les string contenu dans dejaVus
	if (this->dejaVus.find(aTestString) != this->dejaVus.end()){
		return true;
	}

	// si le string est nouveau => on l'ajoute
	//this->dejaVus.push_back(aTestString);
	this->dejaVus[aTestString] = board;
	return false;
}


bool Jeu::checkWin(Board* board) {
	return board->plat[this->winx][this->winy] == 1;
}

std::vector<Move*> Jeu::list_move_to_moves(std::vector<int> tab) {
	std::vector<Move*> resMoves;

	for (int i = 0; i < tab.size(); i += 2)
	{
		Move* tmp = new Move(tab[i], tab[i + 1]);

		resMoves.push_back(tmp);
	}
	return resMoves;
}