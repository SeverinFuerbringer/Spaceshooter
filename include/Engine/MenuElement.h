//////////////////////////////////////////////////
//	Copyright © Severin Fürbringer 2014
//
//	Author: Severin Fürbringer
//	Jahr:	2014
//	Datei:	MenuElement.h
//////////////////////////////////////////////////

#ifndef MENUELEMENT_H
#define MENUELEMENT_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "EngineExport.h"
#include "Engine.h"

namespace se
{
class SEVENGINEDLL_API MenuElement
{
public:
	virtual ~MenuElement();
	MenuElement();
	MenuElement(se::vec2u pos, se::vec2u size);

	// Setters:
	virtual void setElementColor(sf::Color col);
	virtual void setFontColor(sf::Color col);
	virtual void setString(std::string s);
	virtual void setFontSize(se::uint fs);
	virtual void setFont(sf::Font& f);
	virtual void setPosition(se::vec2u pos);
	virtual void setSize(se::vec2u s);
	virtual void setTexture(sf::Texture& t);

	// Getters
	virtual sf::Color getElementColor();
	virtual sf::Color getFontColor();
	virtual std::string getString();
	virtual se::uint getFontSize();
	virtual sf::Font getFont();
	virtual se::vec2u getPosition();
	virtual se::vec2u getSize();
	virtual const sf::Texture* getTexture();

	virtual sf::RectangleShape& getDrawable();
	virtual sf::Text& getDrawableText();

	virtual void draw(sf::RenderWindow& window);

	bool hasTexture;
public:
	sf::Color m_color;
	sf::Texture m_texture;
	se::vec2u m_position;
	se::vec2u m_size;		
	
	std::string m_string;
	sf::Font m_font;
	se::uint m_font_size;
	sf::Color m_font_color;

	sf::Text m_drawable_text;
	sf::RectangleShape m_drawable_rectangle;
	
};
} // namespace SevEngine

#endif // MENUELEMENT_H
