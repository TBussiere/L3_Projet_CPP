#ifndef JEU_HPP
#define JEU_HPP
#include <string>
#include <vector>

class Board;
class Jeu {
    public :
        int** board;
        int whidth = 6;
    	int height = 6;

	    Jeu(std::string path);
        void addVoiture(int** board, int id, bool verti, int l, int x, int y);
        bool getOrientationVoiture(int** board, int id);
        int getLenVoiture(int** board, int id);
        int getFirstX(int** board, int id);
        int getFirstY(int** board, int id);
        int moveVoiture(int** board, int id, bool direction);
        std::vector<int> list_move(int** board, int nbVoiture);

        void disp(int** board);


};
#endif // !JEU_HPP