#ifndef UILIBRARY
#define UILIBRARY

#include <SFML\Graphics.hpp>
#include <iostream>

class UiLibrary
{
public:
	UiLibrary();
	~UiLibrary();
	void render(sf::RenderWindow &t_window);
	void setLabel();
	void setRadioButton();
	void setCheckBox();
	void setPosition(sf::Vector2f t_position);
	void labelPressed();

private:
	sf::Texture m_labelTexture;
	sf::Texture m_labelPressedTexture;
	sf::Texture m_radioButtonTexture;
	sf::Texture m_checkBoxTexture;

	sf::Sprite m_uiSprite;
	sf::RectangleShape m_labelRectangle;
};

#endif // !UILIBRARY

