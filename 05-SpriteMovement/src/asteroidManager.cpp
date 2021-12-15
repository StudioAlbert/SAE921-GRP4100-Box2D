#include "asteroidManager.h"

#include "SFML/Graphics/Drawable.hpp"

AsteroidManager::AsteroidManager(b2World& world_) : m_world(world_)
{
	
}

void AsteroidManager::draw (sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto& m : asteroids) {
		target.draw(m, states);
	}
}

void AsteroidManager::update()
{
	auto a = std::remove_if(
		asteroids.begin(),
		asteroids.end(),
		[](Asteroid& a) {return a.getIsDead(); });

	asteroids.erase(a, asteroids.end());
	
	for (auto& aa : asteroids) {
		aa.update();
	}
}

void AsteroidManager::AddAsteroid(sf::Vector2f startPos, float angle)
{

	asteroids.emplace_back(
		Asteroid(
			m_world, 
			startPos,
			angle)
	);
}

void AsteroidManager::putAsteroidToDeath(int idAsteroid_)
{
	// Check id, then put isDead to true
	auto a = std::find_if(
		asteroids.begin(),
		asteroids.end(),
		[idAsteroid_](Asteroid& a) {return a.getLocalId() == idAsteroid_; }
	);

	if (a != asteroids.end())
	{
		a->setIsDead();
	}


}



