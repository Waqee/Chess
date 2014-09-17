#include "gamestates.h"
#include "global.h"
#include "gamestates.h"

using namespace sf;

//Similar to 2-player game with just 1 difference i.e the function computer turn is called in case of 2nd players turn
comvcom::comvcom(RenderWindow &wind) : GameState(wind)
{
    end=false;
    wind.clear();
    Chess.reset(wind);
    turn = 1;
	wind.display();
}

void comvcom::handle_events()
{
	temp=0;
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
        }
    }
}

void comvcom::logic()
{
    if(clock.getElapsedTime().asSeconds()>=1)
    {
        end = Chess.computerturn(window,3);
        turn = Chess.getturn();
        clock.restart();
		        temp=1;
    }
	if(temp==1)
		window.display();
}

void comvcom::render()
{
}
