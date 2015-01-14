//////////////////////////////////////////////////
//	Copyright © Severin Fürbringer 2014
//
//	Author: Severin Fürbringer
//	Jahr:	2014
//	Datei:	GameLoop.h
//////////////////////////////////////////////////

#include "Engine/Engine.h"
#include "Engine/GameTime.h"

struct AppStartupOptions
{
	char* Icon;
	se::uint Fps;
	sf::Uint32 Style;
	sf::VideoMode VideoMode;
	bool Vsync;
	bool DebugMode;

	AppStartupOptions();
};


class SpaceShooter
{
public:
	bool initialize(AppStartupOptions aso, se::Scene* startup, sf::Uint32 style);
	void gameLoop();

private:
	void updateDebugDisplay();

public:
	int argc;
	char** argv;
	bool debug;
	se::uint frame_rate;

	sf::Event m_event;
	sf::Clock m_debug_display_clock;
	sf::Time m_debug_display_time;
	sf::Font m_font;
	sf::Text m_debug_display;
	sf::Image m_win_icon;
	sf::RenderWindow m_win;
};