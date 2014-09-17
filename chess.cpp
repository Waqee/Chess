#include "chess.h"
#include <sstream>
#include "global.h"

using namespace sf;

//Functions for converting float to string
std::string Convert (float number)
{
    std::ostringstream buff;
    buff<<number;
    return buff.str();
}

//Initializes board to starting positions
void chess::reset(RenderWindow &window,int player)
{
    board.initialize(player); //chess board function for initializing positions
    board.drawboard(window);  //chessboard function to draw board
    board.draw(window,Vector2i(10,10)); //chess board function to draw pieces
}

//Updates the game board, this is used for drag and drop
void chess::update(RenderWindow &window, Vector2f position, Vector2f fixedpos,Clock &clock)
{
    window.clear(); //clears everything drawn on screen
    time(window,clock,fixedpos); //call time function of chess class
    board.update(window,position,fixedpos); //calls update function of chess board class
}

//If the user made a move that is dropped a piece then validates the move and does resulting evaluations
bool chess::move(RenderWindow &window,Vector2f position, Vector2f fixedpos,Clock &clock)
{
    Vector2i pos(position);
    Vector2i fix(fixedpos);
    board.move(window,Vector2i(pos.x/75,pos.y/75),Vector2i(fix.x/75,fix.y/75),clock);  //chess board function that validates and performs the move
    board.drawboard(window); //draws the board again
    board.draw(window,Vector2i(10,10)); //draws the pieces again
    return end(window,position,fixedpos); //chess class function end to indicate wether check mate or stale mate occured
}

//checks if check mate or stale mate is true and returns result
bool chess::end(RenderWindow &window,Vector2f position, Vector2f fixedpos)
{
    if(board.Checkmate==true || board.Stalemate== true)
    {
        //if either ending conditions reached then redraws board and pieces the displays ending message and return true indicating end is reached
        board.drawboard(window);
        board.draw(window,Vector2i(fixedpos.x/75,fixedpos.y/75));
        board.ending(window);
        return true;
    }
    return false;
}

//time function which handles time shown on top right of screen
bool chess::time(RenderWindow &window,Clock &clock,Vector2f fixedpos)
{
    Time time = clock.getElapsedTime(); //gets elapsed time
    if(time.asSeconds()>=120) //if time is greater then 2 minutes then other player won automatically
    {
        //Makes end true and displays the sentence that player won
        currentState->end=true;
        Font font;
        font.loadFromFile("acmesa.TTF");
        sf::String sentence;
        sentence="Time over Player ";
        sentence+=board.turn==2?'1':'2';
        sentence+=" Won";

        Text text(sentence,font,40);
        text.setPosition(30,100);
        text.setColor(Color::Red);

        window.draw(text);
        return true;
    }

    //displays the time in minutes :: seconds format
    Font font;
    font.loadFromFile("acmesa.TTF");

    sf::String sentence;
    sentence=Convert((int)time.asSeconds()/60);
    sentence+=':';
    sentence+=Convert((int)time.asSeconds()%60);

    Text text(sentence,font,40);
    text.setPosition(490,0);
    text.setColor(Color(100,60,20));
    window.clear();
    board.drawboard(window);
    board.draw(window,Vector2i(fixedpos.x/75,fixedpos.y/75));
    window.draw(text);
}

//Handles promotion
void chess::promotion(RenderWindow &window,int type)
{
    board.promote(type); //Calls chessboard funtion with argument indicating the type to which promotion be done
    board.drawboard(window);
    board.draw(window,Vector2i(10,10));
}

//function for getting the which players turn is it
int chess::getturn()
{
    return board.turn;
}

//Sends packet
void chess::sender(Packet &packet)
{
    board.sender(packet);
}

//recieves packet and redraws the board
void chess::receiver(RenderWindow &window,Packet &packet)
{
    board.receiver(packet);
    board.drawboard(window);
    board.draw(window,Vector2i(10,10));
}

//Function to be called if other player disconnected
void chess::disconnected(RenderWindow &window)
{
    Font font;
    font.loadFromFile("acmesa.TTF");

    sf::String sentence;
    sentence="Opponent disconnected ";

    Text text(sentence,font,30);
    text.setPosition(50,100);
    text.setColor(Color::Red);

    window.draw(text);
}

//Function that calls chess board class for AI
int chess::computerturn(RenderWindow &window,int depth)
{
    board.autoturn(depth); //Function that handles ai
    board.drawboard(window);
    board.draw(window,Vector2i(10,10));
    return end(window,Vector2f(1000,1000),Vector2f(10000,10000));
}
