#pragma once

#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"

class Game;

class Ship : public sf::Drawable, public sf::Transformable {

public:

	explicit Ship(Game& game_);
	~Ship() {};

	void init(sf::Vector2u winsize);
	void update();

	void move(sf::Vector2f _pixelsPosition, sf::Vector2f _velocity);

	void speedUp(float force);
	void speedDown(float force);
	void ApplyLocalForceWithCheck(float force);

	void rotateLeft(float torque);
	void rotateRight(float torque);
	void ApplyTorqueWithCheck(float torque);

	// DRAWABLE OVERRIDES
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	Game& m_game;

	sf::Sprite m_sprite;

	b2Body* body = nullptr;

	float life = 100.0f;

};