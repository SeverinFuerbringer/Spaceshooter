//////////////////////////////////////////////////
//	Copyright © Severin Fürbringer 2014
//
//	Author: Severin Fürbringer
//	Jahr:	2014
//	Datei:	Level_000.h
//////////////////////////////////////////////////

#ifndef LEVEL_000_H
#define LEVEL_000_H

#include "Engine/Engine.h"
#include "Engine/ProgressBar.h"
#include "Ship.h"
#include "Fleet.h"
#include "Starfield.h"
#include "MainMenu.h"

#include <SFML/Audio.hpp>

class Level_000 : public se::Scene
{
public:
	Level_000();
	~Level_000();
	
	void loadContent();
	void unloadContent();
	void update(sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);

private:
	void initialize();
	
	// HUD, Score, Health
	se::uint m_score_count;
	se::ProgressBar* m_health_bar;
	se::HUD* m_score;

	// Ship stuff
	Fleet* m_fleet;
	Starfield m_parallax_starfield[3];
	std::vector<EnemyShip> e_ship;
	StaticShip* ship;
	sf::Texture m_ship_tx;

	
	// Sound
	sf::SoundBuffer m_laser_buffer;
	sf::Sound m_laser_sound;
	sf::SoundBuffer m_destroy_buffer;
	sf::Sound m_destroy_sound;

	// Time
	sf::Time m_respawn_t;
	sf::Clock m_clock;
};

#endif // LEVEL_000_H
