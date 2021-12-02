#include "asteroidManager.h"

void AsteroidManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto& m : asteroids) {
		target.draw(m, states);
	}
}

void AsteroidManager::update()
{
	for (auto& m : asteroids) {
		m.update();
	}
}

void AsteroidManager::AddAsteroid(Game& game_, sf::Vector2f startPos, float angle)
{

	asteroids.emplace_back(
		Asteroid(
			game_, 
			startPos,
			angle)
	);
}


