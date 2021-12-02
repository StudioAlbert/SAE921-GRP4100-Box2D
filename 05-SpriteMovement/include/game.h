#pragma once
#include <vector>

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Window//Event.hpp"
#include "box2d/b2_world.h"

#include "SFML_Utilities.h"

#include "asteroidManager.h"
#include "bouncer.h"
#include "ship.h"

#include "textureManager.h"
#include <lifeBar.h>

class Game {
public:
	Game();
	void init();
	void loop();

	b2World& getWorld() { return m_world; };

private:

	bool m_debugMode;

	// The window ---------------------------------------------
	sf::RenderWindow m_window;

	// The physical world -------------------------------------
	b2Vec2 m_gravity;
	b2World m_world;
	std::vector<Bouncer> m_windowLimits;

	// The game entities --------------------------------------
	Ship m_ship;
	AsteroidManager m_asteroidManager;

	// The ui entities
	LifeBar m_lifeBar = LifeBar(100.0f);

	sf::Vector2f m_mousePressedPos_sensor, m_mouseReleasedPos_sensor;
	sf::Vector2f m_mousePressedPos_ball, m_mouseReleasedPos_ball;

};
