//////////////////////////////////////////////////
//	Copyright © Severin Fürbringer 2014
//
//	Author: Severin Fürbringer
//	Jahr:	2014
//	Datei:	SplashScreen.cpp
//////////////////////////////////////////////////

#include "SplashScreen.h"
#include "MainMenu.h"
#include "Engine/Engine.h"

SplashScreen::SplashScreen()
{
}

SplashScreen::~SplashScreen()
{
}


void SplashScreen::loadContent()
{
	try
	{
		// Load gfx
		if(!m_splash_texture.loadFromFile("bin/gfx/splashscreen/l4dhand.jpeg"))
			throw se::Error::FilesMissing::Image();

		// Load font
		if(!m_font.loadFromFile("bin/gfx/fonts/space_age.ttf"))
			throw se::Error::FilesMissing::Font();
	}
	catch(const char* error_message)
	{
		se::MsgBox::show(error_message, "Error", se::MsgBox::Icon::Error);
		exit(EXIT_FAILURE);
	}
	this->initialize();
}


void SplashScreen::unloadContent()
{

}


void SplashScreen::update(sf::RenderWindow& window)
{
	if(trns->done)
		se::Engine::get().switchScene(new MainMenu);
}


void SplashScreen::draw(sf::RenderWindow& window)
{
	window.draw(m_splash);
	window.draw(m_text);
	trns->animate();
}


void SplashScreen::initialize()
{
	m_text.setString("	 Severin's\nSpace Shooter");
	m_text.setFont(m_font);
	m_text.setCharacterSize(48);
	
	float text_x = static_cast<float>(se::Engine::get().getWinSize().x/7);
	float text_y = static_cast<float>(se::Engine::get().getWinSize().y/4);
	se::vec2f mt(text_x, text_y);
	m_text.setPosition(mt);
	m_text.setColor(sf::Color(5, 7, 7));

	m_splash.setTexture(&m_splash_texture);
	m_splash.setPosition(se::vec2f(0, 0));
	
	float m_x = static_cast<float>(se::Engine::get().getWinSize().x);
	float m_y = static_cast<float>(se::Engine::get().getWinSize().y);
	m_splash.setSize(se::vec2f(m_x, m_y));

	trns = new se::Transition(se::Transition::Fade, sf::Color::Black, 0, 155, sf::seconds(2), se::Engine::get().getRenderWindow());
}
