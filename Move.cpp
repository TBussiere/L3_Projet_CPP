#include "Move.hpp"
#include <iostream>

Move::Move(int id,int taille,Move* pres){
    this->carId = id;
    this->nbMoves = taille;
    this->pred = pres;
}