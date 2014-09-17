#include "pieceheaders.h"
#include "global.h"

using namespace sf;

extern int enpasant;

//pawn class with id 1 and weight 100
Pawn::Pawn(int pl):pieces(pl,1,100)
{
}

//draws the pawn piece
void Pawn::draw(RenderWindow & window,Vector2f position)
{
    //If nothing previously stored in image object then loading the image
    if(image.getTexture()==NULL)
    {
        if(player==1)
                ptexture.loadFromFile("sprite.png",IntRect(0,0,75,75));
        else
                ptexture.loadFromFile("sprite.png",IntRect(0,75,75,75));
    }
    image.setTexture(ptexture);
    image.setPosition(position.x,position.y+50);
    window.draw(image);
}

//gets all the valid moves avaliable for the piece by brute force
void Pawn::getposmoves (Vector2i current,std::vector <Vector2i> &moves, pieces* board[8][8],int turn)
{
    int temp = currentState->player; //If multiplayer game then inverting the possible moves for player 2 as his prespective of board in inverted
    if (temp == 2)
        turn=3-turn;
    //If player 1 turn then checking the moves 1 by 1
    if(turn==1 && current.y>0)
    {
        if(board[current.y-1][current.x]->getplayer()==0)
            moves.push_back(Vector2i(current.x,current.y-1));
        if(current.x<7)
            if((board[current.y-1][current.x+1]->getplayer()==((temp==2)?1:2)  || (enpasant==true && board[current.y][current.x+1]->getplayer()==((temp==2)?1:2))) && current.x<8)
                moves.push_back(Vector2i(current.x+1,current.y-1));
        if(current.x>0)
            if((board[current.y-1][current.x-1]->getplayer()==((temp==2)?1:2)  || (enpasant==true && board[current.y][current.x-1]->getplayer()==((temp==2)?1:2))) && current.x>=0)
                moves.push_back(Vector2i(current.x-1,current.y-1));
        if(current.y==6 && board[current.y-1][current.x]->getplayer()==0)
            if(board[current.y-2][current.x]->getplayer()==0)
                moves.push_back(Vector2i(current.x,current.y-2));
    }
    else if(current.y<7) //Checking player 2 moves 1 by 1
    {
        if(board[current.y+1][current.x]->getplayer()==0)
            moves.push_back(Vector2i(current.x,current.y+1));
        if(current.x>0)
            if((board[current.y+1][current.x-1]->getplayer()==1 || (enpasant==true && board[current.y][current.x-1]->getplayer()==1)) && current.x>=0)
                moves.push_back(Vector2i(current.x-1,current.y+1));
        if(current.x<7)
            if((board[current.y+1][current.x+1]->getplayer()==1 || (enpasant==true && board[current.y][current.x+1]->getplayer()==1)) && current.x<8)
                moves.push_back(Vector2i(current.x+1,current.y+1));
        if(current.y==1 && board[current.y+1][current.x]->getplayer()==0)
            if(board[current.y+2][current.x]->getplayer()==0)
                moves.push_back(Vector2i(current.x,current.y+2));
    }
    if (temp==2)
        turn=3-turn;
}

//returns the bonus value of each piece
int Pawn::bonusposition(Vector2i current,pieces *board[8][8])
{
    int bonus=0;
    if(player==1)
        bonus+=pawn[current.y][current.x];
    else
        bonus+=pawn[7-current.y][7-current.x];
	return bonus;
}
