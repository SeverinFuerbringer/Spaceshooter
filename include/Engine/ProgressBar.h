#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include "HUD.h"

namespace se
{

class SEVENGINEDLL_API ProgressBar : public HUD
{
public:
	ProgressBar();
	ProgressBar(se::vec2u size);
	ProgressBar(se::vec2u size, se::vec2i pos);
	ProgressBar(se::vec2u size, se::vec2i pos, sf::Text text);
	ProgressBar(se::vec2u size, se::vec2i pos, sf::Text text, sf::Font font);

	sf::RectangleShape& getProgressBar();

	void setBarTexture(sf::Texture* texture);
	void setBackgroundTexture(sf::Texture* texture);
	
	void setProgress(float percent);

private:
	sf::RectangleShape m_progress_bar;
	sf::Texture m_progress_bar_texture;

	void initialize();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
} // Namespace SevEngine

#endif // !PROGRESSBAR_H