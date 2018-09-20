
#ifndef BULLET_LOOP
#define BULLET_LOOP

#include "SFML\Graphics.hpp"
#include <array>
#include "Bullet.h"

class BulletLoop
{
public:
	BulletLoop() = default;

	//makes a new projectile, sets the position of the projectile
	void create(sf::Texture const & t_texture, double t_x, double t_y);

	void update(sf::Time const &t_dTime, sf::RectangleShape t_platform[], int const T_MAX_PLAT, sf::RectangleShape t_box[], int const T_MAX_BOX);

	void render(sf::RenderWindow &t_window);

	void setRotation(double t_angle);

	bool checkBodyCollision(sf::RectangleShape &t_rectangle, int t_facing);
private:
	static const int M_POOL_SIZE = 10;

	std::array<Bullet, M_POOL_SIZE> m_bullets;

	int m_nextAvailable{ 0 };

	bool m_poolFull{ false };

};

#endif