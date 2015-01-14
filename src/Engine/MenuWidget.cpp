//////////////////////////////////////////////////
//	Copyright © Severin Fürbringer 2014
//
//	Author: Severin Fürbringer
//	Jahr:	2014
//	Datei:	MenuWidget.cpp
//////////////////////////////////////////////////

#include "MenuWidget.h"
#include "MsgBox.h"

namespace se
{

MenuWidget::MenuWidget()
{
}


MenuWidget::~MenuWidget()
{
}


void MenuWidget::draw(sf::RenderWindow& window)
{
	for (unsigned i = 0; i < elements.size(); i++)
	{
		elements[i].draw(window);
	}
}


void MenuWidget::add(MenuElement menu_element)
{
	elements.push_back(menu_element);
}


void MenuWidget::operator+=(MenuElement menu_element)
{
	elements.push_back(menu_element);
}
}