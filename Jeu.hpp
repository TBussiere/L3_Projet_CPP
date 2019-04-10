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
        //pointeur du board principale
		Board* board;
        //valeur pas defaut pour les taille et la case de win
        int whidth = 6;
    	int height = 6;
        int winx = 5;
        int winy = 2;
        int nbVoiture;
        //Hash map des positions deja exploré
        std::unordered_map<std::string, Board*> dejaVus;
        //Queue pour le bon fonctionemant du BFS
		std::queue<Board*> BFSQueue;
        //pile pour le resulta du bfs
		std::stack<Board*> resultBFS;


	    Jeu(const char* path);
		~Jeu();
        //ajoute une voiture en (x,y) de longeur l vertical ou pas
        void addVoiture(Board* board, int id, bool verti, int l, int x, int y);
        //avoir l'oriantation de la voiture id
        bool getOrientationVoiture(Board* board, int id);
        //avoir la longeur de la voiture id
        int getLenVoiture(Board* board, int id);
        //avoir le premier X de la voiture id        
        int getFirstX(Board* board, int id);        
        //avoir le premier Y de la voiture id        
        int getFirstY(Board* board, int id);
        //deplace la voiture id        
        int moveVoiture(Board* board, int id, bool direction);
        //renvoi la liste des move posible pour un certain board
        std::vector<int> list_move(Board* board);
        //converti le vector de int de la fonction list_move en vector de Move
        std::vector<Move*> list_move_to_moves(std::vector<int> list);
        //revoi si le board a deja ete vu sinon l'ajoute dans la hash map
        bool dejaVu(Board* board);
        //ANCIEN plus utiliser nous permetai d'ajouter le board a la hash map
        void ajoutVu(Board* board);
        // renvoi si le board est une position gagnante
        bool checkWin(Board* board);

        //lance le Parcour en largeur
        bool BFS(Board* board);

        //affiche le board
		void disp(Board* board);
        //affiche tous les elements de la pile resultBFS
		void dispResult();

};
#endif // !JEU_HPP