#include "MainMenu.h"

MainMenu::MainMenu()
{
	m_logoTexture.loadFromFile("assets//Art Assets//UI//Logo.png");
}

MainMenu::~MainMenu()
{
}

void MainMenu::setUp(sf::Font & t_font, sf::Texture &t_texture)
{
	for (int i = 0; i < M_MAX_BUTTON_NUMBER; i++)
	{
		m_label[i].setLabel();
		m_label[i].setPosition(sf::Vector2f(175, (i * 100) + 300));

		m_buttonText[i].setFont(t_font);
		m_buttonText[i].setString(M_TEXT[i]);
		m_buttonText[i].setFillColor(sf::Color::Black);
		m_buttonText[i].setStyle(sf::Text::Bold);
		m_buttonText[i].setStyle(sf::Text::Italic);
		m_buttonText[i].setCharacterSize(25);
		m_buttonText[i].setPosition(145, (i * 100) + 290);
	}

	m_background.setSize(sf::Vector2f(1920, 1080));
	m_background.setPosition(0, 0);
	m_background.setTexture(&t_texture);

	m_logo.setSize(sf::Vector2f(500, 400));
	m_logo.setPosition(800, 100);
	m_logo.setTexture(&m_logoTexture);

	moveButton(0);
}

void MainMenu::update(sf::Time & t_dtime, Xbox360Controller & t_controller)
{
	if (m_currentButton > 2)
	{
		m_currentButton = 0;
	}
	if (m_currentButton < 0)
	{
		m_currentButton = 2;
	}
	if (!m_moved)
	{
		if (t_controller.m_currentState.LeftThumbStick.y >= -15)
		{
			m_currentButton += 1;
			m_moved = true;
		}
		if (t_controller.m_currentState.LeftThumbStick.y <= 15)
		{
			m_currentButton -= 1;
			m_moved = true;
		}
	}

	if (t_controller.m_currentState.LeftThumbStick.y > 0 && t_controller.m_currentState.LeftThumbStick.y < 15 ||
		t_controller.m_currentState.LeftThumbStick.y < 0 && t_controller.m_currentState.LeftThumbStick.y > -15)
	{
		m_moved = false;
	}

	if (m_currentButton == 0)
	{
		moveButton(0);
		resetButton(1, 2);
		if (t_controller.m_currentState.A)
		{
			if (!t_controller.m_previousState.A)
			{
				t_controller.m_currentState.A = true;
				m_switchStart = true;
			}
		}
	}

	if (m_currentButton == 1)
	{
		moveButton(1);
		resetButton(0, 2);
		if (t_controller.m_currentState.A)
		{
			m_switchHelp = true;
		}
	}

	if (m_currentButton == 2)
	{
		moveButton(2);
		resetButton(0, 1);
		if (t_controller.m_currentState.A)
		{
			m_switchExit = true;
		}
	}
	//Animated title text
	if (m_logo.getPosition().y == 100)
	{
		m_fall = false;
	}
	if (m_logo.getPosition().y == 10 && !m_fall)
	{
		m_fall = true;
	}
	if (m_fall)
	{
		m_pos.y += 0.5;
	}
	if (!m_fall)
	{
		m_pos.y -= 0.5;
	}
	m_logo.setPosition(m_pos);

}

void MainMenu::render(sf::RenderWindow & t_window)
{
	t_window.draw(m_background);
	for (int i = 0; i < M_MAX_BUTTON_NUMBER; i++)
	{
		m_label[i].render(t_window);
		t_window.draw(m_buttonText[i]);
	}
	t_window.draw(m_logo);
}

void MainMenu::resetButton(int t_buttonNum, int t_buttonNum1)
{
	m_label[t_buttonNum].setLabel();
	m_label[t_buttonNum1].setLabel();

	m_buttonText[t_buttonNum].setFillColor(sf::Color::Black);

	m_buttonText[t_buttonNum1].setFillColor(sf::Color::Black);


	m_buttonText[t_buttonNum].setOutlineThickness(0);
	m_buttonText[t_buttonNum1].setOutlineThickness(0);
}

void MainMenu::moveButton(int t_buttonNum)
{
	m_buttonText[t_buttonNum].setFillColor(M_CYAN);
	m_label[t_buttonNum].labelPressed();
	m_buttonText[t_buttonNum].setOutlineColor(sf::Color::Black);
	m_buttonText[t_buttonNum].setOutlineThickness(5);
}
