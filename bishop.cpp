#include "pieceheaders.h"
#include "global.h"

using namespace sf;

//bishop class with id 4 and weight 330
Bishop::Bishop(int pl):pieces(pl,4,330)
{
}

void Bishop::draw(RenderWindow & window,Vector2f position)
{
    if(image.getTexture()==NULL)
    {
        if(player==1)
            ptexture.loadFromFile("sprite.png",IntRect(75,0,75,75));
        else
            ptexture.loadFromFile("sprite.png",IntRect(75,75,75,75));
    }
        image.setTexture(ptexture);
        image.setPosition(position.x,position.y+50);
        window.draw(image);

}

void Bishop::getposmoves (Vector2i current,std::vector <Vector2i> &moves, pieces* board[8][8],int turn)
{
    Vector2i temp;
    //Checking all possible moves diagonally
    for(temp.x=current.x+1,temp.y=current.y+1;temp.x<8 && temp.y<8 && board[temp.y][temp.x]->getplayer()==0; temp.x++,temp.y++)
        moves.push_back(temp);
    if(temp.x<8 && temp.y<8 && board[temp.y][temp.x]->getplayer()==3-turn)
        moves.push_back(temp);

    for(temp.x=current.x-1,temp.y=current.y+1;temp.x>=0 && temp.y<8 && board[temp.y][temp.x]->getplayer()==0; temp.x--,temp.y++)
        moves.push_back(temp);
    if(temp.x>=0 && temp.y<8 && board[temp.y][temp.x]->getplayer()==3-turn)
        moves.push_back(temp);

    for(temp.x=current.x+1,temp.y=current.y-1;temp.x<8 && temp.y>=0 && board[temp.y][temp.x]->getplayer()==0; temp.x++,temp.y--)
        moves.push_back(temp);
    if(temp.x<8 && temp.y>=0 && board[temp.y][temp.x]->getplayer()==3-turn)
        moves.push_back(temp);

    for(temp.x=current.x-1,temp.y=current.y-1;temp.x>=0 && temp.y>=0 && board[temp.y][temp.x]->getplayer()==0; temp.x--,temp.y--)
        moves.push_back(temp);
    if(temp.x>=0 && temp.y>=0 && board[temp.y][temp.x]->getplayer()==3-turn)
        moves.push_back(temp);
}

int Bishop::bonusposition(Vector2i current,pieces *board[8][8])
{
    int bonus=0;
    if(player==1)
        bonus+=bishop[current.y][current.x];
    else
        bonus+=bishop[7-current.y][7-current.x];
	return bonus;
}

