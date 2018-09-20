#ifndef CLOCK_ENEMY
#define CLOCK_ENEMY

#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "SFML\Graphics.hpp"
#include "Gravity.h"
#include "Animation.h"
#include "GlobalInclude.h"
#include "BulletLoop.h"
#include "Player.h"
#include "ParticleSystem.h"

#include <SFML\Audio.hpp>

enum EnemyState
{
	ENEMYWALKING,
	ENEMYDIEING
};

class Player;
class ClockEnemy
{
public:
	ClockEnemy();
	

	void setup(sf::Texture t_walktexture, sf::Texture t_bullet, sf::SoundBuffer t_buffer);
//	void update(sf::Time t_dTime);

	//void setup(sf::Texture t_walktexture, sf::Texture t_bullet);
	void update(sf::Time t_dTime, sf::RectangleShape t_platform[], int const T_MAX_PLAT, sf::RectangleShape t_box[], int const T_MAX_BOX, Player &t_player);

	void render(sf::RenderWindow &t_window);
	bool platformCollision(sf::RectangleShape & t_rectangle);

	bool m_isAlive{ false };

	void jump();

	void respawn( sf::Vector2f t_playerPos, int t_spawnside);

	bool m_requestFire = false;

	void chase(sf::Vector2f t__targetPos);

	void requestFire();

	EnemyState m_currentState;

	Animation m_walkAnim;

	BulletLoop m_pool;

	sf::RectangleShape m_body;

	void setUpBody();
	
	sf::Texture m_walkTexture;

	sf::Texture m_bulletTexture;
	sf::Vector2f m_movement{ 0, 0 };


	float m_speed{ 0.5 };
	float m_randSpeed = 0;
private:

	
	
	sf::Texture m_bodyTexture;

	


	int m_randSpwan;


	int m_randSeed;


	sf::Vector2f m_position{ 200,900 };

	sf::Time m_shotWaitTime{ sf::milliseconds(1400) };
	sf::Time m_amassedTime{ sf::Time::Zero };

	bool m_jump = true;
	int m_jumpHeight = 5;


	sf::RectangleShape m_pickups;
	bool m_pickupAlive;

	sf::SoundBuffer m_bulletBuffer;
	sf::Sound m_bulletSound;

	ParticleSystem m_muzzleflash;
	sf::Color m_flashColourEnemy{ sf::Color(230, 188, 130, 230) };
};

#endif