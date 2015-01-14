#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Engine/EngineMath.hpp"
#include "Engine/EngineTypes.hpp"
#include "Entity.h"

class Projectile
{
};

class StaticProjectile : public Projectile, public StaticEntity
{
public:
	StaticProjectile();
};

class AnimatedProjectile : public Projectile, public AnimatedEntity
{
public:
	AnimatedProjectile(sf::Time frameTime = sf::seconds(0.2f), bool paused = false, bool looped = true);
};

#endif // PROJECTILE_H