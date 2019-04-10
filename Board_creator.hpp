#ifndef BOARD_CREATOR
#define BOARD_CREATOR
#include <string>
#include <vector>
#include <queue>
#include "Move.hpp"
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
#include "Board.hpp"

// beaucoup des fonctions dans ce fichier sont tres similaires a celles dans la classe Jeu
// elles ont ete adaptees a la creation de board
// deplus par manque de temps je n'ai pas pu les merge avec celles de Jeu 

bool DFS(int** board, int height, int winx, int winy, std::unordered_map<std::string, Board*> dejaVus);
bool addVoiture(int** board, int id, bool verti, int l, int x, int y, bool verif);
bool getOrientationVoiture(int** board, int id, int height);
int getLenVoiture(int** board, int id, int height);
int getFirstX(int** board, int id, int height);
int getFirstY(int** board, int id, int height);

// id: id de la voiture a bouger
// direction: direction du movement de la voiture
// 			  le sens depend de l'orientation de la voiture 
// 			  true  => vers le bas ou la droite
// 			  false => vers la gauche ou le haut
int moveVoiture(int** board, int id, bool direction, int height);

// le nombre de voiture est egale au plus grand id des voitures
int get_nb_voiture(int** board, int height);


std::vector<int> list_move(int** board, int height, int nbVoiture);

// affiche le tableau
void disp(int** board, int height);

// test si le board a deja ete vu,  sinon ajout dans la list des vus
bool dejaVu(int** board, int height, int nbv, std::vector<std::string> dejaVus);
bool checkWin(int** board, int winx, int winy);
int BFS(int** board, int height, int winx, int winy);
std::vector<int> list_pos(int** board, int height);
void save_to_txt(int** board, int height);
void Board_creator(int height, int width, int nb_coup_min, int nb_board_voulues);

// return toutes les positions ou on peut mettre une voiture
std::vector<int> list_pos(int** board, int height);


#endif