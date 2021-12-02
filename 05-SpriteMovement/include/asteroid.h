#pragma once

#include <box2d/b2_body.h>

#include "userData.h"
#include "SFML/Graphics.hpp"

class Game;

class Asteroid : public sf::Drawable, public sf::Transformable
{
public:
	Asteroid(Game& game_, const sf::Vector2f startPos, const float angle);
	~Asteroid();

	// DRAWABLE OVERRIDES
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void update();

private:
	Game& m_game;

	sf::Sprite	m_sprite;
	bool isTextureLoaded;

	b2Body* m_body = nullptr;
	UserData* m_userData = new UserData(UserDataType::ASTEROID);

};
