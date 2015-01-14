//////////////////////////////////////////////////
//	Copyright © Severin Fürbringer 2014
//
//	Author: Severin Fürbringer
//	Jahr:	2014
//	Datei:	MenuCredits.cpp
//////////////////////////////////////////////////

#include "MenuCredits.h"
#include "MainMenu.h"
#include "Engine/Engine.h"

MenuCredits::MenuCredits()
{
}


MenuCredits::~MenuCredits()
{
}


void MenuCredits::loadContent()
{
	try
	{
		if(!m_font.loadFromFile("bin/gfx/fonts/boombox2.ttf") ||
			!m_back_button_font.loadFromFile("bin/gfx/fonts/space_age.ttf"))
			throw se::Error::FilesMissing::Font();
		
		if(!m_background_texture.loadFromFile("bin/gfx/menuscreen/credits_background.png"))
			throw se::Error::FilesMissing::Image();
	}
	catch(const char* error_message)
	{
		se::MsgBox::show(error_message, "Error", se::MsgBox::Icon::Error);
	}
	this->initialize();
}


void MenuCredits::unloadContent()
{
	delete trns;
}


void MenuCredits::update(sf::RenderWindow& window)
{
	if(m_back.getDrawable().getGlobalBounds().contains(se::vec2f(sf::Mouse::getPosition(window))))
	{
		if(se::Engine::get().getEvent()->type == sf::Event::MouseButtonPressed
			&& se::Engine::get().getEvent()->mouseButton.button == sf::Mouse::Left)
		{
			se::Engine::get().switchScene(new MainMenu);
			return;
		}
		else
		{
			m_back.getDrawableText().setColor(sf::Color(4, 4, 4, 255));
			m_back.getDrawable().setOutlineThickness(5.0f);
		}
	}
	else
	{
		m_back.getDrawableText().setColor(sf::Color(50, 40, 40, 200));
		m_back.getDrawable().setOutlineThickness(0.0f);
	}
}


void MenuCredits::draw(sf::RenderWindow& window)
{
	window.draw(m_background);
	window.draw(m_text_background);
	window.draw(m_credits_text);
	m_back.draw(window);
	if(!trns->done)
		trns->animate();
}


void MenuCredits::initialize()
{
	// Background
	m_background.setTexture(&m_background_texture);
	m_background.setPosition(se::vec2f(0, 0));
	m_background.setSize((se::vec2f)se::Engine::get().getWinSize());	


	// Background text
	m_text_background.setFillColor(sf::Color(30, 75, 200, 100));
	m_text_background.setPosition(se::vec2f(0, 0));
	m_text_background.setSize((se::vec2f)se::Engine::get().getWinSize());

	// Credits
	m_credits_text.setString("CREDITS\n\nSeverin's Space Shooter\n"
		"By Severin Fuerbringer\n\nTools used:\n\nSFML library: "
		"sfml-dev.org\n\nSource code available"
		"here:\nhttp://furbringer.com/INSRTSRC");
	m_credits_text.setFont(m_font);
	m_credits_text.setCharacterSize(18);
	m_credits_text.setColor(sf::Color(sf::Color(5, 5, 5, 255)));
	m_credits_text.setPosition(se::vec2f(
		static_cast<float>(se::Engine::get().getWinSize().x/40),
		static_cast<float>(se::Engine::get().getWinSize().y/20)));
	
	// Backbutton
	m_back.setElementColor(sf::Color(20, 220, 220, 120));
	m_back.setFontColor(sf::Color(50, 40, 40, 200));
	m_back.setString("back");
	m_back.setFont(m_back_button_font);
	m_back.setPosition(se::vec2u((se::uint)(se::Engine::get().getWinSize().x/1.5f),
		(se::uint)(se::Engine::get().getWinSize().y/1.2f)));
	m_back.setSize(se::vec2u(240, 80));
	m_back.getDrawable().setOutlineColor(sf::Color(5, 10, 10, 250));
	m_back.getDrawable().setOutlineThickness(5.0f);

	trns = new se::Transition(se::Transition::Fade,
		sf::Color::Black, 255, 0, sf::seconds(1),
		se::Engine::get().getRenderWindow());
}
