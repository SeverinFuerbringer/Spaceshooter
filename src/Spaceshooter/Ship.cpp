//////////////////////////////////////////////////
//	Copyright © Severin Fürbringer 2014
//
//	Author: Severin Fürbringer
//	Jahr:	2014
//	Datei:	Ship.cpp
//////////////////////////////////////////////////

#include "Ship.h"


StaticShip::StaticShip(sf::Color col, se::vec2f pos, bool bot)
	: isBot(bot), m_dir(se::vec2f(0, -7)),
      m_proj_buffer_size(INT32_MAX)
{
	setFillColor(col);
	setPosition(pos.x, pos.y);
	setSize(se::vec2f(32, 32));
	setShootSpeed(0.2f);
	m_shootingSound = nullptr;
}


StaticShip::StaticShip(sf::Texture* texture, se::vec2f pos, bool bot)
	: isBot(bot), m_dir(se::vec2f(0, -7)),
      m_proj_buffer_size(INT32_MAX)
{
	setPosition(pos.x, pos.y);
	setSize(se::vec2f(32, 32));
	setTexture(texture);
	setShootSpeed(0.2f);
	m_shootingSound = nullptr;
}


void StaticShip::update(sf::RenderWindow& win)
{
	m_tInterval = m_cInterval.getElapsedTime();

	int winx = se::Engine::get().getWinSize().x;
	int winy = se::Engine::get().getWinSize().y;

	// Dispose of projectiles outside window
	for(se::uint i = 0; i < m_projectiles.size(); i++)
	{
		if(m_projectiles[i].getPosition().x > winx ||
		        m_projectiles[i].getPosition().x < 0 ||
		        m_projectiles[i].getPosition().y > winy ||
		        m_projectiles[i].getPosition().y < 0)
		{
			m_projectiles.erase(m_projectiles.begin() + i);
			m_proj_dir.erase(m_proj_dir.begin() + i);
		}
	}

	drawProjectiles(win);

	if(!isBot)
	{
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			move(-500 * se::Engine::get().getLastTime(), 0);
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			move(500 * se::Engine::get().getLastTime(), 0);
		}

		//Enable All axis movement if needed
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			move(0, -500 * se::Engine::get().getLastTime());
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			move(0, 500 * se::Engine::get().getLastTime());
		}
	}
}


void StaticShip::drawProjectiles(sf::RenderTarget& target)
{
	for(se::uint i = 0; i < m_projectiles.size(); i++)
	{
		m_projectiles[i].move(m_proj_dir[i].x, m_proj_dir[i].y);
		target.draw(m_projectiles[i]);
	}
}


void StaticShip::shoot()
{
	if(m_tInterval.asMilliseconds() > m_shootingInterval.asMilliseconds())
	{
		m_tInterval = m_cInterval.restart();
		
		StaticProjectile p_left = generateDefaultProjectile(se::vec2i(-35, 12));
		StaticProjectile p_right = generateDefaultProjectile(se::vec2i(42, 12));
				
		if((m_projectiles.size() > m_proj_buffer_size + 1))
		{
			m_projectiles.erase(m_projectiles.begin());
			m_proj_dir.erase(m_proj_dir.begin());
		}
		else
		{
			if(m_shootingSound != nullptr)
				m_shootingSound->play();

			m_projectiles.push_back(p_left);
			m_projectiles.push_back(p_right);
			
			float Angle = static_cast<float>((getRotation() - 90) * 2 * se::pi / 360);
			float factor = 500 * se::Engine::get().getLastTime();
			se::vec2f fdir(std::cos(Angle) * factor, std::sin(Angle) * factor);

			m_proj_dir.push_back(fdir);
			m_proj_dir.push_back(fdir);
		}
	}
	else
		return;
}


void StaticShip::setShootSpeed(float milliseconds)
{
	m_shootingInterval = sf::milliseconds(static_cast<sf::Int32>(milliseconds));
}


void StaticShip::setShootDirection(se::vec2f dir)
{
	m_dir = dir;
}


void StaticShip::setShootSound(sf::Sound* snd)
{
	m_shootingSound = snd;
	m_shoot_sound_enabled = true;
}


void StaticShip::setProjectileBuffer(se::uint buffer)
{
	m_proj_buffer_size = buffer;
}


void StaticShip::enableShootSound(bool enable)
{
	m_shoot_sound_enabled = enable;
	if(enable == false)
		m_shootingSound = nullptr;
}


std::vector<se::vec2i> StaticShip::getProjectilePositions()
{
	std::vector<se::vec2i> temp_pos;

	for(se::uint i = 0; i < m_projectiles.size(); i++)
		temp_pos.push_back(
		static_cast<se::vec2i>(m_projectiles[i].getPosition()));

	return temp_pos;
}

StaticProjectile StaticShip::generateDefaultProjectile(se::vec2i ship_offset)
{
	StaticProjectile pj;
	pj.setSize(se::vec2f(5, 5));
	pj.setOutlineColor(sf::Color(255, 50, 50, 200));
	pj.setPosition(se::vec2f(getPosition().x + ship_offset.x,
	                         getPosition().y + ship_offset.y));

	pj.setFillColor(sf::Color::Magenta);

	return pj;
}
