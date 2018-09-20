#include "Game.h"

static double const MS_PER_UPDATE{ 10.0 };//how many ms per frame update

GameState Game::m_currentState = GameState::MAINMENU;

Game::Game(sf::Texture &t_enemyWalkTexture, sf::Texture &t_playerText, sf::Texture &t_mainBackground, sf::Texture &t_boxTexture, sf::Texture &t_groundTexture, sf::Font &t_font) :
	m_window(sf::VideoMode{ Global::s_fullWidth, Global::s_fullHeight,32 }, "JWWGF2018", sf::Style::Fullscreen),
	m_font(t_font),
	m_player(m_bulletBuffers[0], m_bulletBuffers[1], m_bulletBuffers[2], m_font),
	m_mainMenuTexture(t_mainBackground),
	m_menuFont(t_font),
	m_enemyWalkTexture(t_enemyWalkTexture)
	
{
	t_groundTexture.setRepeated(true);
	m_splashScreen.setUp();
	m_mainMenuScreen.setUp(m_menuFont, m_mainMenuTexture);
	m_helpScreen.setUp(m_menuFont);
	
	m_bulletBuffers[0].loadFromFile("assets//Audio//NormalBullet.ogg");
	m_bulletBuffers[1].loadFromFile("assets//Audio//Shotgun.ogg");
	m_bulletBuffers[2].loadFromFile("assets//Audio//lazer.ogg");

	m_waveBuffers[0].loadFromFile("assets//Audio//Wave1.ogg"); 
	m_waveBuffers[1].loadFromFile("assets//Audio//Wave2.ogg");

	m_waveSounds[0].setBuffer(m_waveBuffers[0]);
	m_waveSounds[1].setBuffer(m_waveBuffers[1]);

	for (int i = 0; i < M_MAX_CLOCK_ENEMY; i++)
	{
		m_clockEnemy[i].setup(m_enemyWalkTexture, m_player.m_bulletTextures[1], m_bulletBuffers[0]);
	}
	m_awningTexture.loadFromFile("assets//Art Assets//awning.png");
	m_awningTexture.setRepeated(true);
	m_walkwayTexture.loadFromFile("assets//Art Assets//billboardWalkway.png");

	m_platforms[0].setSize(sf::Vector2f(500, 200));
	m_platforms[0].setPosition(sf::Vector2f(-200, Global::s_fullHeight));

	m_platforms[1].setSize(sf::Vector2f(400, 200));
	m_platforms[1].setPosition(sf::Vector2f(-500, Global::s_fullHeight));

	m_platforms[2].setSize(sf::Vector2f(400, 200));
	m_platforms[2].setPosition(sf::Vector2f(300, Global::s_fullHeight-1));

	m_platforms[3].setSize(sf::Vector2f(40, 20));
	m_platforms[3].setPosition(sf::Vector2f(190, 990));

	m_platforms[4].setSize(sf::Vector2f(200, 10));
	m_platforms[4].setPosition(sf::Vector2f(-51, 920));

	m_platforms[5].setSize(sf::Vector2f(40, 20));
	m_platforms[5].setPosition(sf::Vector2f(-130, 990));

	
	for (int i = 0; i < M_MAX_BOXES; i++)
	{
		m_boxes[i].setSize(sf::Vector2f(30, 30));
		m_boxes[i].setTexture(&t_boxTexture);
	}

	m_boxes[0].setPosition(120, Global::s_fullHeight - 30);
	m_boxes[1].setPosition(120, Global::s_fullHeight - 60);
	m_boxes[2].setPosition(120, Global::s_fullHeight - 90);
	m_boxes[3].setPosition(-50, Global::s_fullHeight - 30);
	m_boxes[4].setPosition(-50, Global::s_fullHeight - 60);



	for (int i = 0; i < M_MAX_PLATFORMS; i++)
	{
		m_platforms[i].setTexture(&t_groundTexture);
		m_platforms[i].setTextureRect(sf::IntRect(0, 0, m_platforms[i].getGlobalBounds().width, m_platforms[i].getGlobalBounds().height));
	}
	//up to this point needs to be changed


	m_platforms[4].setTexture(&m_walkwayTexture);
	m_platforms[3].setTexture(&m_awningTexture);
	m_platforms[5].setTexture(&m_awningTexture);

	m_platforms[3].setTextureRect(sf::IntRect(0, 0, m_platforms[3].getSize().x, m_platforms[3].getSize().y));
	m_platforms[5].setTextureRect(sf::IntRect(0, 0, m_platforms[5].getSize().x, m_platforms[5].getSize().y));

	m_time.setCharacterSize(25);
	m_time.setFillColor(sf::Color::Black);
	m_time.setFont(t_font);
	m_time.setPosition(20, 850);

	m_killsText.setCharacterSize(25);
	m_killsText.setFillColor(sf::Color::Black);
	m_killsText.setFont(t_font);
	m_killsText.setPosition(20, 875);
	m_killsText.setString("Enemies Killed: " + std::to_string(m_kills));

	m_backgroundTexture.loadFromFile("assets//Art Assets//background2.png");
	m_backgroundTexture2.loadFromFile("assets//Art Assets//background.png");
	m_background.setSize(sf::Vector2f( 500, 400));
	m_background.setPosition(sf::Vector2f(-200, Global::s_fullHeight - m_background.getSize().y));

	m_bgmBuffer.loadFromFile("assets//Audio//LondonFog.wav");
	m_gameSound.setBuffer(m_bgmBuffer);
	m_gameSound.setLoop(true);
	m_gameSound.setVolume(10);
	m_gameSound.play();

	m_gameOverText.setCharacterSize(50);
	m_gameOverText.setFillColor(sf::Color::Yellow);
	m_gameOverText.setFont(m_menuFont);
	m_gameOverText.setString("GAME OVER\n\tScore:" + std::to_string(m_kills));
	m_gameOverText.setOrigin(100,100);

	for (int i = 0; i < M_MAX_LABELS; i++)
	{
		m_label[i].setLabel();
		m_label[i].setPosition(sf::Vector2f(37, (i  * 100) + 900));

		m_buttonText[i].setFont(m_menuFont);
		m_buttonText[i].setString(M_TEXT[i]);
		m_buttonText[i].setFillColor(sf::Color::Black);
		m_buttonText[i].setStyle(sf::Text::Italic);
		m_buttonText[i].setCharacterSize(25);
	}
	m_buttonText[0].setPosition(-3, 890);
	m_buttonText[1].setPosition(22, 990);

	moveButton(0);

	reset();

	m_sepiaTexture.loadFromFile("assets//Art Assets//sepia.png");
	m_overlay.setTexture(&m_sepiaTexture);
	m_overlay.setFillColor(sf::Color(255, 255, 255, 100));
	m_overlay.setSize(sf::Vector2f(500, 600));
	m_overlay.setPosition(sf::Vector2f(-200, Global::s_fullHeight - 400));

	m_window.setVerticalSyncEnabled(true);
	m_controller.connect();
}

void Game::run()
{
	sf::Clock clock;
	sf::Int32 lag = 0;//keeps track of how much time has passed since the last update(frame lag)

	while (m_window.isOpen())
	{
		sf::Time dTime = clock.restart();//difference in time e.g. time since frame was last updated
		lag += dTime.asMilliseconds();
		processEvents();

		//keep updating the frame until the lag has dissipated and the frame catches up to where it should be
		while (lag > MS_PER_UPDATE)
		{
			update(sf::milliseconds(MS_PER_UPDATE));
			lag -= MS_PER_UPDATE;
		}

		//draw the frame
		render();
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}
	}
}


void Game::reset()
{
	if (m_player.m_isDead == true)
	{
		m_kills = -1;
		m_currentWave = 0;
	}
	else
	{
		m_currentWave = 0;
	}
	m_myClock.restart();
	m_timer = 0;
	m_player.reset();
	m_gameOver = false;
	m_paused = false;
	m_enemiesThisWave = 1;
	for (int i = 0; i < M_MAX_CLOCK_ENEMY; i++)
	{	
		m_clockEnemy[i].m_isAlive = false;
	}
	m_currentButton = 0;
	moveButton(0);
}

void Game::playerEnemyCollision(ClockEnemy &t_enemy)
{
	if (m_player.m_body.getPosition().x < t_enemy.m_body.getPosition().x + t_enemy.m_body.getLocalBounds().width &&
		m_player.m_body.getPosition().x + m_player.m_body.getLocalBounds().width > t_enemy.m_body.getPosition().x &&
		m_player.m_body.getPosition().y < t_enemy.m_body.getPosition().y + t_enemy.m_body.getLocalBounds().height &&
		m_player.m_body.getLocalBounds().height + m_player.m_body.getPosition().y > t_enemy.m_body.getPosition().y)
	{
		if (m_player.m_movement.y >= 0 && m_player.m_body.getPosition().y + m_player.m_body.getLocalBounds().height >= t_enemy.m_body.getPosition().y && m_player.m_body.getPosition().y + m_player.m_body.getLocalBounds().height < t_enemy.m_body.getPosition().y + m_player.m_movement.y + 1)
		{
			if (m_player.m_body.getScale().x > 0 && t_enemy.m_body.getScale().x > 0)
			{
				if (m_player.m_body.getPosition().x + m_player.m_body.getLocalBounds().width - 15 > t_enemy.m_body.getPosition().x && m_player.m_body.getPosition().x < t_enemy.m_body.getPosition().x + t_enemy.m_body.getLocalBounds().width - 15)
				{
					m_player.m_movement.y = -2;
					m_player.m_body.setPosition(m_player.m_body.getPosition().x, t_enemy.m_body.getPosition().y - m_player.m_body.getLocalBounds().height);
					m_player.m_jump = false;
					m_player.m_falling = false;
				}
			}
			else if (m_player.m_body.getScale().x < 0 && t_enemy.m_body.getScale().x < 0)
			{
				if (m_player.m_body.getPosition().x - m_player.m_body.getLocalBounds().width + 15 < t_enemy.m_body.getPosition().x && m_player.m_body.getPosition().x > t_enemy.m_body.getPosition().x - t_enemy.m_body.getLocalBounds().width + 15)
				{
					m_player.m_movement.y = -2;
					m_player.m_body.setPosition(m_player.m_body.getPosition().x, t_enemy.m_body.getPosition().y - m_player.m_body.getLocalBounds().height);
					m_player.m_jump = false;
					m_player.m_falling = false;
				}
			}
		}
		else if (t_enemy.m_body.getPosition().y + t_enemy.m_body.getLocalBounds().height >= m_player.m_body.getPosition().y && t_enemy.m_body.getPosition().y + t_enemy.m_body.getLocalBounds().height < m_player.m_body.getPosition().y + t_enemy.m_movement.y + 1)
		{
			if (m_player.m_body.getScale().x > 0 && t_enemy.m_body.getScale().x > 0)
			{

				if (t_enemy.m_body.getPosition().x + t_enemy.m_body.getLocalBounds().width - 15 > m_player.m_body.getPosition().x && t_enemy.m_body.getPosition().x < m_player.m_body.getPosition().x + m_player.m_body.getLocalBounds().width - 15)
				{
					t_enemy.m_movement.y = -2;
					t_enemy.m_body.setPosition(t_enemy.m_body.getPosition().x, m_player.m_body.getPosition().y - t_enemy.m_body.getLocalBounds().height);
				}
			}
			else if (m_player.m_body.getScale().x < 0 && t_enemy.m_body.getScale().x < 0)
			{

				if (t_enemy.m_body.getPosition().x - t_enemy.m_body.getLocalBounds().width + 15 < m_player.m_body.getPosition().x && t_enemy.m_body.getPosition().x > m_player.m_body.getPosition().x - m_player.m_body.getLocalBounds().width + 15)
				{
					t_enemy.m_movement.y = -2;
					t_enemy.m_body.setPosition(t_enemy.m_body.getPosition().x, m_player.m_body.getPosition().y - t_enemy.m_body.getLocalBounds().height);
				}
			}

		}
		else
		{
			float number = 1.5f;

			if (m_player.m_body.getScale().x > 0 && m_player.m_body.getPosition().x + m_player.m_body.getLocalBounds().width >= t_enemy.m_body.getPosition().x + t_enemy.m_body.getLocalBounds().width)
			{
				t_enemy.m_body.setPosition(t_enemy.m_body.getPosition().x - number, t_enemy.m_body.getPosition().y);
			}


			else if (m_player.m_body.getScale().x < 0 && m_player.m_body.getPosition().x + m_player.m_body.getLocalBounds().width >= t_enemy.m_body.getPosition().x + t_enemy.m_body.getLocalBounds().width)
			{
				t_enemy.m_body.setPosition(t_enemy.m_body.getPosition().x - number, t_enemy.m_body.getPosition().y);
			}


			else if (m_player.m_body.getScale().x > 0 && m_player.m_body.getPosition().x <= t_enemy.m_body.getPosition().x + t_enemy.m_body.getLocalBounds().width)
			{
				t_enemy.m_body.setPosition(t_enemy.m_body.getPosition().x + number, t_enemy.m_body.getPosition().y);
			}
			else if (m_player.m_body.getScale().x < 0 && m_player.m_body.getPosition().x + m_player.m_body.getLocalBounds().width <= t_enemy.m_body.getPosition().x + t_enemy.m_body.getLocalBounds().width)
			{
				t_enemy.m_body.setPosition(t_enemy.m_body.getPosition().x + number, t_enemy.m_body.getPosition().y);
			}
		}


	}
}


void Game::update(sf::Time t_dTime)
{
	bool temp = true;

	if (m_controller.isConnected())
	{
		m_controller.update();
	}
	else
	{
		m_controller.connect();
	}

	switch (m_currentState)
	{
	case GameState::SPLASH:
		m_splashScreen.update(t_dTime);
		m_splashScreen.KeyIsPressed(m_controller);
		if (m_splashScreen.m_switch == true)
		{
			m_currentState = GameState::MAINMENU;
		}
		break;
	case GameState::MAINMENU:
		reset();
		m_mainMenuScreen.update(t_dTime, m_controller);
		if (m_mainMenuScreen.m_switchStart == true)
		{
			m_currentState = GameState::PLAYING;
			m_mainMenuScreen.m_switchStart = false;
		}
		if (m_mainMenuScreen.m_switchHelp == true)
		{
			m_currentState = GameState::HELPMENU;
			m_mainMenuScreen.m_switchHelp = false;
		}
		if (m_mainMenuScreen.m_switchExit == true)
		{
			m_window.close();
		}
		break;
	case GameState::PLAYING:
		m_view.setSize(sf::Vector2f(Global::s_width, Global::s_height));

		if (m_gameOver)
		{
			if (m_controller.m_currentState.Start)
			{
				Game::m_currentState = GameState::MAINMENU;
			}
		}

		if (!m_paused && !m_gameOver)
		{
			//changes background every second wave
			if (m_currentWave % 2 == 0)
			{
				m_background.setTexture(&m_backgroundTexture);
				m_boxes[0].setPosition(120, Global::s_fullHeight - 30);
				m_boxes[1].setPosition(120, Global::s_fullHeight - 60);
				m_boxes[2].setPosition(10, Global::s_fullHeight - 30);
				m_boxes[3].setPosition(-50, Global::s_fullHeight - 30);
				m_boxes[4].setPosition(-50, Global::s_fullHeight - 60);
			}
			else if(m_currentWave % 3 ==0)
			{
				m_background.setTexture(&m_backgroundTexture2);
				m_boxes[0].setPosition(10, Global::s_fullHeight - 30);
				m_boxes[1].setPosition(10, Global::s_fullHeight - 60);
				m_boxes[2].setPosition(130, Global::s_fullHeight - 30);
				m_boxes[3].setPosition(50, Global::s_fullHeight - 30);
				m_boxes[4].setPosition(50, Global::s_fullHeight - 60);
			}
			else
			{
				m_background.setTexture(&m_backgroundTexture2);
				m_boxes[0].setPosition(100, Global::s_fullHeight - 30);
				m_boxes[1].setPosition(130, Global::s_fullHeight - 30);
				m_boxes[2].setPosition(130, Global::s_fullHeight - 60);
				m_boxes[3].setPosition(-10, Global::s_fullHeight - 30);
				m_boxes[4].setPosition(-10, Global::s_fullHeight - 60);
			}

			m_currentButton = 0;
			moveButton(0);
			//timer 
			m_elapsedTime = m_myClock.getElapsedTime();
			m_time.setString("Wave: " + std::to_string(m_currentWave));
			if (m_elapsedTime.asSeconds() >= 1000)
			{
				m_timer += 1;
				m_myClock.restart();
			}

			if (m_player.m_isDead == true)
			{
				m_gameOver = true;
				m_player.m_currentState = PlayerState::DEAD;
				m_player.m_body.setPosition(m_player.m_body.getPosition().x, m_platforms[0].getPosition().y-10);
			}

			m_killsText.setString("KillED: " + std::to_string(m_kills));
			m_gameOverText.setString("GAME OVER \n\tKills:" + std::to_string(m_kills));

			//player boundaries
			if (m_player.m_body.getPosition().x > 280)
			{
				m_player.m_body.setPosition(280, m_player.m_body.getPosition().y);
			}
			else if (m_player.m_body.getPosition().x < -210)
			{
				m_player.m_body.setPosition(-210, m_player.m_body.getPosition().y);
			}

			else
			{

				m_view.setCenter((m_player.m_body.getPosition().x), 950);
			}

			//view boundaries
			if (m_view.getCenter().x <= 1)
			{
				m_view.setCenter(1, 950);
			}
			else if (m_view.getCenter().x >= 101)
			{
				m_view.setCenter(101, 950);
			}

			m_player.update(t_dTime, m_controller, m_platforms, M_MAX_PLATFORMS, m_boxes, M_MAX_BOXES, m_clockEnemy, M_MAX_CLOCK_ENEMY);

			//player platform collisions
			for (int i = 0; i < M_MAX_PLATFORMS; i++)
			{
				m_player.platformCollision(m_platforms[i]);
			}
			int enemiesRemaining = 0;
			//enemy chase player
			for (int i = 0; i < M_MAX_CLOCK_ENEMY; i++)
			{
				if (m_clockEnemy[i].m_body.getPosition().y > Global::s_fullHeight)
				{
					m_clockEnemy[i].m_isAlive = false;
				}
				if (m_clockEnemy[i].m_isAlive)
				{
					enemiesRemaining++;
					
					m_clockEnemy[i].chase(m_player.m_body.getPosition());
				}
				m_clockEnemy[i].update(t_dTime, m_platforms, M_MAX_PLATFORMS, m_boxes, M_MAX_BOXES, m_player);
				if (m_clockEnemy[i].m_isAlive)
				{
					playerEnemyCollision(m_clockEnemy[i]);
				}
			}
			if (m_previousEnemies > enemiesRemaining)
			{
				m_kills++;
			}

			if (enemiesRemaining == 0)
			{
				m_currentWave += 1;
				if (m_waveSounds[0].getStatus() != sf::SoundSource::Playing || m_waveSounds[1].getStatus() != sf::SoundSource::Playing)
				{
					if (m_currentWave % 2 == 0)
					{
						m_waveSounds[0].play();
					}
					else
					{
						m_waveSounds[1].play();
					}
				}
				if (m_enemiesThisWave + 3 <= M_MAX_CLOCK_ENEMY)
				{
					m_enemiesThisWave += 3;
					for (int i = 0; i < m_enemiesThisWave; i++)
					{
						m_clockEnemy[i].respawn(m_player.m_body.getPosition(), m_enemySpawnSide);
						m_enemySpawnSide++;
					}
				}
				else
				{
					m_enemiesThisWave = M_MAX_CLOCK_ENEMY;
					for (int i = 0; i < m_enemiesThisWave; i++)
					{
						m_clockEnemy[i].respawn(m_player.m_body.getPosition(), m_enemySpawnSide);
						m_enemySpawnSide++;
					}
				}
			}
			//player box collision
			for (int i = 0; i < M_MAX_BOXES; i++)
			{
				m_player.platformCollision(m_boxes[i]);
			}

			//enemy box collisions
			for (int i = 0; i < m_enemiesThisWave; i++)
			{
				for (int j = 0; j < M_MAX_BOXES; j++)
				{
					m_clockEnemy[i].platformCollision(m_platforms[j]);
					m_clockEnemy[i].platformCollision(m_boxes[j]);
				}
			}

			if (m_controller.m_currentState.Start)
			{
				m_paused = true;
			}
			m_previousEnemies = enemiesRemaining;
		}
		//PAUSED SECTION
		if (m_paused)
		{ 
			if (m_controller.m_currentState.B)
			{
				m_paused = false;
			}
			if (m_currentButton > 1)
			{
				m_currentButton = 0;
			}
			if (m_currentButton < 0)
			{
				m_currentButton = 1;
			}
			if (!m_moved)
			{
				if (m_controller.m_currentState.LeftThumbStick.y >= -15)
				{
					m_currentButton += 1;
					m_moved = true;
				}
				if (m_controller.m_currentState.LeftThumbStick.y <= 15)
				{
					m_currentButton -= 1;
					m_moved = true;
				}
			}

			if (m_controller.m_currentState.LeftThumbStick.y > 0 && m_controller.m_currentState.LeftThumbStick.y < 15 ||
				m_controller.m_currentState.LeftThumbStick.y < 0 && m_controller.m_currentState.LeftThumbStick.y > -15)
			{
				m_moved = false;
			}

			if (m_currentButton == 0)
			{
				moveButton(0);
				resetButton(1);
				if (m_controller.m_currentState.A)
				{
					if (!m_controller.m_previousState.A)
					{
						m_controller.m_currentState.A = true;
						m_paused = false;
					}
				}
			}

			if (m_currentButton == 1)
			{
				moveButton(1);
				resetButton(0);
				if (m_controller.m_currentState.A)
				{
					if (!m_controller.m_previousState.A)
					{
						m_controller.m_currentState.A = true;
						m_currentState = GameState::MAINMENU;
					}
				}
			}
		}
		m_gameOverText.setPosition(m_view.getCenter());
		m_window.setView(m_view);
		break;
	case GameState::HELPMENU:
		m_helpScreen.KeyIsPressed(m_controller);
		m_helpScreen.update(t_dTime);
		if (m_helpScreen.m_switch == true)
		{
			m_currentState = GameState::MAINMENU;
			m_helpScreen.m_switch = false;
		}
		break;
	default:
		break;
	}
	m_controller.m_previousState = m_controller.m_currentState;
}

void Game::render()
{
	m_window.clear(sf::Color::White);
	switch (m_currentState)
	{
	case GameState::SPLASH:
		m_splashScreen.render(m_window);
		break;
	case GameState::MAINMENU:
		m_window.setView(m_window.getDefaultView());
		m_mainMenuScreen.render(m_window);
		break;
	case GameState::PLAYING:

		m_window.draw(m_background);
		m_window.draw(m_time);
		m_window.draw(m_killsText);


		for (int i = 0; i < M_MAX_PLATFORMS; i++)
		{
			m_window.draw(m_platforms[i]);
		}
		for (int i = 0; i < m_enemiesThisWave; i++)
		{
			m_clockEnemy[i].render(m_window);
		}
		m_player.render(m_window);
		
		for (int i = 0; i < M_MAX_BOXES; i++)
		{
			m_window.draw(m_boxes[i]);
		}
		m_window.draw(m_overlay);


		//PAUSED SECTION
		if (m_paused)
		{
			for (int i = 0; i < M_MAX_LABELS; i++)
			{
				m_label[i].render(m_window);
				m_window.draw(m_buttonText[i]);
			}
		}

		if (m_gameOver == true)
		{
			m_window.draw(m_gameOverText);
		}
		break;
	case GameState::HELPMENU:
		m_window.setView(m_window.getDefaultView());
		m_helpScreen.render(m_window);
		break;
	default:
		break;
	}
	m_window.display();
}

//FUNCTIONS USED FOR THE PAUSE MENU
void Game::resetButton(int t_buttonNum)	
{
	m_label[t_buttonNum].setLabel();
	m_buttonText[t_buttonNum].setFillColor(sf::Color::Black);
	m_buttonText[t_buttonNum].setOutlineThickness(0);
}

void Game::moveButton(int t_buttonNum)
{
	m_buttonText[t_buttonNum].setFillColor(M_CYAN);
	m_label[t_buttonNum].labelPressed();
	m_buttonText[t_buttonNum].setOutlineColor(sf::Color::Black);
	m_buttonText[t_buttonNum].setOutlineThickness(5);
}



