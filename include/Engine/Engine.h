//////////////////////////////////////////////////
//	Copyright © Severin Fürbringer 2014
//
//	Author: Severin Fürbringer
//	Jahr:	2014
//	Datei:	Engine.h
//////////////////////////////////////////////////

#ifndef ENGINE_H
#define ENGINE_H

#include "EngineExport.h"
#include "EngineErrorStrings.hpp"
#include "EngineMath.hpp"
#include "EngineTypes.hpp"
#include "Scene.h"
#include "FrameClock.h"

namespace se
{

class SEVENGINEDLL_API Engine
{
public:
	// Engine dTor.
	~Engine();

	// Get Engine instance
	static Engine& get();

	// Set the current RenderWindow
	void setRenderWindow(sf::RenderWindow* rw);

	// Initializes the engine
	void initialize(Scene* startup_scene, se::vec2u win_size, sf::Font);

	// Changes the window size
	void setFrameSize(se::vec2u win_size);

	// Switches to the new scene
	void switchScene(Scene* screen);

	// Loads the scene's content
	void loadContent();
	
	// Updates the current Scene (which the scene pointer holds)
	void update();

	// Updates the event and the current Scene (which the scene pointer holds)
	void update(sf::RenderWindow& window, sf::Event* e);

	// Calls render function
	void draw(sf::RenderWindow& window) const;

	void setGlobalFont(sf::Font font);
	sf::Font getGlobalFont();

	// Get Scenes
	Scene getCurrentScene();
	Scene getLastScene();
	
	vec2u getWinSize();

	// Returns pointer to the current sf::RenderWindow
	sf::RenderWindow* getRenderWindow();

	// Returns engine event
	sf::Event* getEvent();
	
	// Engine ticks & time
	float getLastTime();

	void shutDown();
	int shutDown(int exitcode);
	
	std::string debug_display;
	sfx::FrameClock frame_clock;
	sf::Event* m_event;
	
private:
	sf::RenderWindow* m_renderWindow;
	vec2u m_win_size;
	sf::Font m_globalFont;

	sf::Clock m_clock;

	Engine();
	Engine(Engine const&);
	void operator=(Engine const&);
};
} // namespace SevEngine

#endif // ENGINE_H
