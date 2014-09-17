#ifndef CHESSBOARD_H_INCLUDED
#define CHESSBOARD_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include <iostream>
#include "pieceheaders.h"

using namespace std;

//Main class that handles all the logic of the game

class chessboard {
    private:
        vector <sf::Vector2i> moves; //Stores the valid moves the piece picked by a user can make
        int check[2]; //array for indicating if king is in check
        pieces *board[8][8];  //Stores the current pieces positions on board in form of 2d array of type pieces(and polymerised class)
        sf::Texture ptexture1;
        sf::Sprite tile;//Stored the tile on top on which player name and time is displayed
        sf::Sprite boardpic; //Stores the picture of board for displaying
        sf::Texture ptexture2;
    public:
        int turn;
        bool Checkmate;
        bool Stalemate;
        void drawboard(sf::RenderWindow &);
        void initialize(int);
        void draw(sf::RenderWindow &,sf::Vector2i);
        void update(sf::RenderWindow &,sf::Vector2f,sf::Vector2f);
        void move(sf::RenderWindow &,sf::Vector2i,sf::Vector2i,sf::Clock&);
        void checker();
        void checkmate();
        void ending(sf::RenderWindow &);
        void promotion(sf::Vector2i,sf::Clock&);
        void promote(int);
        void sender(sf::Packet &);
        void receiver(sf::Packet &);
        void autoturn(int);
        friend class Computer;
        void castle_checker();
};

#endif
