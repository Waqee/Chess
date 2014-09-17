#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

#include "gamestates.h"

//Making a header file for the global variables so they can be accessed easily

extern int INFINITY;

extern GameStates stateID;
extern GameStates nextState;
extern GameState *tempstate;
extern GameState *currentState;

extern void set_next_state( GameStates );

extern void change_state(sf::RenderWindow &);

extern int pawn[8][8];
extern int rook[8][8];
extern int bishop[8][8];
extern int knight[8][8];
extern int queen[8][8];
extern int king[8][8];

#endif // GLOBAL_H_INCLUDED
