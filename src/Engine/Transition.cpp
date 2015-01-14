#include "Transition.h"

namespace se
{

Transition::Transition(Type animType, sf::Color color, sf::Uint8 startAlpha, sf::Uint8 endAlpha, sf::Time length, sf::RenderWindow* win)
		: m_animType(animType), m_color(color), m_startAlpha(startAlpha), m_endAlpha(endAlpha), m_trn_length(length), m_win(win), m_alpha(0), done(false), m_trn_timer(sf::milliseconds(200))
{
	m_trn_overlay.setSize(sf::Vector2f(static_cast<float>(win->getSize().x), static_cast<float>(win->getSize().y)));
	m_trn_overlay.setFillColor(color);
	m_trn_overlay.setPosition(sf::Vector2f(0, 0));
}


void Transition::animate()
{
	if(m_trn_timer >= m_trn_length)
	{
		done = true;
		m_trn_overlay.setFillColor(sf::Color(m_color.r, m_color.g, m_color.b, m_endAlpha));
	}
	else
	{
		m_trn_timer = m_clock.getElapsedTime();

		// Fade Animation Formula
		// start color + ((end color - start color)  * (elapsed time / total time))
		
		m_alpha = static_cast<sf::Uint8>((m_endAlpha - m_startAlpha) *
			(m_trn_timer.asSeconds() / m_trn_length.asSeconds()));

		m_trn_overlay.setFillColor(sf::Color(m_color.r, m_color.g, m_color.b, m_alpha));
		m_win->draw(m_trn_overlay);
	}
}
}