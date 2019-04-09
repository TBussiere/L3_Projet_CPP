#ifndef JEU_HPP
#define JEU_HPP
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_map>
#include "Move.hpp"
#include "Board.hpp"

class Jeu {
    public :
		Board* board;
        int whidth = 6;
    	int height = 6;
        int winx = 5;
        int winy = 2;
        int nbVoiture;
        std::unordered_map<std::string, Board*> dejaVus;
		std::queue<Board*> BFSQueue;
		std::stack<Board*> resultBFS;


	    Jeu(const char* path);
        void addVoiture(Board* board, int id, bool verti, int l, int x, int y);
        bool getOrientationVoiture(Board* board, int id);
        int getLenVoiture(Board* board, int id);
        int getFirstX(Board* board, int id);
        int getFirstY(Board* board, int id);
        int moveVoiture(Board* board, int id, bool direction);
        std::vector<int> list_move(Board* board);
        std::vector<Move*> list_move_to_moves(std::vector<int> list);
        bool dejaVu(Board* board);
        void ajoutVu(Board* board);
        bool checkWin(Board* board);

        bool BFS(Board* board);

		void disp(Board* board);
		void dispResult();


};
#endif // !JEU_HPP