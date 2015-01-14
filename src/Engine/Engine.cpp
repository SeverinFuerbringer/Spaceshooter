//////////////////////////////////////////////////
//	Copyright © Severin Fürbringer 2014
//
//	Author: Severin Fürbringer
//	Jahr:	2014
//	Datei:	Engine.cpp
//////////////////////////////////////////////////

#include "Engine.h"

namespace se
{

// Engine class:

Scene *current_scene, *new_scene, *last_scene;

void Engine::setRenderWindow(sf::RenderWindow* rw)
{
	this->m_renderWindow = rw;
}


Engine& Engine::get()
{
	static Engine instance;
	return instance;
}


Engine::Engine()
{
}


Engine::~Engine()
{
	delete current_scene;
	delete last_scene;
}


void Engine::initialize(Scene* startup_scene, se::vec2u win_size, sf::Font globalFont)
{
	this->m_win_size = win_size;
	frame_clock.setSampleDepth(100);
	current_scene = startup_scene;
	m_globalFont = globalFont;
}


void Engine::setFrameSize(se::vec2u win_size)
{
	this->m_win_size = win_size;
}


void Engine::switchScene(Scene *screen)
{
	current_scene->unloadContent();
	delete current_scene;
	current_scene = screen;
	current_scene->loadContent();
}


void Engine::loadContent()
{
	current_scene->loadContent();
}


void Engine::update()
{
	debug_display = "";
	current_scene->update();
}


void Engine::update(sf::RenderWindow& window, sf::Event* e)
{
	debug_display = "";
	current_scene->update(window);
	m_event = e;
}


void Engine::draw(sf::RenderWindow& window) const
{
	current_scene->draw(window);
}


void Engine::setGlobalFont(sf::Font font)
{
	m_globalFont = font;
}


sf::Font Engine::getGlobalFont()
{
	return m_globalFont;
}


Scene Engine::getCurrentScene()
{
	return *current_scene;
}


Scene Engine::getLastScene()
{
	return *last_scene;
}


vec2u Engine::getWinSize()
{
	return m_win_size;
}


sf::RenderWindow* Engine::getRenderWindow()
{
	return m_renderWindow;
}


sf::Event* Engine::getEvent()
{
	return m_event;
}


float Engine::getLastTime()
{
	return 0.01f;
}


void Engine::shutDown()
{
	current_scene->unloadContent();
	std::exit(0);
}


int Engine::shutDown(int exitcode)
{
	current_scene->unloadContent();
	Engine::get().getRenderWindow()->close();
	return exitcode;
}
} // namespace SevEngine