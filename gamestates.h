#ifndef GAMESTATES_H_INCLUDED
#define GAMESTATES_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include "chess.h"

using namespace std;


//The type for indicating the states
enum GameStates
{
    STATE_NULL,
    STATE_TITLE, //First main menu
    STATE_COMPUTER, //Game for human v computer
    STATE_GAME, //Game for 2-player mode
    STATE_SINGLE,//Screen displaying option for single player game
    STATE_COMVCOM, //Game for playing computer v computer match
    STATE_PROMOTION, //Promotion state
    STATE_MULTI_TITLE1, //Multiplayer title 1 screen showing server and client buttons
    STATE_MULTI_TITLE2, //Screen showing wait or text box
    STATE_MULTIPLAYER, //Playing multiplayer game
    STATE_EXIT //Exiting game
};


//Abstract base class containing functions to be called for running game
class GameState {
    protected:
        sf::RenderWindow &window; //Refernce to window passed to each game state used for rendering on the screen
        sf::Event event; //Event object used by every gamestate
        sf::Vector2f fixedpos; //Variable to put position of mouse when button clicked
        static sf::TcpSocket socket; //Used in networking to connect to a socket in one game state then use it in another thus has class scope
    public:
		int temp;
        bool end;
        sf::Clock clock;
        chess Chess;
        int promotion;
        int turn;
        int player;
        GameState (sf::RenderWindow& wind) : window(wind),promotion(0),turn(1),player(0),end(0) { }
        virtual void handle_events() = 0; //Function that handles keypresses
        virtual void logic() = 0; //Function that does logic
        virtual void render() = 0; //Function that renders graphics to the window
};


//Derived classes of game state showing the cirrent state

//Title screen
class Title : public GameState {
    public:
        Title(sf::RenderWindow&);
        void handle_events();
        void logic();
        void render();
};

//Single player screen
class Single : public GameState {
    public:
        Single(sf::RenderWindow&);
        void handle_events();
        void logic();
        void render();
};

//2 player player game on same computer
class Game : public GameState {
        int status;
    public:
        Game(sf::RenderWindow&);
        void handle_events();
        void logic();
        void render();
};

//Promotion window
class Promotion : public GameState {
    public:
        Promotion(sf::RenderWindow&);
        void handle_events();
        void logic();
        void render();
};

//Multiplayer title screen
class Multi1 : public GameState {
        string ip[2];
    public:
        Multi1(sf::RenderWindow&);
        void handle_events();
        void logic();
        void render();
};

//Second multiplayer title screen
class Multi2 : public GameState {
        sf::TcpListener listener;
        sf::RectangleShape rect;
        sf::String sentence2;
        string ip[2];
    public:
        Multi2(sf::RenderWindow&,int);
        void handle_events();
        void logic();
        void render();
};

//Multiplayer game
class Multiplayer : public GameState {
        int status;
        sf::Packet packet;
    public:
        Multiplayer(sf::RenderWindow&,int);
        void handle_events();
        void logic();
        void render();
};

//Single player game against computer
class AI: public GameState {
        int status;
    public:
        AI(sf::RenderWindow&);
        void handle_events();
        void logic();
        void render();
};

//Computer v Computer match
class comvcom : public GameState {
    public:
        comvcom(sf::RenderWindow&);
        void handle_events();
        void logic();
        void render();
};
#endif
