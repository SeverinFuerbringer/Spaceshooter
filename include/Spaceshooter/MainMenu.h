//////////////////////////////////////////////////
//	Copyright © Severin Fürbringer 2014
//
//	Author: Severin Fürbringer
//	Jahr:	2014
//	Datei:	MainMenu.h
//////////////////////////////////////////////////

#ifndef MAINMENU_H
#define MAINMENU_H

#include "Engine/Scene.h"
#include "Engine/MenuWidget.h"
#include <SFML/Audio.hpp>

class MainMenu : public se::Scene
{
public:
	MainMenu();
	~MainMenu();

	void loadContent();
	void unloadContent();
	void update(sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);

private:
	void initialize();
	void initButtons();

private:
	bool m_play_intro;
	sf::Event m_event;
	
	sf::Font m_font;
	sf::Font m_title_font;
	sf::Text m_title_text;

	sf::RectangleShape m_menu_poster;
	sf::Texture m_menu_poster_texture;

	// Menu buttons
	se::MenuWidget m_menu;
	se::MenuButton m_menu_btn_arr[4];

	se::Transition *trns;
};

#endif // MAINMENU_H
