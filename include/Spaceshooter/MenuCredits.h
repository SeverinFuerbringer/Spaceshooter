//////////////////////////////////////////////////
//	Copyright © Severin Fürbringer 2014
//
//	Author: Severin Fürbringer
//	Jahr:	2014
//	Datei:	MenuCredits.h
//////////////////////////////////////////////////

#ifndef MENUCREDITS_H
#define MENUCREDITS_H

#include "Engine/Scene.h"
#include "Engine/MenuButton.h"

class MenuCredits : public se::Scene
{
public:
	MenuCredits();
	~MenuCredits();

	void loadContent();
	void unloadContent();
	void update(sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);

private:
	void initialize();

private:
	sf::Font m_font;
	sf::Font m_back_button_font;
	sf::Text m_credits_text;

	sf::Texture m_background_texture;
	sf::RectangleShape m_background;
	sf::RectangleShape m_text_background;

	se::MenuButton m_back;

	se::Transition* trns;
};

#endif // MENUCREDITS
