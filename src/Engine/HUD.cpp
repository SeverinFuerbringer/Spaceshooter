#include "HUD.h"

namespace se
{

HUD::HUD()
	: m_font(se::Engine::get().getGlobalFont())
{
	setTextPosition(se::vec2i(0, 0));
}


HUD::HUD(se::vec2u size)
	: m_font(se::Engine::get().getGlobalFont())
{
	m_box.setSize(static_cast<se::vec2f>(size));
	setTextPosition(se::vec2i(0, 0));
}


HUD::HUD(se::vec2u size, se::vec2i pos)
	: m_font(se::Engine::get().getGlobalFont())
{
	m_box.setSize(static_cast<se::vec2f>(size));
	m_box.setPosition(static_cast<se::vec2f>(pos));
	setTextPosition(se::vec2i(0, 0));
}


HUD::HUD(se::vec2u size, se::vec2i pos, sf::Text text)
	: m_font(se::Engine::get().getGlobalFont()), m_text(text)
{
	m_text.setFont(m_font);
	m_box.setSize(static_cast<se::vec2f>(size));
	m_box.setPosition(static_cast<se::vec2f>(pos));
	setTextPosition(se::vec2i(0, 0));
}


HUD::HUD(se::vec2u size, se::vec2i pos, sf::Text text, sf::Font font)
	: m_font(font), m_text(text)
{
	m_box.setSize(static_cast<se::vec2f>(size));
	m_box.setPosition(static_cast<se::vec2f>(pos));
	setTextPosition(se::vec2i(0, 0));
}


void HUD::setTextPosition(se::vec2i offset)
{
	se::vec2f pos(m_box.getPosition().x + offset.x, m_box.getPosition().y + offset.y);
	m_text.setPosition(pos);
}


void HUD::setText(sf::Text text)
{
	m_text = text;
}


void HUD::setTextString(const std::string& str)
{
	m_text.setString(str);
}


sf::Text& HUD::getText()
{
	return m_text;
}


sf::RectangleShape& HUD::getBox()
{
	return m_box;
}


void HUD::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_box, states);
	target.draw(m_text, states);
}
} // Namespace SevEngine