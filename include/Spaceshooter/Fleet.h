#ifndef FLEET_H
#define FLEET_H

#include "Engine/Engine.h"
#include "Engine/EngineRandom.h"
#include "EnemyShip.h"
#include <vector>

// Mit dieser Klasse kann man
// eine Flotte von Raumschiffen generieren
class Fleet : public sf::Drawable
{
public:
	Fleet(se::uint ships, se::vec2i spawnpoint, sf::Texture tex, sf::Time respawninterval);
	~Fleet();

	void update();
	// Also returns the amount of destroyed ships
	se::uint update(std::vector<se::vec2i> projectiles);
	
	void setSpawnSound(sf::Sound s);
	void toggleSpawnSound(bool val);

	void setDestroySound(sf::Sound s);
	void toggleDestroySound(bool val);
	void pointAllTo(se::vec2i p);
	void setSpawnpoint(se::vec2i sp);

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void deleteDeadShips();
	void generateNewShip();
	void cruise();
	se::uint checkHit(std::vector<se::vec2i> projectiles);

	sf::Time m_respawnDuration;
	sf::Time m_lastRespawn;
	sf::Clock m_clock;
	sf::Texture m_texture;
	std::vector<EnemyShip> m_fleet;
	se::vec2i m_spawn_point;

	sf::Sound m_spawn_sound;
	bool m_spawn_sound_enabled;

	sf::Sound m_destroy_sound;
	bool m_destroy_sound_enabled;
};

#endif // FLEET_H