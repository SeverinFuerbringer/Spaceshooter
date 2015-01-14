//////////////////////////////////////////////////
//	Copyright © Severin Fürbringer 2014
//
//	Author: Severin Fürbringer
//	Jahr:	2014
//	Datei:	SplashScreen.h
//////////////////////////////////////////////////

#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include "Engine/Scene.h"

class SplashScreen : public se::Scene
{
public:
	SplashScreen();
	~SplashScreen();

	void loadContent();
	void unloadContent();
	void update(sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);

private:
	void initialize();

private:
	sf::Font m_font;
	sf::Text m_text;
	sf::Texture	m_splash_texture;
	sf::RectangleShape m_splash;
	se::Transition* trns;
};

#endif // SPLASHSCREEN_H
