#include "Player.h"

Player::Player(sf::SoundBuffer & t_bulletSound1, sf::SoundBuffer & t_bulletSound2, sf::SoundBuffer & t_bulletSound3, sf::Font & t_font) :
	m_walkAnim(m_body, 30, m_walkTexture, sf::IntRect(0, 0, 287, 517)),
	m_jumpAnim(m_body, 30, m_jumpTexture, sf::IntRect(0, 0, 312, 571)),
	m_idleTipAnim(m_body, 30, m_idleTipTexture, sf::IntRect(0, 0, 279, 509)),
	m_idleGunAnim(m_body, 30, m_idleGunTexture, sf::IntRect(0, 0, 278, 504)),
	
	m_GunTommyAnim(m_body, 30, m_gunTommyTexture, sf::IntRect(0, 0, 248, 503)),
	m_JumpTommyAnim(m_body, 30, m_jumpTommyTexture, sf::IntRect(0, 0, 273, 575)),
	m_idleTommyTipAnim(m_body, 30, m_IdleTommyTexture, sf::IntRect(0, 0, 242.5, 509)),
	m_WalkTommyAnim(m_body, 30, m_walkTommyTexture, sf::IntRect(0, 0, 283, 516)),

	m_pistolGunAnim(m_body, 30,m_pistolGunTexture, sf::IntRect(0,0,201, 504)),
	m_pistolIdleAnim(m_body, 30, m_pistolIdleTexture, sf::IntRect(0, 0, 194, 509)),
	m_pistolJumpAnim(m_body, 30, m_pistolJumpTexture, sf::IntRect(0, 0, 230, 571)),
	m_pistolWalkAnim(m_body, 30, m_pistolWalkTexture, sf::IntRect(0, 0, 236, 517)),

	m_pistolRecoilAnim(m_body, 20, m_pistolRecoilTexture, sf::IntRect(0,0,206,504)),
	m_tommyRecoilAnim(m_body, 20, m_tommyRecoilTexture, sf::IntRect(0, 0, 256, 504)),
	m_shottyRecoilAnim(m_body, 20, m_shottyRecoilTexture, sf::IntRect(0, 0, 247, 504)),

	m_currentState{ PlayerState::IDLEGUN },
	m_font{t_font},
	m_hud{m_font}
	{
		setUpBody();
		m_pistolRecoilAnim.m_delay = 2.0f;
		m_shottyRecoilAnim.m_delay = 2.0f;
		m_tommyRecoilAnim.m_delay = 2.0f;

		//bullet texture Load
		m_bulletTextures[0].loadFromFile("assets//Art Assets//Bullets//laser.png");	//laser
		m_bulletTextures[1].loadFromFile("assets//Art Assets//Bullets//Bullet.png"); //normal
		m_bulletTextures[2].loadFromFile("assets//Art Assets//Bullets//ShotBullet.png"); //shotgun

		m_bulletBuffers[0].loadFromFile("assets//Audio//Tommy.ogg");
		m_bulletBuffers[1].loadFromFile("assets//Audio//bigshotgun.ogg");
		m_bulletBuffers[2].loadFromFile("assets//Audio//fullautotommy.ogg");

		m_voiceBuffers[0].loadFromFile("assets//Audio//ShotVoice.ogg"); //shotgun pickup
		m_voiceBuffers[1].loadFromFile("assets//Audio//TommyVoice.ogg"); //tommy pickup

		m_voiceSounds[0].setBuffer(m_voiceBuffers[0]);
		m_voiceSounds[1].setBuffer(m_voiceBuffers[1]);

		m_voiceSounds[0].setVolume(100);
		m_voiceSounds[1].setVolume(100);

		for (int i = 0; i < 3; i++)
		{
			m_bulletSounds[i].setBuffer(m_bulletBuffers[i]);
			m_bulletSounds[i].setPosition(m_body.getPosition().x, m_body.getPosition().y, 0);
			m_bulletSounds[i].setVolume(10);
		}

		m_pickupIconTextures[0].loadFromFile("assets//Art Assets//health.png"); //health pack icon
		m_pickupIconTextures[1].loadFromFile("assets//Art Assets//lazerPickup.png"); //lazer pickup icon
		m_pickupIconTextures[2].loadFromFile("assets//Art Assets//shotPickup.png"); //shotty icon
		m_pickupIconTextures[3].loadFromFile("assets//Art Assets//noPickup.png"); //No Pickup active

		m_hudIcon.setTexture(&m_pickupIconTextures[3]);
		m_hudIcon.setSize(sf::Vector2f(18, 18));
		m_hudIcon.setPosition(sf::Vector2f(8, 816));
		
		m_pickups.setSize(sf::Vector2f(10, 10));
}

void Player::update(sf::Time &t_dTime, Xbox360Controller &t_controller, sf::RectangleShape t_platform[], int const T_MAX_PLAT, sf::RectangleShape t_box[], int const T_MAX_BOX, ClockEnemy t_enemy[], const int T_MAX_ENEMIES)
{
	
	AnimationHandler();
	m_hud.update(m_health, m_pickupTimer);

	Gravity::applyGrav(m_movement, t_dTime);
	if (m_amassedTime.asMilliseconds() > 0)
	{
		m_amassedTime -= t_dTime;
	}
	if (m_amassedTime == sf::Time::Zero)
	{
		m_requestFire = false;
	}

	if (t_controller.m_currentState.A && !m_jump) // Jumping
	{
		m_jump = true;
		m_movement.y -= m_jumpHeight;
		m_falling = true;
		if (m_currentState != PlayerState::JUMPING && m_currentState)
		{
			m_currentState = PlayerState::JUMPING; 
		}
		
	}
	
	//the controller thumbstick value needs to be outside the range of the deadzone
	if (t_controller.m_currentState.LeftThumbStick.x > 15) // WALKING TO THE RIGHT
	{
		m_movement.x = m_horizontalSpeed;
		m_body.setOrigin(0, 0);
		m_body.setScale(1, 1);
		
		if (m_currentState != PlayerState::JUMPING && m_currentState != PlayerState::SHOOTING)
		{
			m_currentState = PlayerState::WALKING;
		}
	}
	else if (t_controller.m_currentState.LeftThumbStick.x < -15) //WALKING TO THE LEFT
	{
		m_movement.x = -m_horizontalSpeed;
		m_body.setOrigin(m_body.getGlobalBounds().width, 0);
		m_body.setScale(-1, 1);
		if (m_currentState != PlayerState::JUMPING && m_currentState != PlayerState::SHOOTING)
		{
			m_currentState = PlayerState::WALKING;
		}
	}
	else 
	{
		if (m_currentState != PlayerState::IDLEGUN && m_currentState != PlayerState::SHOOTING)
		{
			m_currentState = PlayerState::IDLETIP;
		}
		m_movement.x = 0;
		
	}


	switch (m_bulletType)
	{
	case BulletType::Normal:
		if (t_controller.m_currentState.RTrigger > 0 && !m_requestFire)
		{
			m_amassedTime = m_shotWaitTime;
			m_previousState = m_currentState;
			m_currentState = PlayerState::SHOOTING;
			m_requestFire = true;
			requestNormalFire();
		}
		break;
	case BulletType::Split:
		m_hudIcon.setTexture(&m_pickupIconTextures[2]);

		m_pickupTimer++;
		if (t_controller.m_currentState.RTrigger > 0 && !m_requestFire)
		{
			m_amassedTime = m_shotWaitTime + m_shotWaitTime + m_shotWaitTime + m_shotWaitTime;
			m_previousState = m_currentState;
			m_currentState = PlayerState::SHOOTING;
			m_requestFire = true;
			requestSplitFire();
		}
		break;
	case BulletType::Laser:

		m_hudIcon.setTexture(&m_pickupIconTextures[1]);

		m_pickupTimer++;
		if (t_controller.m_currentState.RTrigger > 0 && !m_requestFire)
		{
			m_amassedTime = m_shotWaitTime + m_shotWaitTime + m_shotWaitTime + m_shotWaitTime + m_shotWaitTime + m_shotWaitTime + m_shotWaitTime + m_shotWaitTime;
			m_requestFire = true;
			m_previousState = m_currentState;
			m_currentState = PlayerState::SHOOTING;
			requestLaserFire();
		}
		break;
	default:
		break;
	}
	
	m_pool.update(t_dTime, t_platform, T_MAX_PLAT, t_box, T_MAX_BOX);
	for (int i = 0; i < T_MAX_ENEMIES; i++)
	{
		if (t_enemy[i].m_isAlive)
		{
			if (m_pool.checkBodyCollision(t_enemy[i].m_body, t_enemy[i].m_body.getScale().x))
			{
				t_enemy[i].m_isAlive = false;
				m_enemyParticles[activeParticle].initialise(sf::Vector2f(t_enemy[i].m_body.getPosition().x + t_enemy[i].m_body.getSize().x * .5, t_enemy[i].m_body.getPosition().y + 20), sf::Vector2f(4, 4), sf::Color::Red, sf::Vector2f(4, 4), 20);
				activeParticle++;
				if (activeParticle == MAX__ENEMY_EMMITERS)
				{
					activeParticle = 0;
				}

				m_randPickUpType = (rand() % 3) + 1;
				m_pickupAlive = true;

				t_enemy[i].m_randSpeed = (rand() % 100) * 0.01;
				
				if (t_enemy[i].m_randSpeed <= 0.5)
				{
					t_enemy[i].m_randSpeed = 0.5;
				}

				t_enemy[i].m_speed = t_enemy[i].m_randSpeed;
			}
		}
	}

	m_body.setPosition(m_body.getPosition().x + m_movement.x, m_body.getPosition().y + m_movement.y);

	if (m_pickupAlive == false)
	{
		m_pickups.setPosition(0, 0);
	}

	if (m_pickupAlive == true)
	{
		m_pickups.setPosition(50, 910);
		pickUpType(t_controller);
	}

	if (m_body.getGlobalBounds().intersects(m_pickups.getGlobalBounds()))
	{
		m_pickupAlive = false;
		m_dropPickUp = false;
		m_pickUpInUse = true;

		switch (m_randPickUpType)
		{
		case 1:
			m_voiceSounds[1].play();
			break;
		case 2:
			m_voiceSounds[0].play();
			break;
		case 3:
			m_pickUpInUse = false;
			{
				m_health = 100;
			}
			break;
		default:
			break;
		}

	}

	if (m_pickUpInUse == false)
	{
		m_bulletType = BulletType::Normal;
		m_hudIcon.setTexture(&m_pickupIconTextures[3]);
	}

	if (m_pickUpInUse == true)
	{
		m_pickupAlive = false;
	}

	if (m_pickupTimer >= 1000)
	{
		m_pickUpInUse = false;
		m_pickupTimer = 0;
		m_dropPickUp = false;
	}

	m_shotparticle.update();
	
	for (int i = 0; i < MAX__ENEMY_EMMITERS; i++)
	{
		m_enemyParticles[i].update();
	}

	if (m_health <= 0)
	{
		m_isDead = true;
	}

}

void Player::pickUpType(Xbox360Controller t_controller)
{

	switch (m_randPickUpType)
	{
	case 1:
		if (m_pickUpInUse == false)
		{
			m_pickups.setTexture(&m_pickupIconTextures[1]);
			m_bulletType = BulletType::Laser;

		}
		break;
	case 2:
		if (m_pickUpInUse == false)
		{
			m_pickups.setTexture(&m_pickupIconTextures[2]);
			m_bulletType = BulletType::Split;
		}
		break;
	case 3:
		m_pickups.setTexture(&m_pickupIconTextures[0]);
		break;
	default:
		break;
	}

}


void Player::AnimationHandler()
{
	switch (m_currentState)
	{
	case IDLETIP:
		switch (m_bulletType)
		{
		case BulletType::Normal:
			m_pistolIdleAnim.update();
			break;
		case BulletType::Split:
			m_idleTipAnim.update();
			break;
		case BulletType::Laser:
			m_idleTommyTipAnim.update();
			break;
		default:
			break;
		}

		m_body.setSize(sf::Vector2f(30.5, 63.5));
		break;
	case IDLEGUN:
		switch (m_bulletType)
		{
		case BulletType::Normal:
			m_pistolGunAnim.update();
			break;
		case BulletType::Split:
			m_idleGunAnim.update();
			break;
		case BulletType::Laser:
			m_GunTommyAnim.update();
			break;
		default:
			break;
		}
		m_body.setSize(sf::Vector2f(30.0, 63.5));
		break;
	case WALKING:
		switch (m_bulletType)
		{
		case BulletType::Normal:
			m_pistolWalkAnim.update();
			break;
		case BulletType::Split:
			m_walkAnim.update();
			break;
		case BulletType::Laser:
			m_WalkTommyAnim.update();
			break;
		default:
			break;
		}
		m_body.setSize(sf::Vector2f(35.5, 63.5));
		break;
	case DEAD:
		m_body.setTexture(&m_deathTexture);
		m_body.setTextureRect(sf::IntRect(0, 0, 517, 150));
		m_body.setSize(sf::Vector2f(63.5, 18.87));
		break;
	case JUMPING:
		switch (m_bulletType)
		{
		case BulletType::Normal:
			m_pistolJumpAnim.update();
			break;
		case BulletType::Split:
			m_jumpAnim.update();
			break;
		case BulletType::Laser:
			m_JumpTommyAnim.update();
			break;
		default:
			break;
		}
		m_body.setSize(sf::Vector2f(36.5, 63.5));
		break;
	case SHOOTING:
		switch (m_bulletType)
		{
		case BulletType::Normal:
			m_pistolRecoilAnim.update();
		if (m_pistolRecoilAnim.m_currentFrame >= m_pistolRecoilAnim.m_frames)
			{
				m_currentState = PlayerState::IDLEGUN;
				m_pistolRecoilAnim.reset();
			}
			break;
		case BulletType::Split:
			m_shottyRecoilAnim.update();
			if (m_shottyRecoilAnim.m_currentFrame >= m_shottyRecoilAnim.m_frames)
			{
				m_currentState = m_previousState;
				m_shottyRecoilAnim.reset();
			}
			break;
		case BulletType::Laser:
			m_tommyRecoilAnim.update();
			if (m_tommyRecoilAnim.m_currentFrame >= m_tommyRecoilAnim.m_frames)
			{
				m_currentState = m_previousState;
				m_tommyRecoilAnim.reset();
			}
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}

	if (m_jump || m_falling)
	{
		m_currentState = PlayerState::JUMPING;
	}
	else
	{
		m_jumpAnim.reset();
	}

	if (m_jumpAnim.m_currentFrame >= m_jumpAnim.m_frames && m_currentState == PlayerState::JUMPING)
	{
		m_currentState = PlayerState::IDLEGUN;
	}


	if (m_idleTipAnim.m_currentFrame >= m_idleTipAnim.m_frames && m_currentState == PlayerState::IDLETIP)
	{
		m_currentState = PlayerState::IDLEGUN;
		m_idleTipAnim.reset();
	}

	if (m_currentState != PlayerState::IDLEGUN)
	{
		m_idleGunAnim.reset();
	}

	if (m_requestFire && m_currentState == PlayerState::IDLETIP)
	{
		m_currentState = PlayerState::IDLEGUN;
	}


}


void Player::render(sf::RenderWindow & t_window)
{
	m_hud.render(t_window);
	t_window.draw(m_hudIcon);
	t_window.draw(m_body);
	if (m_pickupAlive == true)
	{
		t_window.draw(m_pickups);
	}
	m_pool.render(t_window);
	m_shotparticle.render(t_window);
	for (int i = 0; i < MAX__ENEMY_EMMITERS; i++)
	{
		m_enemyParticles[i].render(t_window);
	}
}

void Player::setUpBody()
{
	if (!m_walkTexture.loadFromFile("assets//Art Assets//Animations//PlayerWalkShot.png"))
	{
		std::cout << "no texture" << std::endl;
	}
	
	m_jumpTexture.loadFromFile("assets//Art Assets//Animations//ShottyJump.png");
	m_idleTipTexture.loadFromFile("assets//Art Assets//Animations//PlayerIdleTipShot.png");
	m_idleGunTexture.loadFromFile("assets//Art Assets//Animations//PlayerIdleShotGun.png");
	m_deathTexture.loadFromFile("assets//Art Assets//ded.png");

	m_gunTommyTexture.loadFromFile("assets//Art Assets//Animations//TommyIdle.png");
	m_walkTommyTexture.loadFromFile("assets//Art Assets//Animations//PlayerTommyWalk.png");
	m_IdleTommyTexture.loadFromFile("assets//Art Assets//Animations//TommyTip.png");
	m_jumpTommyTexture.loadFromFile("assets//Art Assets//Animations//TommyJump.png");

	m_pistolGunTexture.loadFromFile("assets//Art Assets//Animations//PistolIdle.png");
	m_pistolIdleTexture.loadFromFile("assets//Art Assets//Animations//PistolTip.png");
	m_pistolJumpTexture.loadFromFile("assets//Art Assets//Animations//pistolJump.png");
	m_pistolWalkTexture.loadFromFile("assets//Art Assets//Animations//pistolWalk.png");

	m_shottyRecoilTexture.loadFromFile("assets//Art Assets//Animations//shottyRecoil.png");
	m_tommyRecoilTexture.loadFromFile("assets//Art Assets//Animations//tommyRecoil.png");
	m_pistolRecoilTexture.loadFromFile("assets//Art Assets//Animations//pistolRecoil.png");

	m_body.setTexture(&m_idleGunTexture);

	m_body.setPosition(0, 900);
	m_body.setSize(m_size);
}

bool Player::platformCollision(sf::RectangleShape & t_rectangle)
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
			if (m_currentState == PlayerState::JUMPING)
			{
				m_currentState = PlayerState::IDLEGUN;
			}
			m_body.setPosition(m_body.getPosition().x, t_rectangle.getPosition().y - m_body.getLocalBounds().height);
			m_movement.y = 0;
			m_jump = false;
			m_falling = false;
			
		}
		else if (m_movement.y >= 0 && m_body.getScale().x < 0 && m_body.getPosition().y + m_body.getLocalBounds().height >= t_rectangle.getPosition().y && m_body.getPosition().y + m_body.getLocalBounds().height < t_rectangle.getPosition().y + m_movement.y + 1  && m_body.getPosition().x + m_body.getLocalBounds().width - 15 <= t_rectangle.getPosition().x + t_rectangle.getLocalBounds().width)
		{
			if (m_currentState == PlayerState::JUMPING)
			{
				m_currentState = PlayerState::IDLEGUN;
			}
			m_body.setPosition(m_body.getPosition().x, t_rectangle.getPosition().y - m_body.getLocalBounds().height);
			m_movement.y = 0;
			m_jump = false;
			m_falling = false;

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
			return true;
		}
		//left
		else if (m_body.getPosition().x + m_body.getLocalBounds().width >= t_rectangle.getPosition().x + 15 && m_body.getPosition().x + m_body.getLocalBounds().width < t_rectangle.getPosition().x + 19)
		{
			m_body.setPosition(t_rectangle.getPosition().x - m_body.getLocalBounds().width + 14, m_body.getPosition().y);
			return true;
		}

	}
	else
	{
		return true;
	}
}

void Player::requestNormalFire()
{
	
	if (m_body.getScale().x > 0)
	{
		m_pool.setRotation(0.0);
		sf::Vector2f firePos(m_body.getPosition().x + m_body.getLocalBounds().width, m_body.getPosition().y + m_body.getLocalBounds().height / 2 - 7);
		m_pool.create(m_bulletTextures[1], firePos.x, firePos.y);
		m_shotparticle.initialise(firePos, sf::Vector2f(4, 4), m_flashColour, sf::Vector2f(2, 2), 7);
	}
	else
	{
		m_pool.setRotation(180.0);
		sf::Vector2f firePos(m_body.getPosition().x, m_body.getPosition().y + m_body.getLocalBounds().height / 2 - 9);
		m_pool.create(m_bulletTextures[1], firePos.x, firePos.y);
		m_shotparticle.initialise(firePos, sf::Vector2f(4, 4), m_flashColour, sf::Vector2f(2, 2), 7);
	}
	if (m_bulletSounds[0].getStatus() != sf::SoundSource::Playing)
	{
		m_bulletSounds[0].play();
	}
}

void Player::requestSplitFire()
{
	if (m_body.getScale().x > 0)
	{
		sf::Vector2f firePos(m_body.getPosition().x + m_body.getLocalBounds().width, m_body.getPosition().y + m_body.getLocalBounds().height / 2 - 7);
		m_pool.setRotation(10.0);
		m_pool.create(m_bulletTextures[2], firePos.x, firePos.y);
		m_pool.setRotation(0.0);
		m_pool.create(m_bulletTextures[2], firePos.x, firePos.y);
		m_pool.setRotation(350.0);
		m_pool.create(m_bulletTextures[2], firePos.x, firePos.y);
		m_shotparticle.initialise(firePos, sf::Vector2f(4, 4), m_flashColour, sf::Vector2f(2, 2), 7);
	}
	else
	{
		sf::Vector2f firePos(m_body.getPosition().x, m_body.getPosition().y + m_body.getLocalBounds().height / 2 - 9);
		m_pool.setRotation(180.0);
		m_pool.create(m_bulletTextures[2], firePos.x, firePos.y);
		m_pool.setRotation(170.0);
		m_pool.create(m_bulletTextures[2], firePos.x, firePos.y);
		m_pool.setRotation(190.0);
		m_pool.create(m_bulletTextures[2], firePos.x, firePos.y);
		m_shotparticle.initialise(firePos, sf::Vector2f(4, 4), m_flashColour, sf::Vector2f(2, 2), 7);
	}
	if (m_bulletSounds[1].getStatus() == !sf::SoundSource::Playing)
	{
		m_bulletSounds[1].play();
	}

}

void Player::requestLaserFire()
{
	
	int offset = 2;
	if (m_body.getScale().x > 0)
	{
		sf::Vector2f firePos(m_body.getPosition().x + m_body.getLocalBounds().width, m_body.getPosition().y + m_body.getLocalBounds().height / 2 - 7);
		m_pool.setRotation(0.0);
		m_pool.create(m_bulletTextures[1], firePos.x, firePos.y);
		m_pool.create(m_bulletTextures[1], firePos.x + offset, firePos.y);
		m_pool.create(m_bulletTextures[1], firePos.x + offset * 2, firePos.y);
		m_pool.create(m_bulletTextures[1], firePos.x + offset * 3, firePos.y);
		m_pool.create(m_bulletTextures[1], firePos.x + offset * 4, firePos.y);
		m_shotparticle.initialise(firePos, sf::Vector2f(4, 4), m_flashColour, sf::Vector2f(2, 2), 7);

	}
	else
	{
		sf::Vector2f firePos(m_body.getPosition().x, m_body.getPosition().y + m_body.getLocalBounds().height / 2 - 9);
		m_pool.setRotation(180.0);
		m_pool.create(m_bulletTextures[1], firePos.x, firePos.y);
		m_pool.create(m_bulletTextures[1], firePos.x - offset, firePos.y);
		m_pool.create(m_bulletTextures[1], firePos.x - offset * 2, firePos.y);
		m_pool.create(m_bulletTextures[1], firePos.x - offset * 3, firePos.y);
		m_pool.create(m_bulletTextures[1], firePos.x - offset * 4, firePos.y);
		m_shotparticle.initialise(firePos, sf::Vector2f(4, 4), m_flashColour, sf::Vector2f(2, 2), 7);
		
	}
	if (m_bulletSounds[2].getStatus() != sf::SoundSource::Playing)
	{
		m_bulletSounds[2].play();
	}

}

void Player::reset()
{
	m_health = 100;
	m_isDead = false;
	m_body.setPosition(1, 950);
	m_jump = 0;
	m_pickUpInUse == false;
}


