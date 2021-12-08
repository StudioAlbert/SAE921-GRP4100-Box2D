#include "asteroid.h"

long Asteroid::m_localIdAsteroid = 0;

Asteroid::Asteroid(b2World& world_, const sf::Vector2f startPos, const float angle){

    std::random_device rd; // obtain a random number from hardware
    std::mt19937 generator(rd()); // seed the generator
    std::uniform_real_distribution<> rndVelocityX(-1.0f, 1.0f); // define the range
    std::uniform_real_distribution<> rndVelocityY(-1.0f, 1.0f); // define the range

    TextureManager* texManager = TextureManager::Instance();
    m_sprite.setTexture(texManager->getAsteroidTexture());

    m_sprite.setOrigin(0.5f * texManager->getAsteroidTexture().getSize().x, 0.5f * texManager->getAsteroidTexture().getSize().y);

    // Defing the box 2D elements
    b2BodyDef bodyDef;
    bodyDef.fixedRotation = false;
    bodyDef.type = b2_dynamicBody;
    bodyDef.angularDamping = 0.01f;
    bodyDef.linearDamping = 0.01f;
    // Set Datas
    m_userData->setLocalId(getGlobalId());
	bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(m_userData);

    m_body = world_.CreateBody(&bodyDef);
    
    // Shape of the physical (A box)
    b2CircleShape hitBox;
    hitBox.m_radius = pixelsToMeters(texManager->getAsteroidTexture().getSize().x * 0.5f);

    // The fixture is what it defines the physic react
    b2FixtureDef playerFixtureDef;
    playerFixtureDef.shape = &hitBox;
    playerFixtureDef.density = 1.0f;
    playerFixtureDef.friction = 0.0f;
    playerFixtureDef.restitution = 0.6f; // Make it bounce a little bit

    m_body->CreateFixture(&playerFixtureDef);

    // Set angle and velocity
    b2Vec2 physicalStartPos = pixelsToMeters(sf::Vector2f(startPos.x, startPos.y));
    m_body->SetTransform(physicalStartPos, angle);

    b2Vec2 initialVelocity = b2Vec2(rndVelocityX(generator), rndVelocityY(generator));
    m_body->SetLinearVelocity(initialVelocity);

    update();

}

void Asteroid::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
	target.draw(m_sprite, states);
}

void Asteroid::update()
{

    // Get the position of the body
    b2Vec2 bodyPos = m_body->GetPosition();

    // Translate meters to pixels
    sf::Vector2f graphicPosition = metersToPixels(bodyPos);

    // Set the position of the Graphic object
    setPosition(graphicPosition);

    float angle = m_body->GetAngle();
    setRotation(radToDeg(angle));

}

void Asteroid::setIsDead()
{
    m_isDead = true;
}
bool Asteroid::getIsDead()
{
    return m_isDead;
}

long Asteroid::getLocalId()
{
    return m_userData->getLocalId();
}
long Asteroid::getGlobalId()
{
    return m_localIdAsteroid++;
}