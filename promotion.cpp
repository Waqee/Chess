#include "gamestates.h"
#include "global.h"

using namespace sf;

//Game state that handles the window appearing when a promotion is to be done
Promotion::Promotion(RenderWindow &wind) : GameState(wind)
{
}


void Promotion::handle_events()
{
    while(window.pollEvent(event))
    {
        switch (event.type)
        {
            case Event::Closed:
            set_next_state( STATE_EXIT );
            break;

            //Checks co ordinates for indicating the type to which promotion to be done
            case Event::MouseButtonReleased:
            if(event.mouseButton.button==Mouse::Left)
            {
                if(Mouse::getPosition(window).x>=100 && Mouse::getPosition(window).x<200 && Mouse::getPosition(window).y>=250 && Mouse::getPosition(window).y<=350)
                {
                    tempstate->promotion=2;
                    set_next_state( STATE_GAME );
                }
                else if(Mouse::getPosition(window).x>=200 && Mouse::getPosition(window).x<300 && Mouse::getPosition(window).y>=250 && Mouse::getPosition(window).y<=350)
                {
                    tempstate->promotion=3;
                    set_next_state( STATE_GAME );
                }
                else if(Mouse::getPosition(window).x>=300 && Mouse::getPosition(window).x<400 && Mouse::getPosition(window).y>=250 && Mouse::getPosition(window).y<=350)
                {
                    tempstate->promotion=4;
                    set_next_state( STATE_GAME );
                }
                else if(Mouse::getPosition(window).x>=400 && Mouse::getPosition(window).x<500 && Mouse::getPosition(window).y>=250 && Mouse::getPosition(window).y<=350)
                {
                    tempstate->promotion=5;
                    set_next_state( STATE_GAME );
                }
            }
            break;
        }
    }
}

void Promotion::logic()
{
}

void Promotion::render()
{
    //Objects which store the contents of each  piece image
    Texture ptexture1,ptexture2,ptexture3,ptexture4,ptexture5;
    Sprite rook;
    Sprite knight;
    Sprite bishop;
    Sprite queen;
    Sprite tile;

    //loads the gray tile
    if(!ptexture5.loadFromFile("promotion.jpg"))
       cout<<"couldnt load tile";
    tile.setTexture(ptexture5);
	tile.setColor(Color(100,100,100,200));
    tile.setPosition(50,190);
    tile.setScale(1.7,1);

    //loads font and shows text PROMOTE TO
    Font font;
    font.loadFromFile("acmesa.TTF");
    sf::String sentence;
    sentence = "PROMOTE TO ";
    Text text(sentence,font,40);
    text.setPosition(150,200);
    text.setColor(Color::White);

    //Displays the 4 types to which pawn can be promoted to

    if(turn==1)
            ptexture1.loadFromFile("sprite.png",IntRect(0,0,75,75));
    else
            ptexture1.loadFromFile("sprite.png",IntRect(0,75,75,75));
    rook.setTexture(ptexture1);
    rook.setPosition(100,250);
    rook.setScale(1.3,1.3);

    if (turn == 1)
        ptexture2.loadFromFile("sprite.png",IntRect(150,0,75,75));
    else
        ptexture2.loadFromFile("sprite.png",IntRect(150,75,75,75));
    knight.setTexture(ptexture2);
    knight.setPosition(200,250);
    knight.setScale(1.3,1.3);

    if (turn == 1)
        ptexture3.loadFromFile("sprite.png",IntRect(75,0,75,75));
    else
        ptexture3.loadFromFile("sprite.png",IntRect(75,75,75,75));
    bishop.setTexture(ptexture3);
    bishop.setPosition(300,250);
    bishop.setScale(1.3,1.3);

    if (turn == 1)
        ptexture4.loadFromFile("sprite.png",IntRect(300,0,75,75));
    else
        ptexture4.loadFromFile("sprite.png",IntRect(300,75,75,75));
    queen.setTexture(ptexture4);
    queen.setPosition(400,250);
    queen.setScale(1.3,1.3);

    window.clear();

    //also updates the game while promotion is being handled
    tempstate->Chess.update(window,Vector2f(100,100),Vector2f(100,100),tempstate->clock);


    //Draws the pieces, text and tile on window
    window.draw(tile);
    window.draw(text);
    window.draw(rook);
    window.draw(knight);
    window.draw(bishop);
    window.draw(queen);

	window.display();
}
