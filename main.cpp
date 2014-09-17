#include <SFML/Graphics.hpp> //SFML Graphics library
#include <iostream>

#include "gamestates.h" //Including the file which contains the game state i.e main menu,game etc
#include "global.h" //Includes files used for changing the current game state
#include <Windows.h>

using namespace std;

int main()
{
	FreeConsole();
	sf::RenderWindow window (sf::VideoMode(600,650),"Chess Game",sf::Style::Close); //Used to make SFML window

	sf::Image icon;
	icon.loadFromFile("icon.png");

	window.setIcon(icon.getSize().x,icon.getSize().y,icon.getPixelsPtr());

    window.setFramerateLimit(20); //Sets refresh rate to 20 times per second

    currentState = new Title (window); //Makes a new state that is of the type titles screen i.e first main menu

    while( stateID != STATE_EXIT ) //Game loop while the state is not equal to exit
    {
        //Calling respective funtions of polym
        currentState->handle_events();
        currentState->logic();
        change_state(window);
        currentState->render();

    }
    delete currentState; //If user has closed window and game loop ended than deleting the last game state
    return 0;
}
