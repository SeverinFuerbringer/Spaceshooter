//////////////////////////////////////////////////
//	Copyright © Severin Fürbringer 2014
//
//	Author: Severin Fürbringer
//	Jahr:	2014
//	Datei:	GameLoop.cpp
//////////////////////////////////////////////////

#include "GameLoop.h"

AppStartupOptions::AppStartupOptions()
	: Icon(""), Fps(30), Vsync(false), DebugMode(false),
	Style(sf::Style::Default), VideoMode(sf::VideoMode(800, 600, 32))
{
}

bool SpaceShooter::initialize(AppStartupOptions aso, se::Scene* startup, sf::Uint32 style)
{
	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 0;
	settings.majorVersion = 3;
	settings.minorVersion = 0;

	m_win.create(aso.VideoMode, "Severin's Space Shooter", style, settings);
	m_win.setVerticalSyncEnabled(aso.Vsync);

	sf::Image w_icon;

	if(!w_icon.loadFromFile(aso.Icon))
	{
		// Could not load icon, show error & exit
		se::MsgBox::show("Error", "Could not load window icon.", se::MsgBox::Icon::Error);
		return false;
	}
	else
	{
		// Set the icon
		m_win.setIcon(64, 64, w_icon.getPixelsPtr());
	}

	if(m_font.loadFromFile("bin/gfx/fonts/boombox2.ttf"))
	{
		m_debug_display.setCharacterSize(18);
		m_debug_display.setFont(m_font);
		m_debug_display.setPosition(se::vec2f(10, 10));
		m_debug_display.setString("Calculating...");
		debug = aso.DebugMode;
	}
	else
		return false;

	if(m_win.isOpen())
	{
		se::Engine::get().setRenderWindow(&m_win);
		se::Engine::get().initialize(startup, se::vec2u(m_win.getSize().x,
			m_win.getSize().y), m_font);
		se::Engine::get().loadContent();

		if(!aso.Vsync)
			m_win.setFramerateLimit(aso.Fps);
		m_win.setKeyRepeatEnabled(false);
	}
	else
		return false;


	// Set the Engine event pointer to
	// something so it doesn't point to nullptr
	se::Engine::get().m_event = &m_event;

	return true;
}


void SpaceShooter::gameLoop()
{
	se::GameTime gt;

	// The Gameloop:
	while(m_win.isOpen())
	{
		if(m_win.hasFocus())
		{
			while(m_win.pollEvent(m_event))
			{
				// Handle closing of window
				if(m_event.type == sf::Event::Closed /*|| (m_event.type ==
					sf::Event::KeyReleased && sf::Keyboard::F4 && m_event.key.alt)*/)
				{
					m_win.close();
				}
			}
			
			gt.tick();

			while(gt.readyForNextUpdate())
			{
				m_win.clear();

				// Update ////////////////////////////
				se::Engine::get().update(m_win, &m_event);
				updateDebugDisplay();
				//////////////////////////////////////

				// Draw //////////////////////////////
				se::Engine::get().frame_clock.beginFrame();
				se::Engine::get().draw(m_win);
				if(debug)
					m_win.draw(m_debug_display);
				se::Engine::get().frame_clock.endFrame();
				//////////////////////////////////////

				m_win.display();
				
				gt.update();
			}
		}
	}

	//se::uint next_game_tick = se::Engine::get().getTicks();
	//int loops;
	//
	//// The Gameloop:
	//while(m_win.isOpen())
	//{
	//	if(m_win.hasFocus())
	//	{
	//		while(m_win.pollEvent(m_event))
	//		{
	//			// Handle closing of window
	//			if(m_event.type == sf::Event::Closed /*|| (m_event.type ==
	//				sf::Event::KeyReleased && sf::Keyboard::F4 && m_event.key.alt)*/)
	//			{
	//				m_win.close();
	//			}
	//		}
	//		
	//		loops = 0;
	//		se::Engine::get().tick();
	//		while(se::Engine::get().getTicks() > next_game_tick &&
	//			loops < se::Engine::get().getMaxFrameSkip())
	//		{
	//			m_win.clear();
	//
	//			// Update ////////////////////////////
	//			se::Engine::get().update(m_win, &m_event);
	//			updateDebugDisplay();
	//			//////////////////////////////////////
	//
	//			// Draw //////////////////////////////
	//			se::Engine::get().frame_clock.beginFrame();
	//			se::Engine::get().draw(m_win);
	//			if(debug)
	//				m_win.draw(m_debug_display);
	//			se::Engine::get().frame_clock.endFrame();
	//			//////////////////////////////////////
	//
	//			m_win.display();
	//			
	//			next_game_tick += se::Engine::get().getSkipTicks();
	//			loops++;
	//		}
	//	}
	//}
	
	//const int TICKS_PER_SECOND = 60;
	//   const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
	//   const int MAX_FRAMESKIP = 10;
	//
	//   DWORD next_game_tick = GetTickCount();
	//   int loops;
	//
	//// The Gameloop:
	//while(m_win.isOpen())
	//{
	//	while(m_win.pollEvent(m_event))
	//	{
	//		if(m_event.type == sf::Event::Closed ||
	//			(m_event.type == sf::Event::KeyReleased &&
	//			sf::Keyboard::F4 && m_event.key.alt))
	//		{
	//			m_win.close();
	//		}
	//	}
	//
	//	if(m_win.hasFocus())
	//	{
	//	 loops = 0;
	//	 while( GetTickCount() > next_game_tick && loops < MAX_FRAMESKIP) {
	//		se::Engine::get().frame_clock.beginFrame();
	//
	//		m_win.clear();
	//
	//		// Update ////////////////////////////
	//		se::Engine::get().update(m_win, &m_event);
	//		updateDebugDisplay();
	//		//////////////////////////////////////
	//
	//		// Draw //////////////////////////////
	//		se::Engine::get().draw(m_win);
	//		if(debug)
	//			m_win.draw(m_debug_display);
	//		//////////////////////////////////////
	//
	//		m_win.display();
	//
	//		se::Engine::get().frame_clock.endFrame();
	//		next_game_tick += SKIP_TICKS;
	//           loops++;
	//	 }
	//	}
	//}
}


void SpaceShooter::updateDebugDisplay()
{
	m_debug_display_time = m_debug_display_clock.getElapsedTime();
	if(debug && m_debug_display_time.asSeconds() >= 0.2f)
	{
		m_debug_display.setString("FPS: " + std::to_string((se::uint)se::Engine::get().frame_clock.getFramesPerSecond()) +
			"\nAVG FPS: " + std::to_string((se::uint)se::Engine::get().frame_clock.getAverageFramesPerSecond()) +
			"\nMAX FPS: " + std::to_string((se::uint)se::Engine::get().frame_clock.getMaxFramesPerSecond()) +
			"\nMIN FPS: " + std::to_string((se::uint)se::Engine::get().frame_clock.getMinFramesPerSecond()) +
			"\nFRAMECOUNT: " + std::to_string(se::Engine::get().frame_clock.getTotalFrameCount()) +
			"\nFRAMETIME: " + std::to_string(se::Engine::get().frame_clock.getLastFrameTime().asMilliseconds()) +
			se::Engine::get().debug_display.c_str()
			);

		m_debug_display_clock.restart();
	}
	else if(!debug)
		m_debug_display.setString("");
}