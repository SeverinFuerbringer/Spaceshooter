//////////////////////////////////////////////////
//	Copyright © Severin Fürbringer 2014
//
//	Author: Severin Fürbringer
//	Jahr:	2014
//	Datei:	EnemyShip.cpp
//////////////////////////////////////////////////

#include "EnemyShip.h"

EnemyShip::EnemyShip(sf::Color col, se::vec2f pos, bool bot = true)
	: StaticShip(col, pos, bot)
{
}
																	  

EnemyShip::EnemyShip(sf::Texture* texture, se::vec2f pos, bool bot = true)
	:	StaticShip(texture, pos, bot)
{
}
	


EnemyShip::~EnemyShip()
{
}


void EnemyShip::cruise()
{
	if(m_dir == Right)
		this->move(100 * se::Engine::get().getLastTime(), 0);
	else if(m_dir == Left)
		this->move(-100 * se::Engine::get().getLastTime(), 0);
}


void EnemyShip::goLeft()
{
	this->m_dir = Left;
}


void EnemyShip::goRight()
{
	this->m_dir = Right;
}
