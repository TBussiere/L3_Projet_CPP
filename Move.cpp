#include "Move.hpp"
#include <iostream>

Move::Move(int id,int taille){
    this->carId = id;
    this->nbMoves = taille;
	//tentative d'heuristique
	if (id == 1)
	{
		prio = 1;
	}
	else
	{
		prio = 0;
	}
}
