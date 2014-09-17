#ifndef PIECEHEADERS_H_INCLUDED
#define PIECEHEADERS_H_INCLUDED


#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

//An abstract base class for keeping the chess piece and derived classes of each type in chess
class pieces {
    protected:
        int player; //player to which piece belongs
        int id; //id of the piece e.g empty has id 0 , pawn has id 1, rook id 2 etc
        sf::Texture ptexture;
        sf::Sprite image; //Stored the image of each piece
    public:
        int weight; //weight assigned to each piece
        int getplayer() { return player;} //Function to get player to whom piece belongs
        pieces(int pl, int ID,int wht):player(pl),id(ID),weight(wht) {} //Constructor
        virtual void draw(sf::RenderWindow &,sf::Vector2f)=0; //Draws the piece on board
        virtual void getposmoves (sf::Vector2i,std::vector <sf::Vector2i> &, pieces *board[8][8],int)=0; //Gets all the possible moves by the piece
        virtual int bonusposition(sf::Vector2i,pieces*[8][8]) = 0; //Gets the bonus value for piece
        int getid() { return id;} //Gets id of the piece
};

//Derived classes of each type in chess

class Empty:public pieces {
    public:
        Empty() :pieces(0,0,0) {};
        void draw(sf::RenderWindow &window,sf::Vector2f position) {}
        void getposmoves (sf::Vector2i,std::vector <sf::Vector2i> &, pieces*[8][8],int) {}
        int bonusposition(sf::Vector2i,pieces*[8][8]) {return 0;}
};


class Pawn:public pieces {
    public:
        Pawn(int pl);
        void draw(sf::RenderWindow &window,sf::Vector2f);
        void getposmoves (sf::Vector2i,std::vector <sf::Vector2i> &, pieces*[8][8],int);
        int bonusposition(sf::Vector2i,pieces*[8][8]);
};

class Bishop:public pieces {
    public:
        Bishop(int pl);
        void draw(sf::RenderWindow &window,sf::Vector2f);
        void getposmoves (sf::Vector2i,std::vector <sf::Vector2i> &, pieces*[8][8],int);
        int bonusposition(sf::Vector2i,pieces*[8][8]);
};

class King:public pieces {
    public:
        King(int pl);
        void draw(sf::RenderWindow &window,sf::Vector2f);
        void getposmoves (sf::Vector2i,std::vector <sf::Vector2i> &, pieces*[8][8],int);
        int bonusposition(sf::Vector2i,pieces*[8][8]);
};

class Knight:public pieces {
    public:
        Knight(int pl);
        void draw(sf::RenderWindow &window,sf::Vector2f);
        void getposmoves (sf::Vector2i,std::vector <sf::Vector2i> &, pieces*[8][8],int);
        int bonusposition(sf::Vector2i,pieces*[8][8]);
};

class Queen:public pieces {
    public:
        Queen(int pl);
        void draw(sf::RenderWindow &window,sf::Vector2f);
        void getposmoves (sf::Vector2i,std::vector <sf::Vector2i> &, pieces*[8][8],int);
        int bonusposition(sf::Vector2i,pieces*[8][8]);
};

class Rook:public pieces {
    public:
        Rook(int pl);
        void draw(sf::RenderWindow &window,sf::Vector2f);
        void getposmoves (sf::Vector2i,std::vector <sf::Vector2i> &, pieces*[8][8],int);
        int bonusposition(sf::Vector2i,pieces*[8][8]);
};

#endif
