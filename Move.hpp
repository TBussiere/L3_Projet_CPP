#ifndef MOVE_HPP
#define MOVE_HPP

class Move {
    public :
        int carId;
        int nbMoves;
		int prio;

		Move(int carId, int nbMoves);
};

#endif