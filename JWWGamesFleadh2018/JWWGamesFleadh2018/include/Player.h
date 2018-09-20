#ifndef PLAYER
#define PLAYER

#include "Gravity.h"
#include "GlobalInclude.h"
#include "Animation.h"
#include "BulletLoop.h"
#include "ClockEnemy.h"
#include "ParticleSystem.h"
#include "SFML\Audio.hpp"

#include "HUD.h"


enum PlayerState
{
	IDLETIP,
	IDLEGUN,
	WALKING,
	DEAD,
	JUMPING,
	SHOOTING
};

enum class BulletType
{
	Normal,
	Split,
	Laser
};

class ClockEnemy;

const int MAX__ENEMY_EMMITERS{ 10 };
class Player
{
public:
	Player(sf::SoundBuffer & t_bulletSound1, sf::SoundBuffer & t_bulletSound2, sf::SoundBuffer & t_bulletSound3, sf::Font & t_font);
	void update(sf::Time &t_dTime, Xbox360Controller &t_controller, sf::RectangleShape t_platform[], int const T_MAX_PLAT, sf::RectangleShape t_box[], int const T_MAX_BOX, ClockEnemy t_enemy[], const int T_MAX_ENEMIES);
	void render(sf::RenderWindow &t_window);
	bool platformCollision(sf::RectangleShape & t_rectangle);

	bool m_dropPickUp = false;

	void AnimationHandler();

	void requestNormalFire();
	void requestSplitFire();
	void requestLaserFire();

	sf::Vector2f m_position{ 0,100 };
	sf::Vector2f m_size{ 10,56 };
	sf::RectangleShape m_body;
	sf::Vector2f m_movement{ 0,0 };
	bool m_falling = true;
	bool m_jump{ true };

	sf::Texture m_bulletTextures[3];
	int getHealth() { return m_health; }
	void reset();

	ParticleSystem m_shotparticle;


	/// <summary>
	/// figure out why this is here
	/// </summary>
	ParticleSystem m_enemyParticles[MAX__ENEMY_EMMITERS];
	/// <summary>
	/// 
	/// </summary>


	sf::Font m_font;

	int activeParticle{ 0 };

	sf::SoundBuffer m_bulletBuffers[3];
	sf::Sound m_bulletSounds[3];

	sf::SoundBuffer m_voiceBuffers[2];
	sf::Sound m_voiceSounds[2];

	float m_health = 100;

	Hud m_hud;
	float m_pickupTimer = 0;

	bool m_isDead = false;
	int m_horizontalSpeed{ 2 }, m_jumpHeight{ 5 };

	PlayerState m_currentState;

private:
	void setUpBody();

	sf::Texture m_jumpTexture;
	sf::Texture m_walkTexture;
	sf::Texture m_idleTipTexture;
	sf::Texture m_idleGunTexture;
	sf::Texture m_deathTexture;

	sf::Texture m_walkTommyTexture;
	sf::Texture m_jumpTommyTexture;
	sf::Texture m_gunTommyTexture;
	sf::Texture m_IdleTommyTexture;

	sf::Texture m_pistolWalkTexture;
	sf::Texture m_pistolIdleTexture;
	sf::Texture m_pistolGunTexture;
	sf::Texture m_pistolJumpTexture;

	sf::Texture m_pistolRecoilTexture;
	sf::Texture m_shottyRecoilTexture;
	sf::Texture m_tommyRecoilTexture;

	PlayerState m_previousState;
	
	Animation m_walkAnim;
	Animation m_jumpAnim;

	Animation m_idleTipAnim;
	Animation m_idleGunAnim;

	Animation m_idleTommyTipAnim;
	Animation m_GunTommyAnim;
	Animation m_JumpTommyAnim;
	Animation m_WalkTommyAnim;

	Animation m_pistolIdleAnim;
	Animation m_pistolGunAnim;
	Animation m_pistolJumpAnim;
	Animation m_pistolWalkAnim;

	Animation m_pistolRecoilAnim;
	Animation m_shottyRecoilAnim;
	Animation m_tommyRecoilAnim;
//	int m_horizontalSpeed{ 2 },m_jumpHeight{5};


	BulletLoop m_pool;

	sf::Time m_shotWaitTime{ sf::milliseconds(240) };
	sf::Time m_amassedTime{ sf::Time::Zero };
	bool m_requestFire = false;
	BulletType m_bulletType{ BulletType::Normal };
	sf::Color m_flashColour{ sf::Color(230, 188, 130, 230) };

	//pickup
	void pickUpType(Xbox360Controller t_controller);
	sf::RectangleShape m_pickups;
	bool m_pickupAlive = false;
	int m_randSpawnPickUp;
	int m_randPickUpType;
	bool m_pickUpInUse = false;

	sf::RectangleShape m_hudIcon;
	sf::Texture m_pickupIconTextures[4];
};

#endif