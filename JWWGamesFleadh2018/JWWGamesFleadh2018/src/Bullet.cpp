#include "..\include\Bullet.h"


void Bullet::init(sf::Texture const & t_texture, double t_x, double t_y) 
{
	//should be m_bullet.whatever
	m_body.setOrigin(m_body.getLocalBounds().width, m_body.getLocalBounds().height);
	m_body.setPosition(t_x, t_y);
	m_body.setTexture(&t_texture);
	m_body.setTextureRect(sf::IntRect(0, 0, 18, 6));
	m_body.setFillColor(sf::Color::White);
	m_speed = M_MAX_SPEED;
}



bool Bullet::update(sf::Time const & t_dTime)
{
	if (!inUse())
	{
		return false;
	}


	//should be m_bullet
	sf::Vector2f position = m_body.getPosition();
	sf::Vector2f newPos(position.x + std::cos(m_body.getRotation() * 3.141592653 / 180.0) * m_speed * (t_dTime.asMilliseconds() / 1000.0),
		position.y + std::sin(m_body.getRotation() * 3.141592653 / 180.0) * m_speed * (t_dTime.asMilliseconds() / 1000.0));


	//should m_bullet
	m_body.setPosition(newPos.x, newPos.y);

	if (!isOnScreen(newPos))
	{
		m_speed = 0;
	}
	return m_speed == M_MAX_SPEED;
}

bool Bullet::inUse() const
{
	return m_speed == M_MAX_SPEED;
}

void Bullet::setRotation(double t_angle)
{
	m_body.setRotation(t_angle);
}

void Bullet::checkCollision(sf::RectangleShape t_rect[], const int T_ARRAY_SIZE)
{
	for (int i = 0; i < T_ARRAY_SIZE; i++)
	{
		if (m_body.getPosition().x < t_rect[i].getPosition().x + t_rect[i].getLocalBounds().width &&
			m_body.getPosition().x + m_body.getLocalBounds().width > t_rect[i].getPosition().x &&
			m_body.getPosition().y < t_rect[i].getPosition().y + t_rect[i].getLocalBounds().height &&
			m_body.getLocalBounds().height + m_body.getPosition().y > t_rect[i].getPosition().y)
		{
			m_speed = 0;
		}
	}
}

bool Bullet::checkBodyCollision(sf::RectangleShape & t_rectangle, int t_facing)
{
	if (m_body.getPosition().x < t_rectangle.getPosition().x + t_rectangle.getLocalBounds().width &&
		m_body.getPosition().x + m_body.getLocalBounds().width > t_rectangle.getPosition().x &&
		m_body.getPosition().y < t_rectangle.getPosition().y + t_rectangle.getLocalBounds().height &&
		m_body.getLocalBounds().height + m_body.getPosition().y > t_rectangle.getPosition().y)
	{
		if (m_body.getPosition().x <= t_rectangle.getPosition().x + t_rectangle.getLocalBounds().width - 15 && m_body.getPosition().x > t_rectangle.getPosition().x + t_rectangle.getLocalBounds().width - 19)
		{
			m_speed = 0;
			return true;
		}
		//left
		else if (m_body.getPosition().x + m_body.getLocalBounds().width >= t_rectangle.getPosition().x + 15 && m_body.getPosition().x + m_body.getLocalBounds().width < t_rectangle.getPosition().x + 19)
		{
			m_speed = 0;
			return true;
		}
	}
	return false;
}

bool Bullet::isOnScreen(sf::Vector2f position) const
{
	if (position.x - m_body.getLocalBounds().width / 2 > -210.f
		&& position.x + m_body.getLocalBounds().width / 2 < 300
		&& position.y - m_body.getLocalBounds().height / 2 > 0.f
		&& position.y + m_body.getLocalBounds().height / 2 < Global::s_fullHeight)
	{
		return true;
	}
	else
	{
		return false;
	}
}


