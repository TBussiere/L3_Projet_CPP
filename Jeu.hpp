#ifndef JEU_HPP
#define JEU_HPP
#include <string>

class Board;
class Jeu {
    public :
        Board* board;
	    Jeu(std::string path);
};
#endif // !JEU_HPP