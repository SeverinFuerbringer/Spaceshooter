#include "ProgressBar.h"

namespace se
{

ProgressBar::ProgressBar()
	: HUD()
{
	initialize();
}


ProgressBar::ProgressBar(se::vec2u size)
	: HUD(size)
{
	initialize();
}


ProgressBar::ProgressBar(se::vec2u size, se::vec2i pos)
	: HUD(size, pos)
{
	initialize();
}


ProgressBar::ProgressBar(se::vec2u size, se::vec2i pos, sf::Text text)
	: HUD(size, pos, text)
{
	initialize();
}


ProgressBar::ProgressBar(se::vec2u size, se::vec2i pos, sf::Text text, sf::Font font)
	: HUD(size, pos, text, font)
{
	initialize();
}


sf::RectangleShape& ProgressBar::getProgressBar()
{
	return m_progress_bar;
}


void ProgressBar::initialize()
{
	m_progress_bar.setPosition(se::vec2f(m_box.getPosition().x, m_box.getPosition().y));
	m_progress_bar.setSize(se::vec2f(m_box.getSize().x, m_box.getSize().y));
	setProgress(100.0f);
}


void ProgressBar::setBarTexture(sf::Texture* texture)
{
	m_progress_bar_texture = *texture;
}


void ProgressBar::setBackgroundTexture(sf::Texture* texture)
{
	m_box.setTexture(texture);
}


void ProgressBar::setProgress(float percent)
{
	// 100%
	se::uint width = static_cast<se::uint>(m_box.getSize().x);
	
	// New ProgressBar width
	se::vec2f new_prg_bar(((width / 100) * percent), m_progress_bar.getSize().y);
	m_progress_bar.setSize(new_prg_bar);
}


void ProgressBar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_box, states);
	target.draw(m_progress_bar, states);
	target.draw(m_text, states);
}
} // Namespace SevEngine