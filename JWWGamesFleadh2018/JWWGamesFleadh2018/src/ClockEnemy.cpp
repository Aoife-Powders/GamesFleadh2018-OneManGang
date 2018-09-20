#include "ClockEnemy.h"

ClockEnemy::ClockEnemy() :
	m_walkAnim(m_body, 30, m_walkTexture, sf::IntRect(0, 0, 289, 508)),
	m_currentState(EnemyState::ENEMYWALKING)
	{
		setUpBody();
		m_walkAnim.m_delay = 10.0f;

		m_amassedTime = sf::milliseconds(rand() % m_shotWaitTime.asMilliseconds() + 20);
		m_movement.x = 0;
}

void ClockEnemy::setup(sf::Texture t_walktexture, sf::Texture t_bullet, sf::SoundBuffer t_buffer)
{
	m_walkTexture = t_walktexture;
	m_bulletTexture = t_bullet;
	m_bulletBuffer = t_buffer;

	m_bulletSound.setBuffer(m_bulletBuffer);
	m_bulletSound.setVolume(5);
	m_bulletSound.setPosition(m_position.x, m_position.y, 0);
	m_bulletSound.setLoop(false);

	srand(time(NULL));
	m_movement.x = 0;

	

}

void ClockEnemy::update(sf::Time t_dTime, sf::RectangleShape t_platform[], int const T_MAX_PLAT, sf::RectangleShape t_box[], int const T_MAX_BOX, Player &t_player)
{
	if (m_isAlive)
	{
		Gravity::applyGrav(m_movement, t_dTime);
		if (m_amassedTime.asMilliseconds() > 0)
		{
			m_amassedTime -= t_dTime;
		}
		if (m_amassedTime == sf::Time::Zero)
		{
			m_requestFire = false;
		}



		switch (m_currentState)
		{
		case ENEMYWALKING:
			m_walkAnim.update();
			if (!m_requestFire)
			{
				m_amassedTime = m_shotWaitTime;
				m_requestFire = true;
				requestFire();
			}
			break;
		case ENEMYDIEING:
			break;
		default:
			break;
		}
	}

	m_pool.update(t_dTime, t_platform, T_MAX_PLAT, t_box, T_MAX_BOX);
	m_muzzleflash.update();
	if (m_pool.checkBodyCollision(t_player.m_body, t_player.m_body.getScale().x))
	{
		t_player.m_health-=5;
	}
	if (m_isAlive)
	{
		m_body.setPosition(m_body.getPosition().x + m_movement.x, m_body.getPosition().y + m_movement.y);
	}

}

void ClockEnemy::render(sf::RenderWindow & t_window)
{
	if (m_isAlive)
	{
		t_window.draw(m_body);
	}
	
	m_pool.render(t_window);
	m_muzzleflash.render(t_window);
}

void ClockEnemy::setUpBody()
{
	m_body.setTexture(&m_walkTexture);
	m_body.setSize(sf::Vector2f(35.5, 63.5));
	m_body.setPosition(200,900);
}

bool ClockEnemy::platformCollision(sf::RectangleShape & t_rectangle)
{
	//if the player collides with the rectangle(platform)
	if (m_body.getPosition().x < t_rectangle.getPosition().x + t_rectangle.getLocalBounds().width &&
		m_body.getPosition().x + m_body.getLocalBounds().width > t_rectangle.getPosition().x &&
		m_body.getPosition().y < t_rectangle.getPosition().y + t_rectangle.getLocalBounds().height &&
		m_body.getLocalBounds().height + m_body.getPosition().y > t_rectangle.getPosition().y)
	{
		//top
		if (m_movement.y >= 0 && m_body.getScale().x > 0 && m_body.getPosition().y + m_body.getLocalBounds().height >= t_rectangle.getPosition().y && m_body.getPosition().y + m_body.getLocalBounds().height < t_rectangle.getPosition().y + m_movement.y + 1 && m_body.getPosition().x + m_body.getLocalBounds().width - 15 >= t_rectangle.getPosition().x)
		{
			m_body.setPosition(m_body.getPosition().x, t_rectangle.getPosition().y - m_body.getLocalBounds().height);
			m_movement.y = 0;
			m_jump = false;
		}
		else if (m_movement.y >= 0 && m_body.getScale().x < 0 && m_body.getPosition().y + m_body.getLocalBounds().height >= t_rectangle.getPosition().y && m_body.getPosition().y + m_body.getLocalBounds().height < t_rectangle.getPosition().y + m_movement.y + 1 && m_body.getPosition().x + m_body.getLocalBounds().width - 15 <= t_rectangle.getPosition().x + t_rectangle.getLocalBounds().width)
		{
			m_body.setPosition(m_body.getPosition().x, t_rectangle.getPosition().y - m_body.getLocalBounds().height);
			m_movement.y = 0;
			m_jump = false;
		}
		//bottom
		else if (m_movement.y < 0 && m_body.getScale().x > 0 && m_body.getPosition().y <= t_rectangle.getPosition().y + t_rectangle.getLocalBounds().height - 7 && m_body.getPosition().y > t_rectangle.getPosition().y + t_rectangle.getLocalBounds().height - 12 && m_body.getPosition().x + m_body.getLocalBounds().width - 15 >= t_rectangle.getPosition().x)
		{
			m_movement.y = 0;
			return true;
		}
		else if (m_movement.y < 0 && m_body.getScale().x < 0 && m_body.getPosition().y <= t_rectangle.getPosition().y + t_rectangle.getLocalBounds().height - 7 && m_body.getPosition().y > t_rectangle.getPosition().y + t_rectangle.getLocalBounds().height - 12 && m_body.getPosition().x + m_body.getLocalBounds().width - 15 <= t_rectangle.getPosition().x + t_rectangle.getLocalBounds().width)
		{
			m_movement.y = 0;
			return true;
		}
		//right
		else if (m_body.getPosition().x <= t_rectangle.getPosition().x + t_rectangle.getLocalBounds().width - 15 && m_body.getPosition().x > t_rectangle.getPosition().x + t_rectangle.getLocalBounds().width - 19)
		{
			m_body.setPosition(t_rectangle.getPosition().x + t_rectangle.getLocalBounds().width - 14, m_body.getPosition().y);
			if (!m_jump)
			{
				jump();
			}
			return true;
		}
		//left
		else if (m_body.getPosition().x + m_body.getLocalBounds().width >= t_rectangle.getPosition().x + 15 && m_body.getPosition().x + m_body.getLocalBounds().width < t_rectangle.getPosition().x + 19)
		{
			m_body.setPosition(t_rectangle.getPosition().x - m_body.getLocalBounds().width + 14, m_body.getPosition().y);
			if (!m_jump)
			{
				jump();
			}
			return true;
		}

	}
	else
	{
		return true;
	}
}

void ClockEnemy::jump()
{
	m_jump = true;
	m_movement.y = -m_jumpHeight;
}

void ClockEnemy::respawn(sf::Vector2f t_playerPos, int t_spawnside)
{

	if (!m_isAlive)
	{
		m_randSeed = rand() % 13548;
		srand(m_randSeed);
		m_randSpwan = rand() % 1000;

		if (t_spawnside % 2 == 0)
		{
			m_position.x = t_playerPos.x + Global::s_width + (m_randSpwan * .1);
		}
		else
		{
			m_position.x = t_playerPos.x - Global::s_width - (m_randSpwan * .1);
		}
		m_position.y = m_position.y;

		m_body.setPosition(m_position);

		m_isAlive = true;
	}
}

void ClockEnemy::chase(sf::Vector2f t__targetPos)
{
	sf::Vector2f direction;

	direction.x = t__targetPos.x - m_body.getPosition().x;

	if (direction.x < -0.5)
	{
		m_movement.x = -m_speed;
		m_body.setOrigin(m_body.getGlobalBounds().width, 0);
		m_body.setScale(-1, 1);
	}

	else if(direction.x > 0.5)
	{
		m_movement.x = m_speed;
		m_body.setOrigin(0, 0);
		m_body.setScale(1, 1);
	}
	else
	{
		m_movement.x = 0;
	}

}

void ClockEnemy::requestFire()
{

	if (m_body.getScale().x > 0)
	{
		m_pool.setRotation(0.0);
		sf::Vector2f firePos(m_body.getPosition().x + m_body.getLocalBounds().width, m_body.getPosition().y + m_body.getLocalBounds().height / 2 - 5);
		m_pool.create(m_bulletTexture, firePos.x, firePos.y);
		m_muzzleflash.initialise(firePos, sf::Vector2f(4, 4), m_flashColourEnemy, sf::Vector2f(2, 2),5);
	}
	else
	{
		m_pool.setRotation(180.0);
		sf::Vector2f firePos(m_body.getPosition().x, m_body.getPosition().y + m_body.getLocalBounds().height / 2 - 7);
		m_pool.create(m_bulletTexture, firePos.x, firePos.y);
		m_muzzleflash.initialise(firePos, sf::Vector2f(4, 4), m_flashColourEnemy, sf::Vector2f(2, 2), 5);
	}

	m_bulletSound.play();
}

