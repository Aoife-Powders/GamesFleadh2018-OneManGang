#ifndef PARTICLESYSTEM
#define PARTICLESYSTEM

#include "Particle.h"

const int MAX_PARTICLES{ 200 };
class ParticleSystem
{
public:
	ParticleSystem();
	~ParticleSystem();

	void initialise(sf::Vector2f t_position, sf::Vector2f &t_velocity, sf::Color t_color, sf::Vector2f &t_size, int t_maxTimer);
	void update();
	void render(sf::RenderWindow & t_window);

	Particle m_particle[MAX_PARTICLES];

private:
	sf::Vector2f m_positition;

	const int MAX_PARTICLES{ 200 };
	sf::RectangleShape m_particleShape;
};
#endif // !PARTICLESYSTEM

