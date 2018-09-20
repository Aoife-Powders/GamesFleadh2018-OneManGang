#include "HUD.h"

Hud::Hud(sf::Font & hudFont)
	: m_textFont(hudFont)
{



	//Setting up our hud properties 
	m_hudTexture.loadFromFile("assets//Art Assets//UI//HUD.png");
	m_hudBox.setSize(sf::Vector2f(100, 30));
	m_hudBox.setTexture(&m_hudTexture);
	m_hudBox.setTextureRect(sf::IntRect(0, 0, 100, 30));
	m_hudBox.setFillColor(sf::Color(255, 255, 255, 255)); //transparent red
	m_hudBox.setPosition(0, 810);

	m_bulletIconTexture.loadFromFile("assets//Art Assets//UI//gunIcon.png");
	m_healthIconTexture.loadFromFile("assets//Art Assets//UI//healthIcon.png");

	m_icons[0].setPosition(m_hudBox.getPosition().x + 30, m_hudBox.getPosition().y + 17);
	m_icons[1].setPosition(m_hudBox.getPosition().x + 32, m_hudBox.getPosition().y + 7);

	m_icons[0].setTexture(&m_bulletIconTexture);
	m_icons[1].setTexture(&m_healthIconTexture);

	for (int i = 0; i < 2; i++)
	{
		m_icons[i].setSize(sf::Vector2f(8,8));
	}
	
	//Health bar SetUp
	m_pickupBar.setSize(sf::Vector2f(50, 4));
	m_pickupBar.setFillColor(sf::Color(sf::Color::Blue));
	m_pickupBar.setPosition(m_hudBox.getPosition().x + 42, m_hudBox.getPosition().y + 19);


	m_healthBar.setSize(sf::Vector2f(50, 4));
	m_healthBar.setFillColor(sf::Color(sf::Color::Red)); 
	m_healthBar.setPosition(m_hudBox.getPosition().x + 42, m_hudBox.getPosition().y + 9);
}

void Hud::update(float t_health, float t_timer)
{
	m_healthBar.setSize(sf::Vector2f(t_health *.5, 4));
	if (t_health <= 0)
	{
		m_healthBar.setSize(sf::Vector2f(0, 4));
	}
	m_pickupBar.setSize(sf::Vector2f((t_timer * .1) * .5, 4));

}

void Hud::render(sf::RenderWindow &t_window)
{
	t_window.draw(m_hudBox);
	t_window.draw(m_pickupBar);
	t_window.draw(m_healthBar);

	for (int i = 0; i < 2; i++)
	{
		t_window.draw(m_icons[i]);
	}

}
