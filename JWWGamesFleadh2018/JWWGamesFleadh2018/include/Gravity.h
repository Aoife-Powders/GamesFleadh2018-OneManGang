#ifndef GRAVITY
#define GRAVITY

#include <SFML\Graphics.hpp>
#include <iostream>

struct Gravity
{
public:
	static sf::Vector2f s_gravity;
	static void applyGrav(sf::Vector2f &t_movement, sf::Time t_dTime);

};


#endif