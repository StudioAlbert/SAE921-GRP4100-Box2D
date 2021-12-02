#include "textureManager.h"

TextureManager* TextureManager::textureManager_ = nullptr;

TextureManager::TextureManager()
{
    m_asteroidTexture.loadFromFile("./data/Asteroid.png");
}


/**
 * Static methods should be defined outside the class.
 */
TextureManager* TextureManager::Instance()
{
    /**
     * This is a safer way to create an instance. instance = new Singleton is
     * dangeruous in case two instance threads wants to access at the same time
     */
    if (textureManager_ == nullptr) {
        textureManager_ = new TextureManager();
    }
    return textureManager_;
}

std::string TextureManager::getFerFerArgent() {
    return ferFerArgent_;
}

sf::Texture& TextureManager::getAsteroidTexture() {
    return m_asteroidTexture;
}
