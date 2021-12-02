#include "game.h"
#include <random>

Game::Game() : 
	m_gravity(0.0f, 0.0f),
	m_world(m_gravity),
	m_ship(*this)
{
}

void Game::init() {

	m_window.create(sf::VideoMode(1280, 720), "SAE Platformer");
	m_window.setVerticalSyncEnabled(true);
	m_window.setFramerateLimit(60.0f);

	m_ship.init(m_window.getSize());
	m_ship.move(sf::Vector2f(0.5f * m_window.getSize().x, 0.5f * m_window.getSize().y), sf::Vector2f(0, 0));

	// Add a bouncer
// TOP LIMIT -------------------------------------------
	windowLimits.push_back(
		Bouncer(
			*this,
			sf::Vector2f(0.5f * m_window.getSize().x, 0.0f),
			sf::Vector2f(m_window.getSize().x, 10.0f)
		)
	);
	// BOTTOM LIMIT -------------------------------------------
	windowLimits.push_back(
		Bouncer(
			*this,
			sf::Vector2f(0.5f * m_window.getSize().x, m_window.getSize().y),
			sf::Vector2f(m_window.getSize().x, 10.0f)
		)
	);
	// LEFT LIMIT -------------------------------------------
	windowLimits.push_back(
		Bouncer(
			*this,
			sf::Vector2f(0.0f, 0.5f * m_window.getSize().y),
			sf::Vector2f(10.0F, m_window.getSize().y)
		)
	);
	// RIGHT LIMIT -------------------------------------------
	windowLimits.push_back(
		Bouncer(
			*this,
			sf::Vector2f(m_window.getSize().x, 0.5f * m_window.getSize().y),
			sf::Vector2f(10.0f, m_window.getSize().y)
		)
	);

}

void Game::loop()
{

	sf::Clock clock;
	sf::Time collectedElapsed;

	std::random_device rd; // obtain a random number from hardware
	std::mt19937 generator(rd()); // seed the generator
	std::uniform_int_distribution<> rndAngle(0, 360); // define the range
	std::uniform_int_distribution<> rndX(0, m_window.getSize().x); // define the range
	std::uniform_int_distribution<> rndY(0, m_window.getSize().y); // define the range

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
		// Updating the world with a delay
		float timeStep = 1.0f / 60.0f;
		int32 velocityIterations = 6;
		int32 positionIterations = 2;
		m_world.Step(timeStep, velocityIterations, positionIterations);

		m_ship.update();
		m_asteroidManager.update();
		for (auto& b : windowLimits) {
			b.update();
		}

		// Tick every 1.0sec
		sf::Time elapsed = clock.restart();
		collectedElapsed += elapsed;

		if (collectedElapsed.asSeconds() > 10.0f) {

			sf::Vector2f rdnPos(rndX(generator), rndY(generator));

			// Pop an asteroid
			m_asteroidManager.AddAsteroid(*this, rdnPos, rndAngle(generator));

			collectedElapsed = sf::Time::Zero;

		}

#pragma endregion


#pragma region Graphics process
		// Clear all background
		m_window.clear();

		m_window.draw(m_ship);
		m_window.draw(m_asteroidManager);
		for (auto& b : windowLimits) {
			m_window.draw(b);
		}
		// Display all elements
		m_window.display();
#pragma endregion

	}
}
