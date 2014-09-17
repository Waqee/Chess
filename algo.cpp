#include "algo.h"
#include "global.h"


//Function to evaluate the board passed
int Computer::Evaluate(chessboard &chess)
{
    int material=0,bonus=0,mobility=0; //Sets the variables to zero
    //Loops through all positions
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
        {
            if(chess.board[i][j]->getid()!=0) //Checks if there is a piece on the current position, 0 indicates an empty box
            {
                vector <Vector2i> moves; //vector for storing moves
                if(chess.board[i][j]->getplayer()==1) //If piece belongs to player 1 then decreasing the board value for each advantage of player 1
                {
                    material-=chess.board[i][j]->weight; //Decrease according to material value of each piece as set by coder
                    chess.board[i][j]->getposmoves(Vector2i(j,i),moves,chess.board,1);
                    mobility-=moves.size(); //Decrease according to number of moves a piece can make, larger number of moves means better mobility for a player
                    bonus-=chess.board[i][j]->bonusposition(Vector2i(j,i),chess.board); //Decrease according to bonus values set in piece tables in global.cpp
                }
                else //Similar to player 1s evaluation but this increases the board value
                {
                    material+=chess.board[i][j]->weight;
                    chess.board[i][j]->getposmoves(Vector2i(j,i),moves,chess.board,2);
                    mobility+=moves.size();
                    bonus+=chess.board[i][j]->bonusposition(Vector2i(j,i),chess.board);
                }
            }
        }
        return material+bonus/2+mobility/2; //returning the desired sum of the board values
}

int bestvalue; //Stores best value for the first move

void func(chessboard *chess, int depth,int turn,Vector2i* bestmove,Vector2i start,Vector2i end)
{
    Computer temp;
    if(turn==2) //If the computer is playing for player 2 then calling minSearch and trying to find largest value of board for each value returned by minsearch
    {
        int value = temp.minSearch( depth-1 , *chess ,-INFINITY,INFINITY); //Finding all the minimum values of board

        if( value > bestvalue ) //Selecting the best move by finding the maximum of the values obtained
        {
            bestvalue = value;
            bestmove[0].x = start.x;
            bestmove[0].y = start.y;
            bestmove[1].x = end.x;
            bestmove[1].y = end.y;
        }
    }
    else //Opposite of that for player 1
    {
        int value = temp.maxSearch( depth-1 , *chess,-INFINITY,INFINITY ); //Finds all maximum values of board

        if( value < bestvalue ) //Selects the lowest of those values
        {
            bestvalue = value;
            bestmove[0].x = start.x;
            bestmove[0].y = start.y;
            bestmove[1].x = end.x;
            bestmove[1].y = end.y;
        }
    }
    delete chess; //Chess board obtained is deleted as no longer needed

}
Vector2i* Computer::minimax ( int depth, chessboard &a,int turn)
{
    //Implemented the code first to work with thread, it worked fine for sometime then started show strange XInitThread error so had to remove threading
  
    //Array to store the best move
    Vector2i* bestmove = new Vector2i[2];

    int i,j;

    //Putting value least beneficial to player in best value variable
    if(turn==1)
        bestvalue=INFINITY;
    else
        bestvalue=-INFINITY;

    vector<Vector2i> ::iterator it;

    vector<Vector2i> Z;

    //Looping through all the moves the player can make
    for( i = 0; i < 8; i++ )

        for( j = 0; j < 8; j++ )
        {
            if(a.board[i][j]->getid()!=0 && a.board[i][j]->getplayer()==turn )
            {
                a.board[i][j]->getposmoves(Vector2i(j,i),Z,a.board,turn);
                for(it=Z.begin();it!=Z.end();it++)
                {
                    //making a copy of the chess obard
                    chessboard *chess= new chessboard(a);

                    //Attempting the move
                    chess->board[(*it).y][(*it).x]= chess->board[i][j];
                    chess->board[i][j]=new Empty;
                    if(chess->board[(*it).y][(*it).x]->getid() == 1 && (*it).y==(turn-1)*7)
                        chess->board[(*it).y][(*it).x]=new Queen(turn);

                    chess->checker(); //Checking if move was valid
                    if(chess->check[turn-1]==0) //If move was valid then passing it to func
                    {
                        func(chess,depth,turn,bestmove,Vector2i(j,i),Vector2i((*it).x,(*it).y));
                    }
                    //Undo Move
                }
                Z.clear(); //Clear all the moves of each piece after going through them
            }
        }
        //Returning the best move i.e the move for which board had most favourable value
        return bestmove;
}

//Function that tries to find the minimum value of board
int Computer::minSearch( int depth , chessboard &chess, int alpha, int beta)
{
    int turn =1;
    short int i;
    short int j;

    //Checking for check mate or stale mate and if true then returning large values depending upon depth of search
    chess.checkmate();
    if(chess.Checkmate==true)
    {
        chess.Checkmate=false;
        return INFINITY/depth;
    }
    else if(chess.Stalemate==true)
    {
        chess.Stalemate=false;
        if(Evaluate(chess)<0)
            return INFINITY/(2*depth);
        else
            return -INFINITY/(2*depth);
    }

    //If the function has searched to the desired depth then returning the board value
    if(depth==0)
        return Evaluate(chess);

    vector<Vector2i> ::iterator it;
    vector<Vector2i> Z;

    int bestValue = INFINITY;

    int promotion = 0 ;
    //Looping through all the moves
    for( i = 0; i < 8; i++ )
        for( j = 0; j < 8; j++ )
        {
            if(chess.board[i][j]->getid()!=0 && chess.board[i][j]->getplayer()==1)
            {
                chess.board[i][j]->getposmoves(Vector2i(j,i),Z,chess.board,1);
                for(it=Z.begin();it!=Z.end();it++)
                {
                    //Temporarily executing move
                    pieces* DestinationPiece;
                    DestinationPiece=chess.board[(*it).y][(*it).x];
                    //Moving
                    chess.board[(*it).y][(*it).x]= chess.board[i][j];
                    chess.board[i][j]=new Empty;
                    //If any pawn reaches last file than promoting it to queen automatically
                    if(chess.board[(*it).y][(*it).x]->getid() == 1 && (*it).y==0)
                    {
                        promotion=1;
                        chess.board[(*it).y][(*it).x]=new Queen(1);
                    }
                    //
                    chess.checker(); //Checking if move is valid
                    if(chess.check[0]==0)
                    {
                        //If move was valid the finding the opponents respponse to the move i.e calling maxSearch which finds the best response by opponent
                        int value = maxSearch( depth-1 , chess,alpha,beta );
                        if( value <= alpha ) //Alpha-beta pruning if value is less then alpha value then returning the alpha value indicating very bad move
                        {
                            chess.board[i][j]=chess.board[((*it).y)][(*it).x];
                            chess.board[(*it).y][(*it).x]=DestinationPiece;
                            return alpha;
                        }
                        if( value < beta ) //Else storing value in beta value to find best beta value
                            beta = value;
                    }
                    //Undo Move
                    if(promotion==1)
                        chess.board[i][j]=new Pawn(1);
                    else
                        chess.board[i][j]=chess.board[((*it).y)][(*it).x];
                    chess.board[(*it).y][(*it).x]=DestinationPiece;

                }
                Z.clear(); //Clear all the moves of each piece after going through them
            }
        }
        return beta; //returns lowest beta value i.ebesst move for the player
}

//Almost identical to minSearch, only difference being that it tries to maxmize the board and find most profitable move for player 2
int Computer::maxSearch( int depth , chessboard &chess, int alpha, int beta)
{
    short int i;
    short int j;
    chess.turn=2;
    chess.checkmate();
    if(chess.Checkmate==true)
    {
        chess.Checkmate=false;
        return -INFINITY/depth;
    }
    else if(chess.Stalemate==true)
    {
        chess.Stalemate=false;
        if(Evaluate(chess)<0)
            return INFINITY/(2*depth);
        else
            return -INFINITY/(2*depth);
    }

    if(depth==0)
        return Evaluate(chess);

    vector<Vector2i> ::iterator it;
    vector<Vector2i> Z;

    int bestValue = -INFINITY;

    int promotion = 0;

    for( i = 0; i < 8; i++ )
        for( j = 0; j < 8; j++ )
        {
            if(chess.board[i][j]->getid()!=0 && chess.board[i][j]->getplayer()==2 )
            {
                chess.board[i][j]->getposmoves(Vector2i(j,i),Z,chess.board,2);
                for(it=Z.begin();it!=Z.end();it++)
                {
                    pieces* DestinationPiece;
                    DestinationPiece=chess.board[(*it).y][(*it).x];
                    //Moving
                    chess.board[(*it).y][(*it).x]= chess.board[i][j];
                    chess.board[i][j]=new Empty;

                    if(chess.board[(*it).y][(*it).x]->getid() == 1 && (*it).y==7)
                    {
                        promotion=1;
                        chess.board[(*it).y][(*it).x]=new Queen(2);
                    }

                    //
                    chess.checker();
                    if(chess.check[1]==0)
                    {
                        int value = minSearch( depth-1 , chess ,alpha,beta);
                        if( value >= beta )
                        {   chess.board[i][j]=chess.board[((*it).y)][(*it).x];
                            chess.board[(*it).y][(*it).x]=DestinationPiece;
                            return beta;
                        }
                        if( value>alpha )
                            alpha=value;
                    }
                    //Undo
                    if(promotion==1)
                        chess.board[i][j]=new Pawn(2);
                    else
                        chess.board[i][j]=chess.board[((*it).y)][(*it).x];
                    chess.board[(*it).y][(*it).x]=DestinationPiece;

                }
                Z.clear();
            }
        }
        return alpha;
}
