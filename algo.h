#ifndef ALGO_H_INCLUDED
#define ALGO_H_INCLUDED

#include "chessboard.h"

using namespace sf;

//Handles the ai for computer generated move
class Computer {
    public:
        int Evaluate(chessboard&); //Evaluated the board
        Vector2i* minimax(int, chessboard&,int); //Start the minimax algorithm
        int minSearch(int, chessboard&,int,int); //Tries to minimize the board value i.e tries to favour player 1
        int maxSearch(int, chessboard&,int,int); //Tries to maximize the board value i.e tries to favour player 2
};

#endif // ALGO_H_INCLUDED
