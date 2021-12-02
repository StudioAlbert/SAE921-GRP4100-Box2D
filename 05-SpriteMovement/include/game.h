#pragma once
#include <vector>

#include "SFML/Graphics/RenderWindow.hpp"
#include "box2d/b2_world.h"

#include "asteroidManager.h"
#include "bouncer.h"
#include "contact_listener.h"
#include "lifeBar.h"
#include "ship.h"


class Game {
public:
	Game();
	void init();
	void loop();

	b2World& getWorld() { return m_world; };
	Ship& getShip() { return m_ship; };

private:

	bool m_debugMode;
	bool m_gameOver = false;

	// The window ---------------------------------------------
	sf::RenderWindow m_window;

	// The physical world -------------------------------------
	b2Vec2 m_gravity;
	b2World m_world;
	std::vector<Bouncer> m_windowLimits;
	MyContactListener m_contacts;


	// The game entities --------------------------------------
	Ship m_ship;
	AsteroidManager m_asteroidManager;

	// The ui entities
	LifeBar m_lifeBar = LifeBar(100.0f);
	sf::Sprite m_gameOverTitle;

	sf::Clock clock;
	sf::Time collectedElapsed;

	void update();
	void draw();


};
