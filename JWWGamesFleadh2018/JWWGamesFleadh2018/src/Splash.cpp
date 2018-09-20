#include "Splash.h"


Splash::Splash()
{
}

Splash::~Splash()
{
}

void Splash::setUp()
{
	if (!m_logoTexture.loadFromFile("assets//Art Assets//Logos//jww.png"))
	{
		std::cout << "no texture" << std::endl;
	}

	m_logoSprite.setTexture(m_logoTexture);
	m_logoSprite.setPosition(600, 200);
}

void Splash::render(sf::RenderWindow &t_window)
{
	t_window.draw(m_logoSprite);
}

void Splash::KeyIsPressed(Xbox360Controller &t_controller)
{

	if (t_controller.m_currentState.A)
	{
		m_keyPressed = true;
	}

}

void Splash::update(sf::Time time)
{
	m_timer++;
	if(m_timer > 200)
	{ 
		m_switch = true;
	}
	/*if (m_keyPressed == true)
	{
		m_switch = true;
	}
	m_keyPressed = false;*/
}
