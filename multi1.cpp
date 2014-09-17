#include "gamestates.h"
#include "global.h"

using namespace sf;

//The first multiplayer title screen showing server and client buttons
Multi1::Multi1(RenderWindow &wind) : GameState(wind)
{
    //Gets the local and public ip of computer and stores in a string
    ip[0] = "Local ip : ";
    ip[0] += IpAddress::getLocalAddress().toString();

    ip[1] = "Public ip : ";
    ip[1] += IpAddress::getPublicAddress().toString();
}

void Multi1::handle_events()
{
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
            break;

            case Event::MouseButtonReleased:
            if(event.mouseButton.button==Mouse::Left)
            {
                //Changes the game state according to the button pressed
                if(Mouse::getPosition(window).x>=45 && Mouse::getPosition(window).x<=180 && Mouse::getPosition(window).y>=295 && Mouse::getPosition(window).y<=350)
                {
                    set_next_state( STATE_MULTI_TITLE2 );
                    player = 1; //if server is pressed then the player is 1
                }
                else if(Mouse::getPosition(window).x>=45 && Mouse::getPosition(window).x<=180 && Mouse::getPosition(window).y>=350 && Mouse::getPosition(window).y<=405)
                {
                    set_next_state( STATE_MULTI_TITLE2 );
                    player = 2; //if the client button is pressed the the player is 2nd player
                }
            }
            break;
        }

    }
}

void Multi1::logic()
{
}

void Multi1::render()
{
    //loads background
    Texture ptexture;
    Sprite background;
    ptexture.loadFromFile("ground.png");
    background.setTexture(ptexture);

    window.draw(background);

    Font font;
    font.loadFromFile("acmesa.TTF");

    String sentence;

    //displays both ip addresses of computer on screen
    Text text3 (ip[0],font,30);
    text3.setPosition(50,150);

    Text text4 (ip[1],font,30);
    text4.setPosition(50,200);

    //makes the server button and changes color if mouse is over it
    sentence = "Server";
    Text text1 (sentence,font,30);
    text1.setPosition(50,300);
    if(Mouse::getPosition(window).x>=45 && Mouse::getPosition(window).x<=180 && Mouse::getPosition(window).y>=295 && Mouse::getPosition(window).y<=350)
        text1.setColor(Color::Red);
    else
        text1.setColor(Color::Blue);

    //similarly makes the client button
    sentence = "Client";
    Text text2 (sentence,font,30);
    text2.setPosition(50,355);
    if(Mouse::getPosition(window).x>=45 && Mouse::getPosition(window).x<=180 && Mouse::getPosition(window).y>=350 && Mouse::getPosition(window).y<=405)
        text2.setColor(Color::Red);
    else
        text2.setColor(Color::Blue);

    window.draw(text1);
    window.draw(text2);
    window.draw(text3);
    window.draw(text4);
	        window.display();
}
