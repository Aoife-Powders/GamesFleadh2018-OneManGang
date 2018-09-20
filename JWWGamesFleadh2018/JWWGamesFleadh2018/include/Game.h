#ifndef _GAME
#define _GAME
#include <iostream>
#include "GlobalInclude.h"
#include "Player.h"
#include "Splash.h"
#include "Help.h"
#include "MainMenu.h"
#include "ClockEnemy.h"
#include <SFML\Audio.hpp>
#include "Bullet.h"
#include "HUD.h"

//enum used to determine gamestate
enum class GameState
{
	SPLASH,
	MAINMENU,
	PLAYING,
	HELPMENU,
};



class Game
{
public:
	Game(sf::Texture &t_enemyWalkTexture, sf::Texture &t_playerText, sf::Texture &t_mainBackground, sf::Texture &t_boxTexture, sf::Texture &t_groundTexture, sf::Font &t_font);
	void run();

	//current gamestate
	static GameState m_currentState;

private:
	void processEvents();
	void update(sf::Time);
	void render();
	void reset();

	void playerEnemyCollision(ClockEnemy &t_enemy);

	sf::Font m_font;
	sf::Font m_menuFont;
	sf::Texture m_mainMenuTexture;
	sf::Texture m_backgroundTexture;
	sf::Texture m_backgroundTexture2;

	//instance to run splash screen
	Splash m_splashScreen;
	Help m_helpScreen;
	MainMenu m_mainMenuScreen;
	Bullet m_bullet;

	sf::RenderWindow m_window;

	static const int M_MAX_PLATFORMS{ 6 }, M_MAX_CLOCK_ENEMY{ 20 }, M_MAX_BOXES{ 5 };
	Xbox360Controller m_controller;

	Player m_player;
	sf::View m_view;

	sf::RectangleShape m_platforms[M_MAX_PLATFORMS];
	sf::RectangleShape m_boxes[M_MAX_BOXES];
	ClockEnemy m_clockEnemy[M_MAX_CLOCK_ENEMY];

	sf::Text m_time;
	int m_timer = 0;
	sf::Clock m_myClock;
	sf::Time m_elapsedTime;

	sf::Text m_killsText;

	sf::Text m_gameOverText;
	bool m_gameOver = false;


	//PAUSE MENU VARIABLES
	static const int M_MAX_LABELS = 2;
	bool m_paused = { false };
	UiLibrary m_label[M_MAX_LABELS];
	const sf::Color M_CYAN{ 43, 143, 155 };
	const sf::String M_TEXT[M_MAX_LABELS] = { "Continue", "Exit" };
	sf::Text m_buttonText[M_MAX_LABELS];
	void resetButton(int t_buttonNum);
	void moveButton(int t_buttonNum);
	int m_currentButton = 0;
	bool m_moved = false;
	
	sf::RectangleShape m_background;
	sf::RectangleShape m_overlay;

	int m_enemySpawnSide{ 0 };
	sf::Texture m_enemyBulletTexture;
	sf::Texture & m_enemyWalkTexture;
	sf::Texture m_sepiaTexture;

	sf::Texture m_walkwayTexture;
	sf::Texture m_awningTexture;

	sf::Sound m_gameSound;
	sf::SoundBuffer m_bgmBuffer;

	sf::SoundBuffer m_bulletBuffers[3];

	sf::SoundBuffer m_waveBuffers[2];
	sf::Sound m_waveSounds[2];
	int m_enemiesThisWave = 1;
	int m_currentWave = -1;
	int m_kills = 0;
	int m_previousEnemies = 0;

};

#endif