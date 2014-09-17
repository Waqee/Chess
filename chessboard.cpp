#include "chessboard.h"
#include "global.h"
#include "algo.h"
#include <cstring>

using namespace sf;

Vector2i propiece;

int enpasant=0; //variable to indicate if enpasant move is valid

int castle[2][2]; //Variable to indicate if castling can be done

//Draws the board
void chessboard::drawboard (RenderWindow &temp)
{

    if(tile.getTexture()==NULL)
    {
        ptexture1.loadFromFile("images.png");
        tile.setTexture(ptexture1);
        tile.setScale(2,1);
    }

    temp.draw(tile);

    if(boardpic.getTexture()==NULL)
    {
        ptexture2.loadFromFile("board.png");
        boardpic.setTexture(ptexture2);
        boardpic.setPosition(0,50);
    }

    temp.draw(boardpic); //Draws the board stored in class variable

    //Loops through valid moves and displays a green box over the valid moves
    int size = moves.size();
    for(int i=0;i<size;i++)
    {
        Texture ptexture;
        Sprite highlight;
        ptexture.loadFromFile("highlight.jpg"); //load the green box
        highlight.setTexture(ptexture);
        highlight.setColor(sf::Color(0,255,0,100)); //Makes color to green and adds transparency by changing alpha value to 100
        highlight.setScale(0.5,0.5);
        highlight.setPosition(moves[i].x*75,moves[i].y*75+50);
        temp.draw(highlight);
    }
}

//Initializes the piece positions
void chessboard::initialize(int player)
{
    turn = 1; //Puts player 1s turn
    //Array stores the starting positions in chess
    pieces *startup[8][8] = {
                            new Rook(2),new Knight(2),new Bishop(2),new King(2),new Queen(2),new Bishop(2),new Knight(2),new Rook(2),
                            new Pawn(2),new Pawn(2),new Pawn(2),new Pawn(2),new Pawn(2),new Pawn(2),new Pawn(2),new Pawn(2),
                            new Empty,new Empty,new Empty,new Empty,new Empty,new Empty,new Empty,new Empty,
                            new Empty,new Empty,new Empty,new Empty,new Empty,new Empty,new Empty,new Empty,
                            new Empty,new Empty,new Empty,new Empty,new Empty,new Empty,new Empty,new Empty,
                            new Empty,new Empty,new Empty,new Empty,new Empty,new Empty,new Empty,new Empty,
                            new Pawn(1),new Pawn(1),new Pawn(1),new Pawn(1),new Pawn(1),new Pawn(1),new Pawn(1),new Pawn(1),
                            new Rook(1),new Knight(1),new Bishop(1),new King(1),new Queen(1),new Bishop(1),new Knight(1),new Rook(1)
                            };
    int i,j;
    //In case of multiplayer if player is 1 then draws board normally
    if(player!=2)
    {
        for(i=0; i<8; i++)
            for(j=0; j<8; j++)
                  board[i][j]=startup[i][j];
    }
    else //otherwise reverts board for player 2
    {
        for(i=0; i<8; i++)
            for(j=0; j<8; j++)
                board[i][j]=startup[7-i][7-j];
    }

    //sets checkmate and stalemate variables to false
    Checkmate=false;
    Stalemate=false;

    //Castling in all 4 conditions is possible
    castle[0][0]=1;castle[0][1]=1;
    castle[1][0]=1;castle[1][1]=1;
}

//Draws the pieces on board
void chessboard::draw(RenderWindow &window,Vector2i excep)
{
    //loops through 8x8 array and draws all the pieces except the one being drageed indicated by variable excep
    for(int i=0; i<8; i++)
    {
        for (int j=0; j<8; j++)
        {
            if(i!=excep.y || j!=excep.x || board[excep.y][excep.x]->getplayer()!=turn)
            {
                sf::Vector2f position(j*75,i*75);
                board[i][j]->draw(window,position);
            }
        }
    }
    Font font;
    font.loadFromFile("acmesa.TTF");

    //If any player king is in check then displays the text showing king check
    sf::String sentence;
    sentence="Player ";
    sentence+=turn==1?'1':'2';
    sentence+=" Turn";
    if(check[turn-1]==1)
        sentence+="  Checked";

    Text text(sentence,font,35);
    text.setColor(Color(100,60,20));

    window.draw(text);
}

//Incase of drag and drop updates the board and shows the piece being dragged constantly on new position
void chessboard::update(RenderWindow &window,Vector2f position,Vector2f fixedpos)
{
    int x,y;
    x=fixedpos.x/75;
    y=(fixedpos.y)/75;
    //Fixes co-ordinates to show the piece in middle of cursor
    position.x-=35;
    position.y+=15;
    moves.clear();

    //In case of multiplayer only shows the piece being dragged if its the players turn and doesnt show the movement to other player until its completed
    if(board[y][x]->getplayer()==turn)
    {
        board[y][x]->draw(window,position);
        board[y][x]->getposmoves(Vector2i(fixedpos.x/75,fixedpos.y/75),moves,board,turn); //Gets the moves the dragged piece can make
    }

}

//A large function that checks if the move is valid then checks if it doesnt put king in check, also checks ending condition,and special moves
void chessboard::move(RenderWindow & window,Vector2i position,Vector2i fixedpos,Clock &clock)
{
    if (board[fixedpos.y][fixedpos.x]->getplayer()==turn ) //if the piece picked was the players piece
    {
        //looping through all the valid moves to see if move being played is valid
        int size=moves.size();
        for(int i=0; i<size;i++)
            if(moves[i].y==position.y && moves[i].x==position.x)
            {
                //Puts the dragged piece to new position and puts and empty piece on previous position
                pieces *temp = board[position.y][position.x]; //variale to store the piece being deleted in case we need to revert the move in case of check
                board[position.y][position.x]=board[fixedpos.y][fixedpos.x];
                board[fixedpos.y][fixedpos.x]=new Empty;

                //indicated wether caslting was tried as in this case 2 moves are done in 1 turn
                int castle_status=0;

                //Doing a caslting move thus moving the king and castle both at same time
                if(board[position.y][position.x]->getid()==6 && (position.x==fixedpos.x-2)) //this handles castling to right
                {
                    pieces *empty= board[position.y][position.x+1];
                    board[position.y][position.x+1]= board[position.y][0];
                    board[position.y][0]= empty;

                    castle_status=1;
                }
                else if(board[position.y][position.x]->getid()==6 && (position.x==fixedpos.x+2)) //this handles castling to left
                {
                    pieces *empty = board[position.y][position.x-1];
                    board[position.y][position.x-1] = board[position.y][7];
                    board[position.y][7]= empty;

                    castle_status=-1;
                }

                checker(); //checker function that indicates wether king is in check

                if(check[turn-1]==1) //If check returned true this means last move was not possible so reverting the move
                {
                    delete board[fixedpos.y][fixedpos.x];
                    board[fixedpos.y][fixedpos.x]=board[position.y][position.x];
                    board[position.y][position.x]=temp;

                    //Reverting the castling move if made
                    if(castle_status!=0) //indicates the last move made was castling one
                    {
                        //Returns rook to original positions
                        pieces *empty = board[position.y][position.x+castle_status];
                        board[position.y][position.x+castle_status]=board[position.y][castle_status==1?0:7];
                        board[position.y][castle_status==1?0:7] = empty;
                    }
                    break;
                }
                else //if the move was valid and doesnt put king in check then deleting the temp variable
                    delete temp;

				castle_checker(); //castle checker function the renews the caslting array values to new values indicating if casszztling is possible or notcastle_checker(); //castle checker function the renews the caslting array values to new values indicating if castling is possible or not

                if(enpasant==true && board[position.y][position.x]->getid()==1) //If the move done was enpassant then  deleting the pawn behind moved pawn according to rules
                {
                    int y=position.y;
                    turn == 1 ? y+=1:y-=1;
                    delete board[y][position.x];
                    board[y][position.x]=new Empty;
                }
                enpasant=false; //reverting the enpasant variable to false

                if(board[position.y][position.x]->getid()==1 && (fixedpos.y==position.y+2 || fixedpos.y==position.y-2)) //check if enpassant move is made
                   enpasant=true;

                //handles promotion
                if (board[position.y][position.x]->getid()==1)
                    promotion(position,clock);
                else //else changes turn and restarts the clock
                {
                    turn = 3-turn;
                    clock.restart();
                    checker(); //check function to indicate wether other player is checked
                    checkmate(); //check mate function to indicate wethr ending condition reached
                }
                break;
            }
    }
    moves.clear(); //clear the vector containing valid moves
}


//Function to check if castling is valid, check the board to see if any king or castle have moved from there positions
void chessboard::castle_checker()
{
    if(castle[0][0]==1 && (board[7][0]->getid()!=2 || board[7][3]->getid()!=6))
        castle[0][0]=0;
    if(castle[0][1]==1 && (board[7][7]->getid()!=2 || board[7][3]->getid()!=6))
        castle[0][1]=0;
    if(castle[1][0]==1 && (board[0][0]->getid()!=2 || board[0][3]->getid()!=6))
        castle[1][0]=0;
    if(castle[1][1]==1 && (board[0][7]->getid()!=2 || board[0][3]->getid()!=6))
        castle[1][1]=0;
}

//Function to check wether king is being attacked
void chessboard::checker()
{
    vector <Vector2i> temp;
    //Loop through all the opponent pieces, get there valid move and check if king is in any of those moves
    for (int i=0 ;i <8; i++)
        for (int j=0; j<8; j++)
            if (board[i][j]->getplayer()==3-turn)
            {
                board[i][j]->getposmoves(Vector2i(j,i),temp,board,3-turn);
                for(int z=0; z<temp.size(); z++)
                    if(board[temp[z].y][temp[z].x]->getid() == 6 && board[temp[z].y][temp[z].x]->getplayer()==turn)
                    {
                        check[turn-1]=1; //If king is present in any opponent moves then making chess variable true
                        return;
                    }
                temp.clear();
            }
    check[turn-1]=0;
}

//Function to check for check mate or stale mate
void chessboard::checkmate()
{
    int cond = check[turn-1]; //Storing the current state i.e wether king is check or not
    vector <Vector2i> temp;
    //Looping throung all our possible moves and checking if any of those moves puts king out of check
    for (int i=0 ;i <8; i++)
        for (int j=0; j<8; j++)
            if (board[i][j]->getplayer()==turn)
            {
                board[i][j]->getposmoves(Vector2i(j,i),temp,board,turn);
                for(int z=0; z<temp.size(); z++)
                {
                    //Temporarily moving each piece
                    pieces *tempa = board[temp[z].y][temp[z].x];
                    board[temp[z].y][temp[z].x]=board[i][j];
                    board[i][j]=new Empty;

                    checker(); //Checking if king still in check

                    //Reverting previous move
                    delete board[i][j];
                    board[i][j]=board[temp[z].y][temp[z].x];
                    board[temp[z].y][temp[z].x]=tempa;

                    //If king is not in check the returning false
                    if(check[turn-1]==0)
                    {
                        check[turn-1]=cond;
                        return;
                    }
                }
                temp.clear();
            }
        //If none of the moves puts king out of check then ending game with check mate if king was already in check or stale mate if king was not previously in check
        if(cond==1)
            Checkmate=true;
        else
            Stalemate=true;
}

//Function for displaying winner when game ends
void chessboard::ending(RenderWindow & window)
{
    Font font;
    font.loadFromFile("acmesa.TTF");
    sf::String sentence;
    if(Checkmate==true) //If checkmate then displaying the winner
    {
        sentence="Player ";
        sentence+=turn==2?'1':'2';
        sentence+=" Won";
    }
    else if (Stalemate == true) //if stalemate then displaying draw
        sentence="Stalemate - Draw";

    Text text(sentence,font,60);
    text.setPosition(50,100);
    text.setColor(Color::Red);

    window.draw(text);
}

//Function for checking promotion
void chessboard::promotion(Vector2i position,Clock &clock)
{
    //Checks if any of the pawns reached the last file
    if((board[position.y][position.x]->getplayer()==1 && position.y==0) ||
        (board[position.y][position.x]->getplayer()==2 && position.y==7))
    {
        //If condition is true then changing state to promotion to ask user for the piece to promote to
        set_next_state( STATE_PROMOTION );
        propiece.x=position.x;
        propiece.y=position.y;
    }
    else //if promotion is not valid then ending turn and restarting clock
    {
        turn = 3-turn;
        clock.restart();
        checker();
        checkmate();
    }
}

//Function for promotion of a pawn
void chessboard::promote(int type)
{
    //Deletes the current piece
    delete board[propiece.y][propiece.x];

    //Places a new chess piece according to type selected by user
    if(type==2)
        board[propiece.y][propiece.x]=new Rook(turn);
    else if(type==3)
        board[propiece.y][propiece.x]=new Knight(turn);
    else if(type==4)
        board[propiece.y][propiece.x]=new Bishop(turn);
    else
        board[propiece.y][propiece.x]=new Queen(turn);

    turn = 3-turn; //Ending turn of the user
    checker();//Check if king in check
    checkmate(); //Check for check mate or stale mate
}

//Function to store the piece positions on board in a packet to be sent over a network
void chessboard::sender(Packet &packet)
{
    //A testing variable sent on top of each packet
    int test =1;
    packet<<test;

    //The pieces are sent in inverted form as other user views the chess board from his prespective
    for(int i=7; i>=0; i--)
        for( int j=7; j>=0; j--)
            packet<<board[i][j]->getid()<<board[i][j]->getplayer(); //Send id and player of each chess piece
}

//Function to set the board according to the contents of the packet recieved over network
void chessboard::receiver(Packet &packet)
{
    //Loops through the board
    int id,player;
    for(int i=0; i<8; i++)
        for( int j=0; j<8; j++)
        {
            delete board[i][j]; //Deleted current piece

            //Places new piece according to id and player stored in packet
            packet>>id>>player;
            switch(id)
            {
                case 0 :
                board[i][j]=new Empty;
                break;

                case 1 :
                board[i][j]=new Pawn(player);
                break;

                case 2 :
                board[i][j]=new Rook(player);
                break;

                case 3 :
                board[i][j]=new Knight(player);
                break;

                case 4 :
                board[i][j]=new Bishop(player);
                break;

                case 5 :
                board[i][j]=new Queen(player);
                break;

                case 6 :
                board[i][j]=new King(player);
                break;
            }
        }

    //Changes turn and checks as done with end of each turn
    turn = 3-turn;
    checker();
    checkmate();
}


//Function that calls ai function for computer generated move
void chessboard::autoturn(int depth)
{
    Computer play; //Object of class type Computer
    Vector2i *move; //Pointer to store the best move

    //Castling allowed to human player
    castle[turn-1][0]=0;
    castle[turn-1][1]=1;

    //Calling the COmputer function to get best move
    move=play.minimax(depth,*this,turn);

    //Doing the best move
    board[move[1].y][move[1].x]=board[move[0].y][move[0].x];
    board[move[0].y][move[0].x]=new Empty;

    //Ending turn and checking for end conditions
    turn = 3-turn;
    checker();
    checkmate();
    delete [] move; //Deleting the pointer after it has been used
}
