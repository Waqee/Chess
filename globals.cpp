#include "global.h"

using namespace sf;

class GameState; //Declaration of game state class

int INFINITY = 10000;

TcpSocket GameState::socket;
GameStates stateID = STATE_NULL;  //An enum type variable that contain the id of current state
GameStates nextState = STATE_NULL;  //Another enum type variable that contains id of next state
GameState *tempstate = NULL;  //A temporary game state pointer used when promotion is done because we have to return to previous game state after promoting
GameState *currentState = NULL;  //The current game state stored in this variable

//Sets the enum variable next state if it is not equal to exit
void set_next_state( GameStates newState )
{
    if( nextState != STATE_EXIT )
        nextState = newState;
}

void change_state(RenderWindow &window)
{
    //Changes the state of game according to the value of next state variable
    if( nextState != STATE_NULL ) //Checks if there is something in next state
    {
        int player;
        player=currentState->player; //Stores the value of player for last state, this is used during promotion
        if( nextState != STATE_EXIT && nextState != STATE_PROMOTION ) //Deletes the cirrent state unless next state is exxit or promotio
            delete currentState;


        //changes the game state variable according to value stored in next state
        switch( nextState )
        {
            case STATE_TITLE:
            currentState = new Title(window);
            break;

            case STATE_SINGLE:
            currentState = new Single(window);
            break;

            //
            case STATE_COMPUTER:
            //If next state is actually a game mode, we first check if there is something stored in temp state other wise we create a new game.
            if (tempstate == NULL)
                currentState = new AI(window);
            else
			{
                currentState = tempstate;
				tempstate=NULL;
			}
            break;

            case STATE_GAME:
            if (tempstate == NULL)
                currentState = new Game(window);
             else
			{
                currentState = tempstate;
				tempstate=NULL;
			}
			break;

            case STATE_PROMOTION:
            tempstate=currentState;
            currentState = new Promotion(window);
            currentState->turn = tempstate->turn;
            break;

            case STATE_MULTI_TITLE1:
            currentState = new Multi1(window);
            break;

            case STATE_MULTI_TITLE2:
            currentState = new Multi2(window,player);
            break;

            case STATE_MULTIPLAYER:
            if (tempstate == NULL)
                currentState = new Multiplayer(window,player);
             else
			{
                currentState = tempstate;
				tempstate=NULL;
			}
			break;
            case STATE_COMVCOM:
            currentState = new comvcom(window);
            break;

        }
        stateID = nextState;
        nextState = STATE_NULL;
    }
}


//Piece tables used by chess ai to search for better positions

int pawn [8][8] = {  0,  0,  0,  0,  0,  0,  0,  0,
                    50, 50, 50, 50, 50, 50, 50, 50,
                    10, 10, 20, 30, 30, 20, 10, 10,
                     5,  5, 10, 25, 25, 10,  5,  5,
                     0,  0,  0, 20, 20,  0,  0,  0,
                     5, -5,-10,  0,  0,-10, -5,  5,
                     5, 10, 10,-20,-20, 10, 10,  5,
                     0,  0,  0,  0,  0,  0,  0,  0 };

int knight [8][8] = {   -50,-40,-30,-30,-30,-30,-40,-50,
                        -40,-20,  0,  0,  0,  0,-20,-40,
                        -30,  0, 10, 15, 15, 10,  0,-30,
                        -30,  5, 15, 20, 20, 15,  5,-30,
                        -30,  0, 15, 20, 20, 15,  0,-30,
                        -30,  5, 10, 15, 15, 10,  5,-30,
                        -40,-20,  0,  5,  5,  0,-20,-40,
                        -50,-40,-30,-30,-30,-30,-40,-50 };

int rook [8][8] = {   0,  0,  0,  0,  0,  0,  0,  0,
                      5, 10, 10, 10, 10, 10, 10,  5,
                     -5,  0,  0,  0,  0,  0,  0, -5,
                     -5,  0,  0,  0,  0,  0,  0, -5,
                     -5,  0,  0,  0,  0,  0,  0, -5,
                     -5,  0,  0,  0,  0,  0,  0, -5,
                     -5,  0,  0,  0,  0,  0,  0, -5,
                      0,  0,  0,  5,  5,  0,  0,  0 };

int bishop [8][8] = {-20,-10,-10,-10,-10,-10,-10,-20,
                    -10,  0,  0,  0,  0,  0,  0,-10,
                    -10,  0,  5, 10, 10,  5,  0,-10,
                    -10,  5,  5, 10, 10,  5,  5,-10,
                    -10,  0, 10, 10, 10, 10,  0,-10,
                    -10, 10, 10, 10, 10, 10, 10,-10,
                    -10,  5,  0,  0,  0,  0,  5,-10,
                    -20,-10,-10,-10,-10,-10,-10,-20 };

int queen[8][8] = { -20,-10,-10, -5, -5,-10,-10,-20,
                    -10,  0,  0,  0,  0,  0,  0,-10,
                    -10,  0,  5,  5,  5,  5,  0,-10,
                     -5,  0,  5,  5,  5,  5,  0, -5,
                      0,  0,  5,  5,  5,  5,  0, -5,
                    -10,  5,  5,  5,  5,  5,  0,-10,
                    -10,  0,  5,  0,  0,  0,  0,-10,
                    -20,-10,-10, -5, -5,-10,-10,-20 };

int king[8][8] = {  -30,-40,-40,-50,-50,-40,-40,-30,
                    -30,-40,-40,-50,-50,-40,-40,-30,
                    -30,-40,-40,-50,-50,-40,-40,-30,
                    -30,-40,-40,-50,-50,-40,-40,-30,
                    -20,-30,-30,-40,-40,-30,-30,-20,
                    -10,-20,-20,-20,-20,-20,-20,-10,
                     20, 20,  0,  0,  0,  0, 20, 20,
                     20, 30, 10,  0,  0, 10, 30, 20 };
