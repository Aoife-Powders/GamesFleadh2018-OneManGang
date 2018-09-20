#ifndef _HELP
#define _HELP
#include <SFML\Graphics.hpp>
#include "GlobalInclude.h"
#include "Xbox360Controller.h"
class Help
{
public:
	Help();
	~Help();

	void setUp(sf::Font&t_font);
	void render(sf::RenderWindow&t_window);
	void KeyIsPressed(Xbox360Controller &t_controller);
	void update(sf::Time);

	bool m_switch;

private:
	bool m_keyPressed;
	static const int M_MAX_TEXT = 4;

	sf::Text m_helpText[M_MAX_TEXT];
	sf::Texture m_backgroundTexture;
	sf::RectangleShape m_background;
	sf::Texture m_controllerTexture;
	sf::Sprite m_controllerSprite;
};
#endif