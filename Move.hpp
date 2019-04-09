#ifndef MOVE_HPP
#define MOVE_HPP

class Move {
    public :
        int carId;
        int nbMoves;
        Move* pred;

        Move(int carId, int nbMoves, Move* pred);
};

#endif