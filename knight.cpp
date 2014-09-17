#include "pieceheaders.h"
#include "global.h"

using namespace sf;

//knight class with id 3 and weight 320
Knight::Knight(int pl):pieces(pl,3,320)
{
}

void Knight::draw(RenderWindow & window,Vector2f position)
{
    if(image.getTexture()==NULL)
    {
        if(player==1)
            ptexture.loadFromFile("sprite.png",IntRect(150,0,75,75));
        else
            ptexture.loadFromFile("sprite.png",IntRect(150,75,75,75));
    }
        image.setTexture(ptexture);
        image.setPosition(position.x,position.y+50);
        window.draw(image);

}

void Knight::getposmoves (Vector2i current,std::vector <Vector2i> &moves, pieces* board[8][8],int turn)
{
    Vector2i temp;

    //Checking all 8 possible moves by knight
    temp.x=current.x+2 ; temp.y=current.y+1;
    if(temp.x<8 && temp.y<8 && board[temp.y][temp.x]->getplayer()!=turn)
        moves.push_back(temp);

    temp.x=current.x+2 ; temp.y=current.y-1;
    if(temp.x<8 && temp.y>=0 && board[temp.y][temp.x]->getplayer()!=turn)
        moves.push_back(temp);

    temp.x=current.x-2 ; temp.y=current.y+1;
    if(temp.x>=0 && temp.y<8 && board[temp.y][temp.x]->getplayer()!=turn)
        moves.push_back(temp);

    temp.x=current.x-2 ; temp.y=current.y-1;
    if(temp.x>=0 && temp.y>=0 && board[temp.y][temp.x]->getplayer()!=turn)
        moves.push_back(temp);

    temp.x=current.x+1 ; temp.y=current.y+2;
    if(temp.x<8 && temp.y<8 && board[temp.y][temp.x]->getplayer()!=turn)
        moves.push_back(temp);

    temp.x=current.x-1 ; temp.y=current.y+2;
    if(temp.x>=0 && temp.y<8 && board[temp.y][temp.x]->getplayer()!=turn)
        moves.push_back(temp);

    temp.x=current.x+1 ; temp.y=current.y-2;
    if(temp.x<8 && temp.y>=0 && board[temp.y][temp.x]->getplayer()!=turn)
        moves.push_back(temp);

    temp.x=current.x-1 ; temp.y=current.y-2;
    if(temp.x>=0 && temp.y>=0 && board[temp.y][temp.x]->getplayer()!=turn)
        moves.push_back(temp);
}


int Knight::bonusposition(Vector2i current,pieces *board[8][8])
{
    int bonus=0;
    if(player==1)
        bonus+=rook[current.y][current.x];
    else
        bonus+=rook[7-current.y][7-current.x];
	return bonus;
}
