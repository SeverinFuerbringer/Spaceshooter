//////////////////////////////////////////////////
//	Copyright © Severin Fürbringer 2014
//
//	Author: Severin Fürbringer
//	Jahr:	2014
//	Datei:	MenuOptions.h
//////////////////////////////////////////////////

#ifndef	MENUOPTIONS_H
#define MENUOPTIONS_H

#include "Engine/Scene.h"
#include "Engine/MenuWidget.h"
#include "Engine/Engine.h"

class MenuOptions : public se::Scene
{
public:
	MenuOptions();
	~MenuOptions();
	
	void loadContent();
	void unloadContent();
	void update(sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);

private:
	void initialize();

	sf::Font m_back_button_font;
	sf::Font m_font;

	sf::Texture m_background_texture;
	sf::RectangleShape m_background;

	se::MenuButton m_back;

	se::Transition* trns;
};

#endif // MENUOPTIONS_H

