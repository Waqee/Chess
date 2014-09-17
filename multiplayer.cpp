#include "gamestates.h"
#include "global.h"

using namespace sf;

//Same as 2-player game except for some changes to make multiplayer
Multiplayer::Multiplayer(RenderWindow &wind,int pl) : GameState(wind),status(0)
{
    end=false; //End is false
    player = pl;
    turn=1; //Games starts with player 2's turn which jst sends a blank move to player 1 indicating connection successful
    wind.clear();
    Chess.reset(wind,pl);
	wind.display();
}

void Multiplayer::handle_events()
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

            //Same as 2-player game but the user can only press on window if its his turn
            if(event.mouseButton.button==Mouse::Left && end == false && player == turn)
            {
                status=1;
                fixedpos.x=Mouse::getPosition(window).x;
                fixedpos.y=Mouse::getPosition(window).y-50;
            }
            break;

            case Event::MouseButtonReleased:
            if(event.mouseButton.button==Mouse::Left && end == false && player==turn)
            {
                status=0;
                end = Chess.move(window,Vector2f(Mouse::getPosition(window).x,Mouse::getPosition(window).y-50),fixedpos,clock);
				temp=1;
            }

            break;
        }
    }
}

void Multiplayer::logic()
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

    if (status==1 && end == false)
    {
        Vector2f position(Mouse::getPosition(window).x,Mouse::getPosition(window).y-100);
        Chess.update(window,position,fixedpos,clock);
	    temp=1;
    }

    int tester;

    //If the turn has changed that means the player made a move so we send the move to the other player by our send function
    if(turn!=Chess.getturn())
    {
        turn=Chess.getturn();
        Chess.sender(packet);
        socket.send(packet);
    }

    //If the player disconnected then showing the disconnected message and ending the game
    if(socket.receive(packet)==Socket::Disconnected)
    {
        end=true;
        Chess.disconnected(window);
    }
    else if (packet>>tester) //If its not the player turn then he constantly waits for data to arrive which is indicated by wether the packet recievec contains anything
    {
        window.clear(); //clears window
        Chess.receiver(window,packet); //recieves packet
        turn=Chess.getturn(); //changes turn
        clock.restart(); //restarts clock
		temp=1;
    }
	if(temp==1)
		window.display();
}

void Multiplayer::render()
{
}
