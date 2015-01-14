//////////////////////////////////////////////////
//	Copyright © Severin Fürbringer 2014
//
//	Author: Severin Fürbringer
//	Jahr:	2014
//	Datei:	MenuOptions.cpp
//////////////////////////////////////////////////

#include "MenuOptions.h"
#include "MainMenu.h"

MenuOptions::MenuOptions()
{
}


MenuOptions::~MenuOptions()
{
}


void MenuOptions::loadContent()
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


void MenuOptions::unloadContent()
{
	delete trns;
}


void MenuOptions::update(sf::RenderWindow& window)
{
		if(m_back.getDrawable().getGlobalBounds().contains(se::vec2f(
			static_cast<float>(sf::Mouse::getPosition(window).x),
			static_cast<float>(sf::Mouse::getPosition(window).y))))
	{
		if(se::Engine::get().getEvent()->type == sf::Event::MouseButtonPressed &&
			se::Engine::get().getEvent()->mouseButton.button == sf::Mouse::Left)
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


void MenuOptions::draw(sf::RenderWindow& window)
{
	window.draw(m_background);
	m_back.draw(window);
	if(!trns->done)
		trns->animate();
}


void MenuOptions::initialize()
{
	m_background.setTexture(&m_background_texture);
	m_background.setPosition(se::vec2f(0, 0));
	m_background.setSize((se::vec2f)se::Engine::get().getWinSize());

	m_back.setElementColor(sf::Color(20, 220, 220, 120));
	m_back.setFontColor(sf::Color(50, 40, 40, 200));
	m_back.setString("back");
	m_back.setFont(m_back_button_font);
	m_back.setPosition(se::vec2u((se::uint)(se::Engine::get().getWinSize().x/1.5f),
		(se::uint)(se::Engine::get().getWinSize().y/1.2f)));
	m_back.setSize(se::vec2u(240, 80));

	m_back.getDrawable().setOutlineColor(sf::Color(10, 20, 20, 230));
	m_back.getDrawable().setOutlineThickness(5.0f);

	trns = new se::Transition(se::Transition::Fade, sf::Color::Black, 255, 0, sf::seconds(1), se::Engine::get().getRenderWindow());
}