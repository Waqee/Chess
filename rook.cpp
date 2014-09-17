#include "pieceheaders.h"
#include "global.h"

using namespace sf;

//Rook class with id 2 and weight 500 having same functions as pawn class
Rook::Rook(int pl):pieces(pl,2,500)
{
}

void Rook::draw(RenderWindow & window,Vector2f position)
{
    if(image.getTexture()==NULL)
    {
        if(player==1)
            ptexture.loadFromFile("sprite.png",IntRect(225,0,75,75));
        else
            ptexture.loadFromFile("sprite.png",IntRect(225,75,75,75));
    }
        image.setTexture(ptexture);
        image.setPosition(position.x,position.y+50);
        window.draw(image);

}

void Rook::getposmoves (Vector2i current,std::vector <Vector2i> &moves, pieces* board[8][8],int turn)
{
    //Checking moves valid by rook
    Vector2i temp;
    //Checking in right direction
    for(temp.x=current.x+1,temp.y=current.y;temp.x<8 && board[temp.y][temp.x]->getplayer()==0; temp.x++)
        moves.push_back(temp);
    if(temp.x<8 && board[temp.y][temp.x]->getplayer()==3-turn)
        moves.push_back(temp);

    //Checking in left direction
    for(temp.x=current.x-1,temp.y=current.y; temp.x>=0 && board[temp.y][temp.x]->getplayer()==0; temp.x--)
        moves.push_back(temp);
    if(temp.x>=0 && board[temp.y][temp.x]->getplayer()==3-turn)
        moves.push_back(temp);

    //Checking in up direction
    for(temp.x=current.x,temp.y=current.y-1; temp.y>=0 && board[temp.y][temp.x]->getplayer()==0; temp.y--)
        moves.push_back(temp);
    if(temp.y>=0 && board[temp.y][temp.x]->getplayer()==3-turn)
        moves.push_back(temp);

    //Checking in down direction
    for(temp.x=current.x,temp.y=current.y+1; temp.y<8 && board[temp.y][temp.x]->getplayer()==0; temp.y++)
        moves.push_back(temp);
    if(temp.y<8 && board[temp.y][temp.x]->getplayer()==3-turn)
        moves.push_back(temp);
}

//Bonus values
int Rook::bonusposition(Vector2i current,pieces *board[8][8])
{
    int bonus=0;
    if(player==1)
        bonus+=rook[current.y][current.x];
    else
        bonus+=rook[7-current.y][7-current.x];
	return bonus;
}
