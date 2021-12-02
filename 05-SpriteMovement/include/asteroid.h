#pragma once

#include <box2d/b2_body.h>
#include "SFML/Graphics.hpp"

class Game;

class Asteroid : public sf::Drawable, public sf::Transformable
{
public:
	Asteroid(Game& game_, const std::string texturePath, const sf::Vector2f startPos, const float angle);
	~Asteroid();

	// DRAWABLE OVERRIDES
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void update();

private:
	Game& m_game;

	sf::Vector2f m_direction;
	sf::Sprite	m_sprite;

	sf::Texture m_texture;

	b2Body* body = nullptr;

	// Rng Velocity
	//std::random_device rd; // obtain a random number from hardware
	//std::mt19937 generator(rd()); // seed the generator
	//std::uniform_real_distribution<> rndVelocityX(0.0f, 1.0f); // define the range
};
