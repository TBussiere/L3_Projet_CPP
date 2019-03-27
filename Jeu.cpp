#include "Jeu.hpp"
#include "Board.hpp"
#include <string>


Jeu::Jeu(std::string path){
	this->board = new Board(path);
}