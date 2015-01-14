//////////////////////////////////////////////////
//	Copyright © Severin Fürbringer 2014
//
//	Author: Severin Fürbringer
//	Jahr:	2014
//	Datei:	EnemyShip.h
//////////////////////////////////////////////////

#ifndef ENEMYSHIP_H
#define ENEMYSHIP_H

#include "Ship.h"

class EnemyShip : public StaticShip
{
public:
	//using Ship::Ship;
	EnemyShip(sf::Color col, se::vec2f pos, bool bot);
	EnemyShip(sf::Texture* tex, se::vec2f pos, bool bot);
	~EnemyShip();
	void cruise();

	void goLeft();
	void goRight();

private:
	enum Direction
	{
		Left,
		Right,
		None
	};
	
	Direction m_dir = Right;
};

#endif
