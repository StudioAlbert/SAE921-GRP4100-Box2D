#include "lifebar.h"

LifeBar::LifeBar(float lifeMax)
{

	// Life bar of the ship
	m_lifeBar.setSize(sf::Vector2f(400.0f, 5.0f));
	m_lifeBar.setPosition(sf::Vector2f(10, 25));
	m_lifeBar.setOrigin(0, m_lifeBar.getSize().y * 0.5f);
	m_lifeBar.setFillColor(sf::Color::Blue);

	m_lifeMax = lifeMax;

}

void LifeBar::update()
{
	// Life bar update
	m_lifeBar.setScale(1.0f, m_life / m_lifeMax);

}

void LifeBar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_lifeBar, states);
}

void LifeBar::setLife(float life_) {
	m_life = life_;
}
