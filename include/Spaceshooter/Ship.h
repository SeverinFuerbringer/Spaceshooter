//////////////////////////////////////////////////
//	Copyright © Severin Fürbringer 2014
//
//	Author: Severin Fürbringer
//	Jahr:	2014
//	Datei:	Ship.h
//////////////////////////////////////////////////

#ifndef SHIP_H
#define SHIP_H

#include "Engine/Engine.h"
#include "Entity.h"
#include "Projectile.h"

#include <SFML/Audio.hpp>
#include <vector>

class StaticShip : public StaticEntity
{
public:
	StaticShip(sf::Color col, se::vec2f pos, bool bot = true);
	StaticShip(sf::Texture* texture, se::vec2f pos, bool bot = true);
	bool isMovingLeft();
	bool isMovingRight();

	void update(sf::RenderWindow& win);
	void drawProjectiles(sf::RenderTarget& target);
	void shoot();
	void setShootSpeed(float milliseconds);
	void setShootDirection(se::vec2f dir);
	void setShootSound(sf::Sound* snd);
	void setProjectileBuffer(se::uint buffer);
	void enableShootSound(bool enable);
	
	std::vector<se::vec2i> getProjectilePositions();
	
protected:
	//void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	se::uint m_proj_buffer_size;
	std::vector<StaticProjectile> m_projectiles;

	sf::Time m_tInterval;
	sf::Clock m_cInterval;
	
	bool isBot;
	bool m_shoot_sound_enabled;

	sf::Sound* m_shootingSound;
	sf::Time m_shootingInterval;
	se::vec2f m_dir;
	std::vector<se::vec2f> m_proj_dir;
	sf::RenderWindow *m_win;


	StaticProjectile generateDefaultProjectile(se::vec2i ship_offset);
};

class AnimatedShip: public AnimatedEntity, public StaticShip
{
public:
	AnimatedShip(se::vec2f pos, sf::Time frameTime = sf::seconds(0.2f),
		bool bot = true, bool paused = false, bool looped = true)
		: StaticShip(sf::Color::Black, pos, bot),
		AnimatedEntity(frameTime, paused, looped)
	{
		
	}

};

#endif