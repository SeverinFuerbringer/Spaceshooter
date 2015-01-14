//////////////////////////////////////////////////
//	Copyright © Severin Fürbringer 2014
//
//	Author: Severin Fürbringer
//	Jahr:	2014
//	Datei:	Starfield.cpp
//////////////////////////////////////////////////

#include "Starfield.h"

Starfield::Starfield()
	: m_star_amount(10), m_star_radius(2), m_point_amount(4)
{
	generateStarfield();
}


Starfield::Starfield(se::uint stars, float starRadius, se::uint pointAmount)
	: m_star_amount(stars), m_star_radius(starRadius), m_point_amount(pointAmount)
{
	generateStarfield();
}


Starfield::~Starfield()
{
}


void Starfield::setStarAmount(se::uint stars)
{
	m_star_amount = stars;
}


void Starfield::setPointAmount(se::uint pointAmount)
{
	m_point_amount = pointAmount;
}


void Starfield::setStarRadius(float radius)
{
	m_star_radius = radius;
}


void Starfield::generateStarfield()
{
	m_stars.clear();
	for(se::uint i = 0; i < m_star_amount; i++)
	{
		sf::CircleShape cs(m_star_radius, m_point_amount);

		se::vec2f p(static_cast<float>(se::Random::get().Double(
			0, se::Engine::get().getRenderWindow()->getSize().x)),
			static_cast<float>(se::Random::get().Double(
			0, se::Engine::get().getRenderWindow()->getSize().y)));

		cs.setFillColor(sf::Color::White);
		cs.setPosition(p);
		cs.setRotation(static_cast<float>(se::Random::get().Double(0, 360)));
		cs.setOutlineThickness(static_cast<float>(se::Random::get().Int(0, 3)));
		cs.setOutlineColor(sf::Color(240, 250, 255, static_cast<sf::Uint8>(se::Random::get().Int(0, 200))));
		m_stars.push_back(cs);
	}
}


void Starfield::update(se::vec2f moveOffset, bool move)
{
	// Star is out of the screen
	for(se::uint i = 0; i < m_stars.size(); i++)
	{
		if(m_stars[i].getPosition().y > se::Engine::get().getWinSize().y)
			m_stars.erase(m_stars.begin() + i);
	}
	// Move stars
	if(move)
	{
		for(se::uint i = 0; i < m_stars.size(); i++)
		{
			m_stars[i].move(se::vec2f(moveOffset));
		}
	}
	// New stars needed?
	if(m_stars.size() < m_star_amount)
	{
		sf::CircleShape cs(m_star_radius, m_point_amount);
		cs.setFillColor(sf::Color::White);
		cs.setPosition(static_cast<float>(se::Random::get().Double(
			0, se::Engine::get().getRenderWindow()->getSize().x)),
			-static_cast<float>(se::Random::get().Int(1, 100)));
		cs.setRotation(static_cast<float>(se::Random::get().Double(0, 360)));
		cs.setOutlineThickness(static_cast<float>(se::Random::get().Double(0, 2)));
		cs.setOutlineColor(
		sf::Color(240, 250, 255, static_cast<sf::Uint8>(se::Random::get().Int(0, 200)))
		);

		m_stars.push_back(cs);
	}
}


void Starfield::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for(auto& i : m_stars)
	{
		target.draw(i, states);
	}
}