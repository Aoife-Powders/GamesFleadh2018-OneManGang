#include "ParticleSystem.h"
#include <iostream>

ParticleSystem::ParticleSystem() : m_positition(sf::Vector2f(0.0f, 0.0f))
{
}


ParticleSystem::~ParticleSystem()
{
	std::cout << "!!!!!!!!!!!!!!! " << std::endl;
}

void ParticleSystem::initialise(sf::Vector2f t_position, sf::Vector2f &t_velocity, sf::Color t_color, sf::Vector2f &t_size, int t_maxTimer)
{
	m_positition = t_position;

	for (int i = 0; i < MAX_PARTICLES; i++)
	{
		m_particle[i].initialise(m_positition, sf::Vector2f(rand() / double(RAND_MAX) * 4 - 2, rand() / double(RAND_MAX) * 4 - 2), t_color, t_size, t_maxTimer);
	}
}

void ParticleSystem::update()
{
	for (int i = 0; i < MAX_PARTICLES; i++)
	{
		if (m_particle[i].m_timer > 0)
		{
			m_particle[i].m_pos += (m_particle[i].m_velocity);
			m_particle[i].m_timer--;
		}
	}
}

void ParticleSystem::render(sf::RenderWindow & t_window)
{
	for (int i = 0; i < MAX_PARTICLES; i++)
	{
		if (m_particle[i].m_timer > 0)
		{
			m_particleShape.setPosition(m_particle[i].m_pos);
			m_particleShape.setSize(m_particle[i].m_size);
			m_particleShape.setFillColor(m_particle[i].m_color);
			t_window.draw(m_particleShape);
		}
	}
}
