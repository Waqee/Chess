#include "pieceheaders.h"
#include "global.h"


using namespace sf;

extern int castle[2][2];


//king class with id 6 and wieght a very large value
King::King(int pl):pieces(pl,6,INFINITY)
{

}

void King::draw(RenderWindow & window,Vector2f position)
{
    if(image.getTexture()==NULL)
    {
        if(player==1)
            ptexture.loadFromFile("sprite.png",IntRect(375,0,75,75));
        else
            ptexture.loadFromFile("sprite.png",IntRect(375,75,75,75));
    }
        image.setTexture(ptexture);
        image.setPosition(position.x,position.y+50);
        window.draw(image);
}

void King::getposmoves (Vector2i current,std::vector <Vector2i> &moves, pieces* board[8][8],int turn)
{
    Vector2i temp;
    //Checking if castling moves possible
    if(castle[turn-1][0] == 1)
    {
        if(board[current.y][current.x-1]->getid()==0 && board[current.y][current.x-2]->getid()==0)
            moves.push_back(Vector2i(current.x-2,current.y));
    }
    if(castle[turn-1][1] == 1)
    {
        if(board[current.y][current.x+1]->getid()==0 && board[current.y][current.x+2]->getid()==0 && board[current.y][current.x+3]->getid()==0)
            moves.push_back(Vector2i(current.x+2,current.y));
    }
    //Checking all the adjacent blocks for moves
    temp.x=current.x+1 ; temp.y=current.y;
    if(temp.x<8 && board[temp.y][temp.x]->getplayer()!=turn)
        moves.push_back(temp);

    temp.x=current.x-1 ; temp.y=current.y;
    if(temp.x>=0 && board[temp.y][temp.x]->getplayer()!=turn)
        moves.push_back(temp);

    temp.x=current.x ; temp.y=current.y+1;
    if(temp.y<8 && board[temp.y][temp.x]->getplayer()!=turn)
        moves.push_back(temp);

    temp.x=current.x ; temp.y=current.y-1;
    if(temp.y>=0 && board[temp.y][temp.x]->getplayer()!=turn)
        moves.push_back(temp);

    temp.x=current.x+1 ; temp.y=current.y+1;
    if(temp.x<8 && temp.y<8 && board[temp.y][temp.x]->getplayer()!=turn)
        moves.push_back(temp);

    temp.x=current.x+1 ; temp.y=current.y-1;
    if(temp.x<8 && temp.y>=0 && board[temp.y][temp.x]->getplayer()!=turn)
        moves.push_back(temp);

    temp.x=current.x-1 ; temp.y=current.y+1;
    if(temp.x>=0 && temp.y<8 && board[temp.y][temp.x]->getplayer()!=turn)
        moves.push_back(temp);

    temp.x=current.x-1 ; temp.y=current.y-1;
    if(temp.x>=0 && temp.y>=0 && board[temp.y][temp.x]->getplayer()!=turn)
        moves.push_back(temp);


}


int King::bonusposition(Vector2i current,pieces *board[8][8])
{
    int bonus=0;
    if(player==1)
        bonus+=king[current.y][current.x];
    else
        bonus+=king[7-current.y][7-current.x];
	return bonus;
}
