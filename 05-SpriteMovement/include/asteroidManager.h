#pragma once

#include "asteroid.h"

class AsteroidManager : public sf::Drawable {

private:
	std::vector<Asteroid> asteroids;

public:
	// DRAWABLE OVERRIDES
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void update();

	void AddAsteroid(Game& game_, sf::Vector2f startPos, float angle);

};