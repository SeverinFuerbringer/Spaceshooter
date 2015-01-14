#include "Projectile.h"

StaticProjectile::StaticProjectile()
{
}


AnimatedProjectile::AnimatedProjectile(sf::Time frameTime, bool paused, bool looped)
	: AnimatedEntity(frameTime, paused, looped)
{
}