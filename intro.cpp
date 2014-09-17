#include "gamestates.h"
#include "global.h"

using namespace sf;

//First intro screen display single player multiplayer options
Title::Title(RenderWindow &wind) : GameState(wind)
{
}

void Title::handle_events()
{
    while(window.pollEvent(event))
    {
        switch (event.type)
        {
            case Event::Closed: //Checks of game is closed
            set_next_state( STATE_EXIT );
            break;

            case Event::KeyPressed: //Checks if a key is pressed
            if(event.key.code == Keyboard::Escape) //Goes to main menu if escape is pressed
                set_next_state( STATE_EXIT );
            break;

            //Checks mouse position and chages state according the the button pressed
            case Event::MouseButtonReleased:
            if(event.mouseButton.button==Mouse::Left)
            {
                //Location of a button is checked by its co ordinates
                if(Mouse::getPosition(window).x>=45 && Mouse::getPosition(window).x<=360 && Mouse::getPosition(window).y>=295 && Mouse::getPosition(window).y<=350)
                    set_next_state( STATE_SINGLE );
                else if(Mouse::getPosition(window).x>=45 && Mouse::getPosition(window).x<=360 && Mouse::getPosition(window).y>=350 && Mouse::getPosition(window).y<=405)
                    set_next_state( STATE_MULTI_TITLE1 );
            }
            break;
        }
    }
}

void Title::logic()
{
}

void Title::render()
{
    //Draws the back ground image
    Texture ptexture;
    Sprite background;
    ptexture.loadFromFile("ground.png");
    background.setTexture(ptexture);

    window.draw(background);

    //loads font
    Font font;
    font.loadFromFile("acmesa.TTF");

    String sentence;

    //Displays text on the screen in form of button
    sentence = "Singleplayer Game";
    Text text1 (sentence,font,30);
    text1.setPosition(50,300);
    //If mouse is in co ordinates of any button then it changes color
    if(Mouse::getPosition(window).x>=45 && Mouse::getPosition(window).x<=360 && Mouse::getPosition(window).y>=295 && Mouse::getPosition(window).y<=350)
        text1.setColor(Color::Red);
    else
        text1.setColor(Color::Blue);

    sentence = "Multiplayer Game";
    Text text2 (sentence,font,30);
    text2.setPosition(50,355);
    if(Mouse::getPosition(window).x>=45 && Mouse::getPosition(window).x<=360 && Mouse::getPosition(window).y>=350 && Mouse::getPosition(window).y<=405)
        text2.setColor(Color::Red);
    else
        text2.setColor(Color::Blue);

    //Drawing both buttons or text on screen
    window.draw(text1);
    window.draw(text2);
	        window.display();
}
