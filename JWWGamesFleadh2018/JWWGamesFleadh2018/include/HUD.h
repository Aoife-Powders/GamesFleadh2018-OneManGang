#ifndef HUD
#define HUD

#include <SFML/Graphics.hpp>


class Hud
{
public:
	Hud(sf::Font & hudFont);

	void update(float t_health, float t_timer);
	void render(sf::RenderWindow &t_window);

private:
	// The font for this HUD.
	sf::Font m_textFont;

	// A simple background shape for the HUD.
	sf::RectangleShape m_hudBox;
	sf::RectangleShape m_pickupBar;
	sf::RectangleShape m_healthBar;

	sf::RectangleShape m_icons[2];

	sf::Texture m_hudTexture;
	sf::Texture m_healthIconTexture;
	sf::Texture m_bulletIconTexture;

};

#endif // !HUD