//////////////////////////////////////////////////
//	Copyright © Severin Fürbringer 2014
//
//	Author: Severin Fürbringer
//	Jahr:	2014
//	Datei:	Starfield.h
//////////////////////////////////////////////////

#ifndef STARFIELD_H
#define STARFIELD_H

#include <vector>
#include "Engine/Engine.h"
#include "Engine/EngineRandom.h"

class Starfield : public sf::Drawable
{
public:
	Starfield();
	Starfield(se::uint stars, float starRadius, se::uint pointAmount);
	~Starfield();

	void setStarAmount(se::uint stars);
	void setPointAmount(se::uint pointAmount);
	void setStarRadius(float radius);
	void generateStarfield();
	void update(se::vec2f moveOffset, bool move = true);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	
	se::uint m_star_amount;
	se::uint m_point_amount;
	float m_star_radius;
	std::vector<sf::CircleShape> m_stars;
};

#endif