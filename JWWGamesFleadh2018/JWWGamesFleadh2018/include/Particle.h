#ifndef PARTICLE
#define PARTICLE

#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"

class Particle
{
public:
	Particle();
	~Particle();

	void initialise(sf::Vector2f &t_position, sf::Vector2f &t_velocity, sf::Color &t_color, sf::Vector2f &t_size, int &t_maxTimer);

	int m_timer{ 0 };

	sf::Vector2f m_size{ 5,5 };
	sf::Vector2f m_velocity{ 4,4 };

	sf::Vector2f m_pos{ 0,0 };
	sf::Color m_color;
	int m_maxTimer{ 40 };
private:
	

};
#endif // !PARTICLE
