#include "..\include\BulletLoop.h"

void BulletLoop::create(sf::Texture const & t_texture, double t_x, double t_y)
{
	//if no projectiles available, simply re-use the next in sequence.
	if (m_poolFull)
	{
		m_nextAvailable = (m_nextAvailable + 1) % M_POOL_SIZE;
	}

	m_bullets.at(m_nextAvailable).init(t_texture, t_x, t_y);

	update(sf::Time::Zero, nullptr, 20,nullptr, 20);
}

void BulletLoop::update(sf::Time const & t_dTime, sf::RectangleShape t_platform[], int const T_MAX_PLAT, sf::RectangleShape t_box[], int const T_MAX_BOX)
{
	int activeCount = 0;
	m_poolFull = false;
	for (int i = 0; i < M_POOL_SIZE; i++)
	{
		//loop through all of the barriers to see if there is a collision
		if (t_platform != nullptr)
		{
			m_bullets.at(i).checkCollision(t_platform, T_MAX_PLAT);
		}
		if (t_box != nullptr)
		{
			m_bullets.at(i).checkCollision(t_box, T_MAX_BOX);
		}
		if (!m_bullets.at(i).update(t_dTime))
		{
			m_nextAvailable = i;
		}
		else
		{
			activeCount++;
		}
	}
	if (M_POOL_SIZE == activeCount)
	{
		m_poolFull = true;
	}
}

void BulletLoop::render(sf::RenderWindow & t_window)
{
	for (int i = 0; i < M_POOL_SIZE; i++)
	{
		// If projectile is active...
		if (m_bullets.at(i).inUse())
		{
			t_window.draw(m_bullets.at(i).m_body);
		}
	}
}

void BulletLoop::setRotation(double t_angle)
{
	for (int i = 0; i < M_POOL_SIZE; i++)
	{
		if (!m_bullets.at(i).inUse())
		{
			m_bullets.at(i).setRotation(t_angle);
		}
		
	}
	int test = 0;
}

bool BulletLoop::checkBodyCollision(sf::RectangleShape & t_rectangle, int t_facing)
{
	for (int i = 0; i < M_POOL_SIZE; i++)
	{
		
		for (int i = 0; i < M_POOL_SIZE; i++)
		{
			if (m_bullets.at(i).inUse())
			{
				if (m_bullets.at(i).checkBodyCollision(t_rectangle, t_facing))
				{
					return true;
				}
			}
		}
	}
	return false;
}
