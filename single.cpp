#include "gamestates.h"
#include "global.h"

using namespace sf;

//Similar to intro screen but displays different buttons
Single::Single(RenderWindow &wind) : GameState(wind)
{
}

void Single::handle_events()
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
                set_next_state( STATE_EXIT );
            break;

            case Event::MouseButtonReleased:
            if(event.mouseButton.button==Mouse::Left)
            {
                if(Mouse::getPosition(window).x>=45 && Mouse::getPosition(window).x<=320 && Mouse::getPosition(window).y>=295 && Mouse::getPosition(window).y<=350)
                    set_next_state( STATE_GAME );
                else if(Mouse::getPosition(window).x>=45 && Mouse::getPosition(window).x<=360 && Mouse::getPosition(window).y>=350 && Mouse::getPosition(window).y<=405)
                    set_next_state( STATE_COMPUTER );
            }
            break;
        }
    }
}

void Single::logic()
{
}

void Single::render()
{
    Texture ptexture;
    Sprite background;

    ptexture.loadFromFile("ground.png");
    background.setTexture(ptexture);

    window.draw(background);

    Font font;
    font.loadFromFile("acmesa.TTF");

    String sentence ;

    sentence = "Human v Human";
    Text text1 (sentence,font,30);
    text1.setPosition(50,300);
    if(Mouse::getPosition(window).x>=45 && Mouse::getPosition(window).x<=320 && Mouse::getPosition(window).y>=295 && Mouse::getPosition(window).y<=350)
        text1.setColor(Color::Red);
    else
        text1.setColor(Color::Blue);

    sentence = "Human v Computer";
    Text text2 (sentence,font,30);
    text2.setPosition(50,355);
    if(Mouse::getPosition(window).x>=45 && Mouse::getPosition(window).x<=360 && Mouse::getPosition(window).y>=350 && Mouse::getPosition(window).y<=405)
        text2.setColor(Color::Red);
    else
        text2.setColor(Color::Blue);

    window.draw(text1);
    window.draw(text2);
	window.display();
}
