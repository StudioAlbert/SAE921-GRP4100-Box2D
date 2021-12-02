#include <box2d/b2_body.h>

#include "asteroid.h"
#include "game.h"

#include "SFML_Utilities.h"
#include <random>

Asteroid::Asteroid(Game& game_, const sf::Vector2f startPos, const float angle) : m_game(game_) {

    std::random_device rd; // obtain a random number from hardware
    std::mt19937 generator(rd()); // seed the generator
    std::uniform_real_distribution<> rndVelocityX(0.0f, 1.0f); // define the range
    std::uniform_real_distribution<> rndVelocityY(0.0f, 1.0f); // define the range

    TextureManager* texManager = TextureManager::Instance();
    m_sprite.setTexture(texManager->getAsteroidTexture());

    m_sprite.setOrigin(0.5f * texManager->getAsteroidTexture().getSize().x, 0.5f * texManager->getAsteroidTexture().getSize().y);

    // Defing the box 2D elements
    b2BodyDef bodyDef;
    bodyDef.fixedRotation = false;
    bodyDef.type = b2_dynamicBody;
    bodyDef.angularDamping = 0.01f;
    bodyDef.linearDamping = 0.01f;
    body = this->m_game.getWorld().CreateBody(&bodyDef);

    // Shape of the physical (A box)
    b2CircleShape hitBox;
    hitBox.m_radius = pixelsToMeters(texManager->getAsteroidTexture().getSize().x * 0.5f);

    // The fixture is what it defines the physic react
    b2FixtureDef playerFixtureDef;
    playerFixtureDef.shape = &hitBox;
    playerFixtureDef.density = 1.0f;
    playerFixtureDef.friction = 0.0f;
    playerFixtureDef.restitution = 0.6f; // Make it bounce a little bit
    //playerFixtureDef.userData.pointer = reinterpret_cast <std::uintptr_t>(&playerBoxData);
    body->CreateFixture(&playerFixtureDef);

    // Set angle and velocity
    b2Vec2 physicalStartPos = pixelsToMeters(sf::Vector2f(startPos.x, startPos.y));
    body->SetTransform(physicalStartPos, angle);

    b2Vec2 initialVelocity = b2Vec2(rndVelocityX(generator), rndVelocityY(generator));
    body->SetLinearVelocity(initialVelocity);

    update();

}

Asteroid::~Asteroid()
{
	//m_texture.~Texture();
}

void Asteroid::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
	target.draw(m_sprite, states);
}

void Asteroid::update()
{

    // Set speed -------------------------------------------------------------------
    //if (isTextureLoaded) {
        //m_sprite.setTexture(m_texture);
    //}
    //body->SetLinearVelocity(linVelocity);

    // Get the position of the body
    b2Vec2 bodyPos = body->GetPosition();

    // Translate meters to pixels
    sf::Vector2f graphicPosition = metersToPixels(bodyPos);

    // Set the position of the Graphic object
    setPosition(graphicPosition);

    float angle = body->GetAngle();
    setRotation(radToDeg(angle));

}
