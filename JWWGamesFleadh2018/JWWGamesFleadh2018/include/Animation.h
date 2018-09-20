/// <summary>
/// @ Author: Eoin Abbey Maher
/// @ Date : 05/02/2018
/// brief: Animation Class to update frames and Images
/// </summary>

#include <SFML\Graphics.hpp>
#include <iostream>

#ifndef ANIMATION
#define ANIMATION

class Animation
{
public:
	
	Animation(sf::RectangleShape & t_shape, int t_noFrames, sf::Texture & t_texture, sf::IntRect & t_intRect);
	~Animation();

	void update();
	void reset();

	int m_delay{ 7 };
	int m_timer{ 0 };
	int m_currentFrame{ 0 };
	

	sf::RectangleShape & m_body;
	sf::Texture & m_texture;
	sf::IntRect m_intrect { 0,0,0,0 };
	float m_frames{ 0.0f };

};
#endif // !ANIMATION
