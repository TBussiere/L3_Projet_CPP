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

// class Boar_creator {
//     public :
//         int** board_creation(int height, int width);


// };

bool DFS(int** board, int height, int winx, int winy, std::unordered_map<std::string, Board*> dejaVus);
bool addVoiture(int** board, int id, bool verti, int l, int x, int y, bool verif);
bool getOrientationVoiture(int** board, int id, int height);
int getLenVoiture(int** board, int id, int height);
int getFirstX(int** board, int id, int height);
int getFirstY(int** board, int id, int height);
int moveVoiture(int** board, int id, bool direction, int height);
int get_nb_voiture(int** board, int height);
std::vector<int> list_move(int** board, int height, int nbVoiture);
void disp(int** board, int height);
bool dejaVu(int** board, int height, int nbv, std::vector<std::string> dejaVus);
bool checkWin(int** board, int winx, int winy);
int BFS(int** board, int height, int winx, int winy);
std::vector<int> list_pos(int** board, int height);
void save_to_txt(int** board, int height);
void Board_creator(int height, int width, int nb_coup_min, int nb_board_voulues);

#endif