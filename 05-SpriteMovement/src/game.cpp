#include <random>

#include "game.h"

#include <iostream>

#include "textureManager.h"

Game::Game() : 
	m_gravity(0.0f, 0.0f),
	m_world(m_gravity),
	m_ship(*this),
	m_contacts(*this)
{
}

void Game::init() {

	TextureManager* texture_manager = TextureManager::Instance();

	m_window.create(sf::VideoMode(1280, 720), "Asteroid Spaceship");
	m_window.setVerticalSyncEnabled(true);
	m_window.setFramerateLimit(60.0f);

	m_ship.init(m_window.getSize());
	m_ship.move(sf::Vector2f(0.5f * m_window.getSize().x, 0.5f * m_window.getSize().y), sf::Vector2f(0, 0));

	m_gameOverTitle.setTexture(texture_manager->getGameOverTexture());
	m_gameOverTitle.setOrigin(0.5f * texture_manager->getGameOverTexture().getSize().x, 0.5f * texture_manager->getGameOverTexture().getSize().y);
	m_gameOverTitle.setPosition(0.5f * m_window.getSize().x, 0.5f * m_window.getSize().y);

	// Add a bouncer
// TOP LIMIT -------------------------------------------
	m_windowLimits.push_back(
		Bouncer(
			*this,
			sf::Vector2f(0.5f * m_window.getSize().x, 0.0f),
			sf::Vector2f(m_window.getSize().x, 10.0f)
		)
	);
	// BOTTOM LIMIT -------------------------------------------
	m_windowLimits.push_back(
		Bouncer(
			*this,
			sf::Vector2f(0.5f * m_window.getSize().x, m_window.getSize().y),
			sf::Vector2f(m_window.getSize().x, 10.0f)
		)
	);
	// LEFT LIMIT -------------------------------------------
	m_windowLimits.push_back(
		Bouncer(
			*this,
			sf::Vector2f(0.0f, 0.5f * m_window.getSize().y),
			sf::Vector2f(10.0F, m_window.getSize().y)
		)
	);
	// RIGHT LIMIT -------------------------------------------
	m_windowLimits.push_back(
		Bouncer(
			*this,
			sf::Vector2f(m_window.getSize().x, 0.5f * m_window.getSize().y),
			sf::Vector2f(10.0f, m_window.getSize().y)
		)
	);

	m_debugMode = false;

	// Register contacts
	m_world.SetContactListener(&m_contacts);

}

void Game::loop()
{
	while (m_window.isOpen())
	{
#pragma region Event processes
		sf::Event event;

		while (m_window.pollEvent(event))
		{
			// Windows events -------------------------------------------------------------------------------
			if (event.type == sf::Event::Closed)
			{
				m_window.close();
				return;
			}
			if (event.type == sf::Event::Resized)
			{
				auto view = m_window.getView();
				view.setSize(event.size.width, event.size.height);
				m_window.setView(view);
			}

			// Mouse events ---------------------------------------------------------------------------------
			if (event.type == sf::Event::MouseButtonReleased)
			{
				if(event.KeyReleased == sf::Keyboard::Key::D)
				{
					m_debugMode = !m_debugMode;
				}
			}
		}


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
			m_ship.speedUp(1.0f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
			m_ship.speedDown(1.0f);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
			m_ship.rotateLeft(1.0f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
			m_ship.rotateRight(1.0f);
		}


#pragma endregion


#pragma region Physical process
		if(!m_gameOver)
			update();

#pragma endregion
		draw();

#pragma region Graphics process

#pragma endregion

	}
}

void Game::update()
{
	// Updating the world with a delay
	float timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
	m_world.Step(timeStep, velocityIterations, positionIterations);

	// Update the ship
	m_ship.update();
	// Update Life bars with the lif of the ship
	m_lifeBar.setLife(m_ship.getLife());
	m_lifeBar.update();
	if (m_ship.getLife() <= 0)
	{
		// LOOOOSSSEEEEERRRRRRRRRR !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		m_gameOver = true;
		return;
	}

	// Udpate asteroids
	m_asteroidManager.update();
	// Update limits
	for (auto& b : m_windowLimits) {
		b.update();
	}

	// Tick every 1.0sec
	sf::Time elapsed = clock.restart();
	collectedElapsed += elapsed;

	if (collectedElapsed.asSeconds() > 1.0f) {

		std::random_device rd; // obtain a random number from hardware
		std::mt19937 generator(rd()); // seed the generator
		std::uniform_int_distribution<> rndAngle(0, 360); // define the range
		std::uniform_int_distribution<> rndX(0, m_window.getSize().x); // define the range
		std::uniform_int_distribution<> rndY(0, m_window.getSize().y); // define the range

		sf::Vector2f rdnPos(rndX(generator), rndY(generator));

		// Pop an asteroid
		m_asteroidManager.AddAsteroid(*this, rdnPos, rndAngle(generator));

		collectedElapsed = sf::Time::Zero;

	}
}

void Game::draw()
{
	// Clear all background
	m_window.clear();

	// DRWA THINGS ----------------------------------------------------------
	// Draw the ship
	if(!m_gameOver)
		m_window.draw(m_ship);

	// Draw asteroids
	m_window.draw(m_asteroidManager);
	// Draw limits
	if (m_debugMode)
	{
		for (auto& b : m_windowLimits) {
			m_window.draw(b);
		}
	}
	// Draw Life bar
	m_window.draw(m_lifeBar);

	if(m_gameOver)
		m_window.draw(m_gameOverTitle);

	// Display all elements
	m_window.display();
}