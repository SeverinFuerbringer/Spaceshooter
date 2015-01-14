//////////////////////////////////////////////////
//	Copyright © Severin Fürbringer 2014
//
//	Author: Severin Fürbringer
//	Jahr:	2014
//	Datei:	main.cpp
//////////////////////////////////////////////////

#include "MainMenu.h"
#include "GameLoop.h"

void handleCommandInput(int, char**, AppStartupOptions*);

int main(int argc, char* argv[])
try
{
	SpaceShooter ss;
	AppStartupOptions aso;

	aso.Icon = "bin/gfx/SHIP_a.png";
	aso.Vsync = false;
	aso.VideoMode = sf::VideoMode(800, 600);
	aso.Fps = 60;

	handleCommandInput(argc, argv, &aso);

	// Initialize
	if(!ss.initialize(aso, new MainMenu, aso.Style))
	{
		throw se::Error::StartUp::Initialization();
	}

	// Run gameloop
	ss.gameLoop();
}
catch(const char* e)
{
	se::MsgBox::show("Error", e, se::MsgBox::Icon::Error);
	se::Engine::get().shutDown(1);
}


void handleCommandInput(int argcount, char** args, AppStartupOptions* aso)
{
	for(int i = 0; i < argcount; i++)
	{
		if(std::strcmp(args[i], "-debug") == 0)
		{
			// Enable Debug Mode
			aso->DebugMode = true;
		}
		else if(std::strcmp(args[i], "-vsync") == 0)
		{
			// Enable Vsync
			aso->Vsync = true;
		}
		else if(std::strcmp(args[i], "-fullscreen") == 0)
		{
			// Enable Fullscreen
			aso->Style = sf::Style::Fullscreen;
		}
	}
}