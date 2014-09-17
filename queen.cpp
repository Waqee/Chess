#include "pieceheaders.h"
#include "global.h"

using namespace sf;

//queen class with id 5 and weight 975
Queen::Queen(int pl):pieces(pl,5,975)
{

}

void Queen::draw(RenderWindow & window,Vector2f position)
{
    if(image.getTexture()==NULL)
    {
        if(player==1)
            ptexture.loadFromFile("sprite.png",IntRect(300,0,75,75));
        else
            ptexture.loadFromFile("sprite.png",IntRect(300,75,75,75));
    }
        image.setTexture(ptexture);
        image.setPosition(position.x,position.y+50);
        window.draw(image);

}

void Queen::getposmoves (Vector2i current,std::vector <Vector2i> &moves, pieces* board[8][8],int turn)
{
    Vector2i temp;
    //The rook check function and bishop check function cascaded together to get queens moves
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

    for(temp.x=current.x+1,temp.y=current.y;temp.x<8 && board[temp.y][temp.x]->getplayer()==0; temp.x++)
        moves.push_back(temp);
    if(temp.x<8 && board[temp.y][temp.x]->getplayer()==3-turn)
        moves.push_back(temp);

    for(temp.x=current.x-1,temp.y=current.y; temp.x>=0 && board[temp.y][temp.x]->getplayer()==0; temp.x--)
        moves.push_back(temp);
    if(temp.x>=0 && board[temp.y][temp.x]->getplayer()==3-turn)
        moves.push_back(temp);

    for(temp.x=current.x,temp.y=current.y-1; temp.y>=0 && board[temp.y][temp.x]->getplayer()==0; temp.y--)
        moves.push_back(temp);
    if(temp.y>=0 && board[temp.y][temp.x]->getplayer()==3-turn)
        moves.push_back(temp);

    for(temp.x=current.x,temp.y=current.y+1; temp.y<8 && board[temp.y][temp.x]->getplayer()==0; temp.y++)
        moves.push_back(temp);
    if(temp.y<8 && board[temp.y][temp.x]->getplayer()==3-turn)
        moves.push_back(temp);
}


int Queen::bonusposition(Vector2i current,pieces *board[8][8])
{
    int bonus=0;
    if(player==1)
        bonus+=queen[current.y][current.x];
    else
        bonus+=queen[7-current.y][7-current.x];
	return bonus;
}
