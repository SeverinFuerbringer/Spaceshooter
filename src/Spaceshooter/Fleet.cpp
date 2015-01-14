#include "Fleet.h"

Fleet::Fleet(se::uint ships, se::vec2i spawnpoint, sf::Texture tex, sf::Time respawninterval)
	: m_texture(tex), m_respawnDuration(respawninterval),
	m_spawn_sound_enabled(false), m_destroy_sound_enabled(false),
	m_spawn_point(spawnpoint)

{
	for(se::uint i = 0; i <= ships; i++)
	{
		generateNewShip();
	}
}

Fleet::~Fleet()
{
	m_fleet.clear();
}

void Fleet::update()
{
	m_lastRespawn = m_clock.getElapsedTime();
	generateNewShip();

	if(m_lastRespawn > m_respawnDuration)
	{
		// Generate new ship if the time has come
		deleteDeadShips();
	}

	cruise();
}

se::uint Fleet::update(std::vector<se::vec2i> projectiles)
{
	m_lastRespawn = m_clock.getElapsedTime();
	deleteDeadShips();

	if(m_lastRespawn > m_respawnDuration)
	{
		// Generate new ship if the time has come
		generateNewShip();
	}

	cruise();
	return checkHit(projectiles);
}


void Fleet::setSpawnSound(sf::Sound s)
{
	m_spawn_sound_enabled = true;
	m_spawn_sound = s;
}


void Fleet::toggleSpawnSound(bool val)
{
	m_spawn_sound_enabled = val;
}


void Fleet::setDestroySound(sf::Sound s)
{
	m_destroy_sound_enabled = true;
	m_destroy_sound = s;
}


void Fleet::toggleDestroySound(bool val)
{
	m_destroy_sound_enabled = val;
}


void Fleet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for(auto& i : m_fleet)
	{
		target.draw(i, states);
	}
}


void Fleet::deleteDeadShips()
{
	for(se::uint i = 0; i < m_fleet.size(); i++)
	{
		if(m_fleet[i].getFillColor() == sf::Color::Transparent)
		{
			m_fleet.erase(m_fleet.begin() + i);
		}
	}
}


void Fleet::generateNewShip()
{
	if(m_spawn_sound_enabled)
		m_spawn_sound.play();

	EnemyShip shp(&m_texture, se::vec2f(static_cast<float>(m_spawn_point.x),
		static_cast<float>(m_spawn_point.y)), true);
	shp.setScale(3, 3);
	shp.rotate(180.0f);
	shp.setShootDirection(se::vec2f(0, 7));
	m_fleet.push_back(shp);
	m_clock.restart();
}


void Fleet::cruise()
{
	for(auto& i : m_fleet)
	{
		i.shoot();
		if(i.getPosition().x >= se::Engine::get().getRenderWindow()->getSize().x)
			i.goLeft();
		if(i.getPosition().x < i.getSize().x)
			i.goRight();
		i.cruise();
	}
}


void Fleet::setSpawnpoint(se::vec2i sp)
{
	m_spawn_point = sp;
}


void Fleet::pointAllTo(se::vec2i p)
{
	for(auto& i : m_fleet)
	{
		i.pointToPosition(p);
	}
}


se::uint Fleet::checkHit(std::vector<se::vec2i> projectiles)
{
	se::uint destroyed_ships = 0;

	for(auto& i : m_fleet)
	{
		for(auto& x : projectiles)
		{
			if(i.getGlobalBounds().contains(static_cast<se::vec2f>(x)))
			{
				destroyed_ships++;
				// Make the Ships ready for deallocation
				i.setFillColor(sf::Color::Transparent);
				if(m_destroy_sound_enabled)
					m_destroy_sound.play();
			}
		}
	}

	return destroyed_ships;
}