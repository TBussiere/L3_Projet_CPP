#ifndef MOVE_HPP
#define MOVE_HPP

class Move {
    public :
		// id de la voiture
        int carId;
		// nombre de cases a avancer
        int nbMoves;
		// prio pour la liste de priorité (PAS encore UTILISE)  
		int prio;

		Move(int carId, int nbMoves);
};

#endif