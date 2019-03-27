#ifndef JEU_HPP
#define JEU_HPP
#include <string>
#include <vector>

class Jeu {
    public :
        int** board;
        int whidth = 6;
    	int height = 6;
        int winx = 2;
        int winy = 1;
        int nbVoiture;
        std::vector<std::string> dejaVus;


	    Jeu(char* path);
        void addVoiture(int** board, int id, bool verti, int l, int x, int y);
        bool getOrientationVoiture(int** board, int id);
        int getLenVoiture(int** board, int id);
        int getFirstX(int** board, int id);
        int getFirstY(int** board, int id);
        int moveVoiture(int** board, int id, bool direction);
        std::vector<int> list_move(int** board);
        bool dejaVu(int** board);
        void ajoutVu(int** board);
        bool checkWin(int** board);

        bool BFS(int** board);

        void disp(int** board);


};
#endif // !JEU_HPP