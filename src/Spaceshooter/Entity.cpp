#include "Entity.h"

StaticEntity::StaticEntity()
{
}


void StaticEntity::pointToPosition(se::vec2i pos)
{
	se::vec2f curPos = this->getPosition();
	se::vec2i position = pos;

	float dx = curPos.x - position.x;
	float dy = curPos.y - position.y;

	float rotation = static_cast<float>((std::atan2(dy, dx)) * 180 / se::pi);
	this->setRotation(rotation - 90);
}


AnimatedEntity::AnimatedEntity(sf::Time frameTime, bool paused, bool looped)
	: AnimatedSprite(frameTime, paused, looped)
{
}


void AnimatedEntity::pointToPosition(se::vec2i pos)
{
	se::vec2f curPos = this->getPosition();
	se::vec2i position = pos;

	float dx = curPos.x - position.x;
	float dy = curPos.y - position.y;

	float rotation = static_cast<float>((std::atan2(dy, dx)) * 180 / se::pi);
	this->setRotation(rotation - 90);
}