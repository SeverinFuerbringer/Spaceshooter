#ifndef TRANSITION_H
#define TRANSITION_H

#include <SFML/Graphics.hpp>
#include "EngineTypes.hpp"
#include "EngineExport.h"

namespace se
{
class SEVENGINEDLL_API Transition
{
public:
	enum Type
	{
		Fade
	};
	
	Transition(Type animType, sf::Color color, sf::Uint8 startAlpha, sf::Uint8 endAlpha, sf::Time length, sf::RenderWindow* win);

	void animate();
	bool done;
private:
	Type m_animType;
	sf::RenderWindow* m_win;
	sf::Time m_trn_length;
	sf::Time m_trn_timer;
	sf::Clock m_clock;
	sf::Color m_color;
	sf::Uint8 m_startAlpha;
	sf::Uint8 m_endAlpha;
	sf::Uint8 m_alpha;
	sf::RectangleShape m_trn_overlay;
};
} // namespace SevEngine

#endif // TRANSITION_H