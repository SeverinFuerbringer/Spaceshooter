#include "MenuButton.h"

namespace se
{

MenuButton::MenuButton()
{
}


MenuButton::MenuButton(se::vec2u pos, se::vec2u size)
	: MenuElement(pos, size)
{

}


MenuButton::~MenuButton()
{
}

}

//void MenuButton::setHoverOutlineThickness(float p)
//{
//	m_drawable_rectangle.setOutlineThickness(p);
//}
//
//
//void MenuButton::setHoverOutlineColor(sf::Color c)
//{
//	m_drawable_rectangle.setOutlineColor(c);
//}
//
//
//float MenuButton::getHoverOutlineThickness()
//{
//	return m_drawable_rectangle.getOutlineThickness();
//}
//
//
//sf::Color MenuButton::getHoverOutlineColor()
//{
//	return m_drawable_rectangle.getOutlineColor();
//}