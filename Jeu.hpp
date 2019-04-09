#ifndef JEU_HPP
#define JEU_HPP
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include "Move.hpp"

class Jeu {
    public :
        int** board;
        int whidth = 6;
    	int height = 6;
        int winx = 5;
        int winy = 2;
        int nbVoiture;
        std::unordered_map<std::string,int**> dejaVus;
        std::queue<int**> BFSQueue;


	    Jeu(char* path);
        void addVoiture(int** board, int id, bool verti, int l, int x, int y);
        bool getOrientationVoiture(int** board, int id);
        int getLenVoiture(int** board, int id);
        int getFirstX(int** board, int id);
        int getFirstY(int** board, int id);
        int moveVoiture(int** board, int id, bool direction);
        std::vector<int> list_move(int** board);
        std::vector<Move*> list_move_to_moves(std::vector<int> list);
        bool dejaVu(int** board);
        bool checkWin(int** board);

        bool BFS(int** board);

        void disp(int** board);


};
#endif // !JEU_HPP