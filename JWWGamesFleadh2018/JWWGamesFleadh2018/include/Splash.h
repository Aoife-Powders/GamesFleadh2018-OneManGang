#ifndef _SPLASH
#define _SPLASH
#include <SFML\Graphics.hpp>
#include "GlobalInclude.h"
#include "Xbox360Controller.h"

class Splash
{
public:
	Splash();
	~Splash();

	void setUp();
	void render(sf::RenderWindow&t_window);
	void KeyIsPressed(Xbox360Controller &t_controller);
	void update(sf::Time);
	bool m_switch;
private:
	//if input is taken
	bool m_keyPressed;

	sf::Texture m_logoTexture;
	sf::Sprite m_logoSprite;
	
	int m_timer = 0;
};
#endif