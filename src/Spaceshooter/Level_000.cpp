//////////////////////////////////////////////////
//	Copyright © Severin Fürbringer 2014
//
//	Author: Severin Fürbringer
//	Jahr:	2014
//	Datei:	Level_000.cpp
//////////////////////////////////////////////////

#include "Level_000.h"

Level_000::Level_000()
{
}


Level_000::~Level_000()
{
}


void Level_000::loadContent()
{
	try
	{
		if(!m_ship_tx.loadFromFile("bin/gfx/SHIP_a.png"))
			throw se::Error::FilesMissing::Image();
		if(!m_laser_buffer.loadFromFile("bin/audio/Laser_Shoot.wav"))
			throw se::Error::FilesMissing::Audio();
		if(!m_destroy_buffer.loadFromFile("bin/audio/Explosion1.wav"))
			throw se::Error::FilesMissing::Audio();
	}
	catch(const char* error_message)
	{
		se::MsgBox::show(error_message, "Error", se::MsgBox::Icon::Error);
	}

	this->initialize();
}


void Level_000::unloadContent()
{
	delete ship;
	delete m_fleet;
}


void Level_000::update(sf::RenderWindow& window)
{
	m_parallax_starfield[0].update(se::vec2f(0,
	                               50 * se::Engine::get().getLastTime()));
	m_parallax_starfield[1].update(se::vec2f(0,
	                               100 * se::Engine::get().getLastTime()));
	m_parallax_starfield[2].update(se::vec2f(0,
	                               250 * se::Engine::get().getLastTime()));

	ship->update(window);

	se::uint i = m_fleet->update(ship->getProjectilePositions());
	m_score_count += (i * 100);

	ship->pointToPosition(sf::Mouse::getPosition(window));

	if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		ship->shoot();
	}

	m_score->setTextString("Score:\n" + std::to_string(m_score_count));

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		se::Engine::get().switchScene(new MainMenu);
}


void Level_000::draw(sf::RenderWindow& window)
{
	window.draw(m_parallax_starfield[0]);
	window.draw(m_parallax_starfield[1]);
	window.draw(m_parallax_starfield[2]);
	window.draw(*m_fleet);
	window.draw(*ship);
	window.draw(*m_health_bar);
	window.draw(*m_score);
}


void Level_000::initialize()
{
	// Score
	sf::Text score("Score:\n 0", se::Engine::get().getGlobalFont());
	score.setColor(sf::Color(200, 200, 220, 230));

	m_score = new se::HUD(se::vec2u(200, 150),
		se::vec2i(se::Engine::get().getWinSize().x - 200,
		se::Engine::get().getWinSize().y - 100), score);
	m_score->setTextPosition(se::vec2i(10, 10));
	m_score->getBox().setFillColor(sf::Color(100, 150, 150, 150));

	// Health bar
	sf::Text hlt("Health", se::Engine::get().getGlobalFont());
	hlt.setColor(sf::Color(200, 200, 220, 230));
	m_health_bar = new se::ProgressBar(se::vec2u(200, 75),
		se::vec2i(10, se::Engine::get().getWinSize().y - 100), hlt);

	m_health_bar->setTextPosition(se::vec2i(0, -50));
	m_health_bar->getBox().setFillColor(sf::Color(50, 50, 100, 150));
	m_health_bar->getProgressBar().setFillColor(sf::Color(150, 50, 50, 150));
	m_health_bar->getBox().setOutlineColor(sf::Color(255, 255, 255, 50));
	m_health_bar->getBox().setOutlineThickness(2.0f);

	// Parralax starfield background
	m_parallax_starfield[0].setStarAmount(20);
	m_parallax_starfield[0].setStarRadius(1);
	m_parallax_starfield[0].setPointAmount(7);
	m_parallax_starfield[1].setStarAmount(15);
	m_parallax_starfield[1].setStarRadius(2);
	m_parallax_starfield[1].setPointAmount(9);
	m_parallax_starfield[2].setStarAmount(5);
	m_parallax_starfield[2].setStarRadius(3);
	m_parallax_starfield[2].setPointAmount(9);

	m_laser_sound.setBuffer(m_laser_buffer);
	m_laser_sound.setVolume(0.75f);

	ship = new StaticShip(&m_ship_tx, se::vec2f(0, 450), false);
	ship->setScale(4.0f, 4.0f);
	ship->setShootSpeed(100);
	ship->setShootSound(&m_laser_sound);
	ship->setOrigin(se::vec2f(15, 15));

	m_destroy_sound.setBuffer(m_destroy_buffer);
	m_fleet = new Fleet(5, se::vec2i(100, 100), m_ship_tx, sf::seconds(0.1f));
	m_destroy_sound.setVolume(0.75f);
	m_fleet->setDestroySound(m_destroy_sound);
}