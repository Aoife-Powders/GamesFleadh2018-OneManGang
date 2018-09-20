#include "UiLibrary.h"

UiLibrary::UiLibrary()
{
	if (!m_labelTexture.loadFromFile("assets\\Art Assets\\UI\\buttonLong_beige.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}

	if (!m_labelPressedTexture.loadFromFile("assets\\Art Assets\\UI\\buttonLong_beige_pressed.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}
}

UiLibrary::~UiLibrary()
{
}

void UiLibrary::render(sf::RenderWindow &t_window)
{
	t_window.draw(m_uiSprite);
}

void UiLibrary::setLabel()
{
	m_uiSprite.setTexture(m_labelTexture);
	m_uiSprite.setOrigin(82.5, 15);
}

void UiLibrary::setRadioButton()
{
	m_uiSprite.setTexture(m_radioButtonTexture);
}

void UiLibrary::setCheckBox()
{
	m_uiSprite.setTexture(m_checkBoxTexture);
}

void UiLibrary::setPosition(sf::Vector2f t_position)
{
	m_uiSprite.setPosition(t_position);
}

void UiLibrary::labelPressed()
{
	m_uiSprite.setTexture(m_labelPressedTexture);
	m_uiSprite.setOrigin(82.5, 15);
}
