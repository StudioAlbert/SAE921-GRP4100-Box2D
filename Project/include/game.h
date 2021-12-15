#pragma once

#include <vector>

#include "SFML/Graphics/RenderWindow.hpp"

#include "shape.h"

class Game {

public:
	Game();
	void init();
	void loop();

private:

	sf::RenderWindow m_window;
	std::vector<Shape> m_shapes;

	void update();
	void draw();
	void checkTouch(sf::Vector2f mousePosition);
	void addRandomShape();

};
