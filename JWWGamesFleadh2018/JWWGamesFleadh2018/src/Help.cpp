#include "Help.h"



Help::Help()
{
	m_controllerTexture.loadFromFile("assets//Art Assets//UI//xbox360_controller.png");
	m_backgroundTexture.loadFromFile("assets//Art Assets//UI//Background.png");
}


Help::~Help()
{
}

void Help::setUp(sf::Font &t_font)
{
	for (int i = 0; i < M_MAX_TEXT; i++)
	{
		m_helpText[i].setCharacterSize(24);
		m_helpText[i].setFillColor(sf::Color::Black);
		m_helpText[i].setStyle(sf::Text::Italic);
		m_helpText[i].setFont(t_font);
	}
	m_helpText[0].setPosition(1200, 50);
	m_helpText[0].setString("RT to Shoot");
	m_helpText[1].setPosition(1350, 280);
	m_helpText[1].setString("A to Jump");
	m_helpText[2].setPosition(475, 200);
	m_helpText[2].setString("Left Analog \n to Move");
	m_helpText[3].setPosition(900, 500);
	m_helpText[3].setString("Start to Pause");

	m_controllerSprite.setTexture(m_controllerTexture);
	m_controllerSprite.setPosition(sf::Vector2f(460,50));
	m_background.setTexture(&m_backgroundTexture);
	m_background.setPosition(0, 0);
	m_background.setSize(sf::Vector2f(1920, 1080));
}

void Help::render(sf::RenderWindow &t_window)
{
	t_window.draw(m_background);
	t_window.draw(m_controllerSprite);
	for (int i = 0; i < M_MAX_TEXT; i++)
	{
		t_window.draw(m_helpText[i]);
	}
}

void Help::KeyIsPressed(Xbox360Controller &t_controller)
{
	if (t_controller.m_currentState.B)
	{
		m_keyPressed = true;
	}
}

void Help::update(sf::Time)
{
	if (m_keyPressed == true)
	{
		m_switch = true;
	}
	m_keyPressed = false;
}
