//////////////////////////////////////////////////
//	Copyright © Severin Fürbringer 2014
//
//	Author: Severin Fürbringer
//	Jahr:	2014
//	Datei:	MenuElement.cpp
//////////////////////////////////////////////////

#include "MenuElement.h"

namespace se
{

MenuElement::~MenuElement()
{
}


MenuElement::MenuElement(se::vec2u pos, se::vec2u size)
	: m_position(pos), m_size(size)
{
}


MenuElement::MenuElement()
{
}


void MenuElement::setElementColor(sf::Color col)
{
	m_drawable_rectangle.setFillColor(col);
}


void MenuElement::setFontColor(sf::Color col)
{
	m_drawable_text.setColor(col);
}


void MenuElement::setString(std::string s)
{
	m_drawable_text.setString(s);
}


void MenuElement::setFontSize(se::uint fs)
{
	m_drawable_text.setCharacterSize(fs);
}


void MenuElement::setFont(sf::Font& f)
{
	m_font = f;
	m_drawable_text.setFont(f);
}


void MenuElement::setPosition(se::vec2u pos)
{
	m_drawable_rectangle.setPosition(se::vec2f(static_cast<float>(pos.x), static_cast<float>(pos.y)));
	m_drawable_text.setPosition(
		(m_drawable_rectangle.getPosition().x + (m_drawable_rectangle.getSize().x / 5.0f)),
		(m_drawable_rectangle.getPosition().y + (m_drawable_rectangle.getSize().y / 4.5f)));
}


void MenuElement::setSize(se::vec2u s)
{
	m_drawable_rectangle.setSize(se::vec2f(static_cast<float>(s.x), static_cast<float>(s.y)));
}


void MenuElement::setTexture(sf::Texture& t)
{
	hasTexture = true;
	m_texture = t;
	m_drawable_rectangle.setTexture(&m_texture);
}


void MenuElement::draw(sf::RenderWindow& window)
{
	window.draw(m_drawable_rectangle);
	window.draw(m_drawable_text);
}

// -------------------------------------------------------

sf::Color MenuElement::getElementColor()
{
	return m_drawable_rectangle.getFillColor();
}


sf::Color MenuElement::getFontColor()
{
	return m_drawable_text.getColor();
}


std::string MenuElement::getString()
{
	return m_string;
}


se::uint MenuElement::getFontSize()
{
	return m_drawable_text.getCharacterSize();
}


sf::Font MenuElement::getFont()
{
	return m_font;
}


se::vec2u MenuElement::getPosition()
{
	return m_position;
}


se::vec2u MenuElement::getSize()
{
	se::vec2u temp((se::vec2u)m_drawable_rectangle.getSize());
	return temp;
}


const sf::Texture* MenuElement::getTexture()
{
	return m_drawable_rectangle.getTexture();
}


sf::RectangleShape& MenuElement::getDrawable()
{
	return m_drawable_rectangle;
}


sf::Text& MenuElement::getDrawableText()
{
	return m_drawable_text;
}
}