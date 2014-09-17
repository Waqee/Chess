#ifndef CHESS_H_INCLUDED
#define CHESS_H_INCLUDED

#include "chessboard.h"

//And intermidiate class between game states and chess board class usually used for interacting smoothly between them

class chess {
    private:
        chessboard board;
    public:
        void reset(sf::RenderWindow &,int player=0);
        void update(sf::RenderWindow &,sf::Vector2f,sf::Vector2f,sf::Clock&);
        bool move(sf::RenderWindow &,sf::Vector2f,sf::Vector2f,sf::Clock&);
        bool end(sf::RenderWindow &,sf::Vector2f,sf::Vector2f);
        bool time(sf::RenderWindow &,sf::Clock&,sf::Vector2f);
        void promotion(sf::RenderWindow &,int);
        int getturn();
        void sender(sf::Packet &);
        void receiver(sf::RenderWindow&,sf::Packet &);
        void disconnected(sf::RenderWindow&);
        int computerturn(sf::RenderWindow&,int);
};

#endif
