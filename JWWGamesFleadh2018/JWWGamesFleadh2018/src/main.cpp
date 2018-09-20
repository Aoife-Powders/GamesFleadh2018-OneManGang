#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif

#include <iostream>
#include "Game.h"
#include <stdlib.h>
#include <time.h>


int main()
{
	//set the seed fo the game
	srand(time(NULL));

	//declare variables
	sf::Texture playerText;
	sf::Texture mainMenuBackground;
	sf::Texture boxTexture;
	sf::Texture groundTexture;
	sf::Texture enemyWalkTexture;
	sf::Font font;

	//UI Textures
	mainMenuBackground.loadFromFile("assets//Art Assets//UI//Background.png");
	
	//load the font used for the game
	font.loadFromFile("assets//Font//Carnevalee Freakshow.ttf");
	
	//Platform Textures
	boxTexture.loadFromFile("assets//Art Assets//Box.png");
	groundTexture.loadFromFile("assets//Art Assets//cobbleSized.jpg");
	groundTexture.setRepeated(true);


	//Enemy Texture
	enemyWalkTexture.loadFromFile("assets//Art Assets//Animations//enemyWalk.png");

	//create a game object
	Game game(enemyWalkTexture,playerText, mainMenuBackground, boxTexture, groundTexture, font);
	game.run();

	//return 1 when the game has ended
	//for debugging
	return 1;
}