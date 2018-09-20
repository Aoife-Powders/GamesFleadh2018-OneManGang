#ifndef MAINMENU_
#define MAINMENU_
#include <SFML\Graphics.hpp>
#include "Xbox360Controller.h"
#include "UiLibrary.h"

class MainMenu
{
public:
	MainMenu();
	~MainMenu();

	void setUp(sf::Font &t_font, sf::Texture &t_texture);
	void update(sf::Time &t_dtime, Xbox360Controller & t_controller);
	void render(sf::RenderWindow &t_window);

	//Public bools used for switching the screen when a button is pressed
	bool m_switchStart = false;
	bool m_switchExit = false;
	bool m_switchHelp = false;

private:
	static const int M_MAX_BUTTON_NUMBER = 3;
	const sf::Color M_CYAN{ 43, 143, 155 };
	const sf::String M_TEXT[5] = { "Start","Help", "Exit" };
	sf::RectangleShape m_button[M_MAX_BUTTON_NUMBER];
	sf::Text m_buttonText[M_MAX_BUTTON_NUMBER];
	sf::RectangleShape m_background;
	sf::Texture m_logoTexture;
	sf::RectangleShape m_logo;
	void moveButton(int t_buttonNum);
	void resetButton(int t_buttonNum, int t_buttonNum1);
	bool m_moved = false;
	int m_currentButton = 0;
	UiLibrary m_label[M_MAX_BUTTON_NUMBER];
	sf::Vector2f m_pos = { 800, 100 };
	//bool for title animation
	bool m_fall = true;
};

#endif // !MAINMENU_
