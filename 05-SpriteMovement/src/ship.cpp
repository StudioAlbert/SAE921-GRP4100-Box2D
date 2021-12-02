
#include "game.h"
#include "ship.h"

#include "SFML_Utilities.h"
#include <iostream>

Ship::Ship(Game& game_) : m_game(game_)
{
}

void Ship::init(sf::Vector2u winsize) {

    // Defining the shape
    TextureManager* texManager = TextureManager::Instance();
    m_sprite.setTexture(texManager->getShipTexture());
    m_sprite.setOrigin(texManager->getShipTexture().getSize().x * 0.5f, texManager->getShipTexture().getSize().y * 0.5f);
    
    // Defing the box 2D elements
    b2BodyDef bodyDef;
    bodyDef.fixedRotation = false;
    bodyDef.type = b2_dynamicBody;
    b2Vec2 windowSize = pixelsToMeters(winsize);
    bodyDef.position.Set(windowSize.x / 2.0f, windowSize.y / 2.0f);
    bodyDef.angularDamping = 0.75f;
    bodyDef.linearDamping = 0.75f;
    body = this->m_game.getWorld().CreateBody(&bodyDef);

    // Shape of the physical (A box)
    b2PolygonShape hitBox;
    hitBox.SetAsBox(0.5f * pixelsToMeters(texManager->getShipTexture().getSize().x), 0.5f * pixelsToMeters(texManager->getShipTexture().getSize().y));

    // The fixture is what it defines the physic react
    b2FixtureDef playerFixtureDef;
    playerFixtureDef.shape = &hitBox;
    playerFixtureDef.density = 1.0f;
    playerFixtureDef.friction = 0.0f;
    playerFixtureDef.restitution = 0.6f; // Make it bounce a little bit
    //playerFixtureDef.userData.pointer = reinterpret_cast <std::uintptr_t>(&playerBoxData);
    body->CreateFixture(&playerFixtureDef);

}

void Ship::update() {

    // Set speed -------------------------------------------------------------------
    //body->SetLinearVelocity(linVelocity);

    // Get the position of the body
    b2Vec2 bodyPos = body->GetPosition();

    // Translate meters to pixels
    sf::Vector2f graphicPosition = metersToPixels(bodyPos);

    // Set the position of the Graphic object
    setPosition(graphicPosition);

    float angle = body->GetAngle();
    setRotation(radToDeg(angle));

    std::cout << "Angular velocity : " << body->GetAngularVelocity() << std::endl;

}

void Ship::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(m_sprite, states);
}

void Ship::move(sf::Vector2f _pixelsPosition, sf::Vector2f _velocity) {

    b2Vec2 pos = pixelsToMeters(_pixelsPosition);
    b2Vec2 vel = pixelsToMeters(_velocity);

    body->SetTransform(pos, 0.0f);

}

void Ship::speedUp(float forceValue) {
    ApplyLocalForceWithCheck(1.0f * forceValue);
}

void Ship::speedDown(float forceValue) {
    ApplyLocalForceWithCheck(-1.0f * forceValue);
}

void Ship::ApplyLocalForceWithCheck(float forceValue) {

    b2Vec2 force(0.0, forceValue);
    b2Vec2 localForce = body->GetLocalVector(force);

    if (b2Abs(body->GetLinearVelocity().Length()) < 5.0f) {
        body->ApplyForceToCenter(localForce, true);

        if (b2Abs(body->GetLinearVelocity().Length()) < epsilon) {
            body->SetLinearVelocity(b2Vec2_zero);
        }
    }

}

void Ship::rotateLeft(float torque) {
    ApplyTorqueWithCheck(-1.0f * torque);
}

void Ship::rotateRight(float torque) {
    ApplyTorqueWithCheck(1.0f * torque);
}

void Ship::ApplyTorqueWithCheck(float torque) {

    if (b2Abs(body->GetAngularVelocity()) < 0.5f) {

        body->ApplyTorque(torque, true);

        if (b2Abs(body->GetAngularVelocity()) < epsilon) {
            body->SetAngularVelocity(0.0f);
        }

    }

}

