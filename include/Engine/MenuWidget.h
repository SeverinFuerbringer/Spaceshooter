//////////////////////////////////////////////////
//	Copyright © Severin Fürbringer 2014
//
//	Author: Severin Fürbringer
//	Jahr:	2014
//	Datei:	MenuWidget.h
//////////////////////////////////////////////////

#ifndef MENUWIDGET_H
#define MENUWIDGET_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "MenuButton.h"
#include "EngineExport.h"

namespace se
{
class SEVENGINEDLL_API MenuWidget
{
public:
	MenuWidget();
	~MenuWidget();

	void draw(sf::RenderWindow& window);
	void add(MenuElement menu_element);
	void operator+=(MenuElement menu_element);

public:
	std::vector<MenuElement> elements;
};
}

#endif // MENUWIDGET_H
