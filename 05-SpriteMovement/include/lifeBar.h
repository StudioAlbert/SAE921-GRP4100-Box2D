#pragma once

#include "SFML/Graphics.hpp"

class LifeBar : public sf::Drawable
{
public:
	LifeBar(float lifeMax);

	void update();

	// DRAWABLE OVERRIDES
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	// Setters
	void setLife(float life_);

private:
	sf::RectangleShape m_lifeBar;
	float m_lifeMax;
	float m_life;
};
