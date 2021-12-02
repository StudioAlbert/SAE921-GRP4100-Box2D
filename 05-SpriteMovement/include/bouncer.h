#pragma once

#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"

class Game;

class Bouncer : public sf::Drawable, public sf::Transformable
{
public:
	explicit Bouncer(Game& game_, sf::Vector2f pos, sf::Vector2f size);

	void init(sf::Vector2f, sf::Vector2f);
	void update();

	b2Body* getBody(){ return body; };

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	// Root game
	Game& game;

	// Graphic object
	sf::RectangleShape m_shape;

	// The box 2D object
	b2Body* body = nullptr;

};
