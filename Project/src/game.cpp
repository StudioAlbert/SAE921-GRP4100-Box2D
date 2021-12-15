#include <random>

#include "game.h"

Game::Game()
{
}

void Game::init() {

	m_window.create(sf::VideoMode(1280, 720), "Asteroid Spaceship");
	m_window.setVerticalSyncEnabled(true);
	m_window.setFramerateLimit(60.0f);

	for (size_t i = 0; i < 25; i++)
	{
		addRandomShape();
	}

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
				// -----------------------------------------------------------
				for (auto& s : m_shapes) {
					s.checkTouch(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
				}

			}
		}

		update();
		draw();
	}
}

void Game::update()
{
	int nbShapesDestroyed = 0;

	auto shapeIt = std::remove_if(
		m_shapes.begin(),
		m_shapes.end(),
		[&nbShapesDestroyed](auto& s)
		{
			if(s.getIsTouched())
			{
				nbShapesDestroyed++;
			}
			return s.getIsTouched();
		}
	);

	m_shapes.erase(shapeIt, m_shapes.end());

	// -----------------------------------------------------------
	for (auto& s : m_shapes) {
		s.update();
	}

	for (int addAShape = 0; addAShape < nbShapesDestroyed; addAShape++)
	{
		addRandomShape();
	}
}

void Game::draw()
{
	// Clear all background
	m_window.clear();

	// DRAW THINGS ----------------------------------------------------------
	for (auto& s : m_shapes) {
		m_window.draw(s);
	}

	// Display all elements
	m_window.display();
}

void Game::checkTouch(sf::Vector2f mousePosition) {

	for (auto& s : m_shapes) {
		s.checkTouch(mousePosition);
	}

}

void Game::addRandomShape()
{
	Shape newShape(m_window);
	m_shapes.push_back(newShape);

}
