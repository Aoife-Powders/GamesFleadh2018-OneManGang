
#ifndef BULLET
#define BULLET

#include "SFML\Graphics.hpp"
#include "GlobalInclude.h"
#include <iostream>

class Bullet
{
	friend class BulletLoop;
public:
	Bullet() { m_body.setSize(sf::Vector2f(2, 2)); m_body.setFillColor(sf::Color::Black); }

	void init(sf::Texture const & t_texture, double t_x, double t_y);
	bool update(sf::Time const &t_dTime);

	bool inUse() const;

	void setRotation(double t_angle);

	void checkCollision(sf::RectangleShape t_rect[], const int T_ARRAY_SIZE);

	bool checkBodyCollision(sf::RectangleShape &t_rectangle, int t_facing);


private:
	
	static constexpr double M_MAX_SPEED{ 300.0 };

	double m_speed{ 0.0 };

	sf::Sprite m_bullet;

	sf::IntRect m_bulletRect{};

	bool Bullet::isOnScreen(sf::Vector2f position) const;
	sf::RectangleShape m_body;
};

#endif