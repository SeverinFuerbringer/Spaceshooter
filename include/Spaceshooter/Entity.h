#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics/RectangleShape.hpp>
#include "AnimatedSprite.hpp"
#include "Engine/EngineMath.hpp"
#include "Engine/EngineTypes.hpp"

// class for space sntity for non-animated objects
class StaticEntity : public sf::RectangleShape
{
public:
	StaticEntity();

	void pointToPosition(se::vec2i pos);
};


// class for space entity for animated objects
class AnimatedEntity : public AnimatedSprite
{
public:
	AnimatedEntity(sf::Time frameTime = sf::seconds(0.2f), bool paused = false, bool looped = true);
	
	void pointToPosition(se::vec2i pos);
};

#endif // Entity_H