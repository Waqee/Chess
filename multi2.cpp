#include "gamestates.h"
#include "global.h"

using namespace sf;

Multi2::Multi2(RenderWindow &wind,int pl) : GameState(wind)
{
    //gets the ip addresses again for showing
    ip[0] = "Local ip : ";
    ip[0] += IpAddress::getLocalAddress().toString();

    ip[1] = "Public ip : ";
    ip[1] += IpAddress::getPublicAddress().toString();

    player=pl;
    //sets both listner and other socket to non-blocking so that the functions doesnt wait for connection to return
    listener.setBlocking(false);
    socket.setBlocking(false);
    //in case of client display a gray box on which user enters ip address
    if(pl==2)
    {
        rect.setPosition(50,350);
        rect.setSize(Vector2f(300,50));
        rect.setFillColor(Color(200,200,200));
    }
}

void Multi2::handle_events()
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
            if(event.key.code == Keyboard::Return && player==2)
            {
                //if user entered and ip address and presses enter then checks if the address can be connected and changes state
                if(socket.connect(IpAddress(sentence2),6555)==Socket::NotReady || socket.connect(IpAddress(sentence2),6555)==Socket::Done)
                    set_next_state( STATE_MULTIPLAYER );
                else //other wise removes the witten ip address
                    sentence2="";
            }
            break;

            //Used to enter text into the ip address box
            case Event::TextEntered:
            if(event.text.unicode >= 32 && event.text.unicode <= 126 && player==2)
                sentence2 += (char)event.text.unicode;
            else if(event.text.unicode == 8 && sentence2.getSize() > 0 && player==2)
                sentence2.erase(sentence2.getSize() - 1);
            break;
        }
    }
}

void Multi2::logic()
{
}

void Multi2::render()
{
    //if the user made the server then constatly listens on the port but as it is non-blocking so returns as soon as it is called with a vlue indicating if connection was successful
    if(player == 1 )
    {
        listener.listen(6555);
        if(listener.accept(socket)==Socket::Done) //if connections successful then changes game state
            set_next_state( STATE_MULTIPLAYER );
    }

    //loads back ground
    Texture ptexture;
    Sprite background;
    ptexture.loadFromFile("ground.png");
    background.setTexture(ptexture);

    window.draw(background);

    Font font;
    font.loadFromFile("acmesa.TTF");

    String sentence ;

    //displays text
    Text text3 (ip[0],font,30);
    text3.setPosition(50,100);

    Text text4 (ip[1],font,30);
    text4.setPosition(50,150);

    //if the user is server then displays sentence waiting else displays sentence enter host ip
    if(player==1)
        sentence = "Waiting ....";
    else
        sentence = "Enter host ip";
    Text text1 (sentence,font,30);
    text1.setPosition(50,300);
    text1.setColor(Color(200,200,200));

    //if its a client then displays the text box and allows text to be entered
    if(player==2)
    {
        Text text2(sentence2,font,30);
        text2.setPosition(50,350);
        text2.setColor(Color::Black);
        window.draw(rect);
        window.draw(text2);
    }

    window.draw(text1);
    window.draw(text3);
    window.draw(text4);
	window.display();
}
