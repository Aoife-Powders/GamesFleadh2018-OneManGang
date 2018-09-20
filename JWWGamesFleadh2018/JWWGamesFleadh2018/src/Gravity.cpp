#include "Gravity.h"

sf::Vector2f Gravity::s_gravity = sf::Vector2f(0, 9.8f);

void Gravity::applyGrav(sf::Vector2f &t_movement, sf::Time t_dTime)
{
	t_movement.y = t_movement.y + s_gravity.y * t_dTime.asSeconds();
}
