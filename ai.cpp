#include "gamestates.h"
#include "global.h"

using namespace sf;

//Similar to 2-player game with just 1 difference i.e the function computer turn is called in case of 2nd players turn
AI::AI(RenderWindow &wind) : GameState(wind),status(0)
{
    end=false;
    wind.clear();
    Chess.reset(wind);
    turn = 1;
	wind.display();
}

void AI::handle_events()
{
	temp=0;
    //Calls the AI function in case its players 2s turn
    if(turn==2 && end==false)
    {
        end = Chess.computerturn(window,3);
        turn = Chess.getturn();
        clock.restart();
		        temp=1;
    }

    while(window.pollEvent(event))
    {
        switch (event.type)
        {
            case Event::Closed:
            set_next_state( STATE_EXIT );
            break;

            case Event::KeyPressed:
            if(event.key.code == Keyboard::Escape)
                set_next_state( STATE_TITLE );

            case Event::MouseButtonPressed:
            if(event.mouseButton.button==Mouse::Left && end == true)
                set_next_state(STATE_TITLE);
            else if(event.mouseButton.button==Mouse::Left && end == false && turn==1)
            {
                status=1;
                fixedpos.x=Mouse::getPosition(window).x;
                fixedpos.y=Mouse::getPosition(window).y-50;
            }
            break;

            case Event::MouseButtonReleased:
            if(event.mouseButton.button==Mouse::Left && end == false && turn==1)
            {
                status=0;
                end = Chess.move(window,Vector2f(Mouse::getPosition(window).x,Mouse::getPosition(window).y-50),fixedpos,clock);
                turn = Chess.getturn();
				       temp=1;
            }

            break;
        }
    }
}

void AI::logic()
{
    if(promotion!=0)
    {
        Chess.promotion(window,promotion);
        clock.restart();
        promotion=0;
        return;
    }
    if(clock.getElapsedTime().asSeconds()>=1 && end == false)
	{
            Chess.time(window,clock,Vector2f(10000,10000));
			        temp=1;
	}

    if (status==1 )
    {
        Vector2f position(Mouse::getPosition(window).x,Mouse::getPosition(window).y-100);
        Chess.update(window,position,fixedpos,clock);
		        temp=1;
    }
	if(temp==1)
		window.display();
}

void AI::render()
{
}
