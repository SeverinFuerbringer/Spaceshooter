#ifndef HUD_H
#define HUD_H

#include <SFML/Graphics.hpp>
#include "Engine.h"

namespace se
{

// HUD base class
class SEVENGINEDLL_API HUD : public sf::Drawable
{
public:
	HUD();
	HUD(se::vec2u size);
	HUD(se::vec2u size, se::vec2i pos);
	HUD(se::vec2u size, se::vec2i pos, sf::Text text);
	HUD(se::vec2u size, se::vec2i pos, sf::Text text, sf::Font font);

	// Sets the position offset relative to
	// the x & y coordinates of the rectangle
	void setTextPosition(se::vec2i offset);
	void setText(sf::Text text);
	void setTextString(const std::string& str);
	
	sf::Text& getText();
	sf::RectangleShape& getBox();

	//virtual ~HUD() {}

protected:
	sf::Text m_text;
	sf::RectangleShape m_box;
	sf::Font m_font;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
} // Namespace SevEngine


#endif // !HUD_H
