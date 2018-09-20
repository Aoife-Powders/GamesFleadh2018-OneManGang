#include "Particle.h"


Particle::Particle()
{
}

Particle::~Particle()
{
	/*delete this;*/
}

void Particle::initialise(sf::Vector2f &t_position, sf::Vector2f &t_velocity, sf::Color &t_color, sf::Vector2f &t_size, int &t_maxTimer)
{
	m_pos = t_position;
	m_size = t_size;
	m_color = t_color;

	m_velocity = t_velocity;
	m_timer = (rand() % t_maxTimer) + 1;
}
