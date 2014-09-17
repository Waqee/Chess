#include "gamestates.h"
#include "global.h"

using namespace sf;

//Actual 2-player game
Game::Game(RenderWindow &wind) : GameState(wind),status(0)
{
    //sets end variable to false indicating game is not finished
    end=false;
    wind.clear(); //Clears window
    Chess.reset(wind); //Resets the chess game
	wind.display();
}

void Game::handle_events()
{
	temp=0;
    while(window.pollEvent(event))
    {
        switch (event.type)
        {
            //closes window
            case Event::Closed:
            set_next_state( STATE_EXIT );
            break;

            //escapes current game state
            case Event::KeyPressed:
            if(event.key.code == Keyboard::Escape)
                set_next_state( STATE_TITLE );

            //if games has ended and user presses a button then goes to title screen
            case Event::MouseButtonPressed:
            if(event.mouseButton.button==Mouse::Left && end == true)
                set_next_state(STATE_TITLE);

            //if a button is pressed any where on screen then puts a variable status to true indicating a something has being dragged and stores the location of click
            else if(event.mouseButton.button==Mouse::Left && end == false)
            {
                status=1;
                fixedpos.x=Mouse::getPosition(window).x;
                fixedpos.y=Mouse::getPosition(window).y-50;
            }
            break;

            //When mouse button is released checks the current position of mouse then class a function move of chess class to validate if move was valid
            case Event::MouseButtonReleased:
            if(event.mouseButton.button==Mouse::Left && end == false )
            {
                status=0; //Reverting variable to 0 indicating that mouse button is released to anything being dragged is dropped
                end = Chess.move(window,Vector2f(Mouse::getPosition(window).x,Mouse::getPosition(window).y-50),fixedpos,clock);
                turn = Chess.getturn(); //sets turn
				temp=1;
            }
            break;
        }
    }
}

void Game::logic()
{
    //Checks if there is promotion and calls the promotion if function if some piece can be promoted
    if(promotion!=0)
    {
        Chess.promotion(window,promotion);
        clock.restart();
        promotion=0;
        return;
    }

    //Calss time function to refresh time every 1 second
    if(clock.getElapsedTime().asSeconds()>=1 && end == false)
	{
            Chess.time(window,clock,Vector2f(10000,10000));
			        temp=1;
	}

    //Checking the variable if it is true meaning something is being dragged so calling update function to continously update the position of piece
    if (status==1 )
    {
        Vector2f position(Mouse::getPosition(window).x,Mouse::getPosition(window).y-100);
        Chess.update(window,position,fixedpos,clock);
		temp=1;
    }
	if(temp==1)
		window.display();
}

void Game::render()
{
}
