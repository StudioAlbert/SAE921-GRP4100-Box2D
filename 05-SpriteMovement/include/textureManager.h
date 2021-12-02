
#pragma once

#include <string>

#include "SFML/Graphics.hpp"

/**
 * The Singleton class defines the `GetInstance` method that serves as an
 * alternative to constructor and lets clients access the same instance of this
 * class over and over.
 */
class TextureManager
{

    /**
     * The Singleton's constructor should always be private to prevent direct
     * construction calls with the `new` operator.
     */

protected:
    TextureManager();

    static TextureManager* textureManager_;

    std::string ferFerArgent_ = "FerFerArgent";

    sf::Texture m_asteroidTexture;

public:

    /**
     * Singletons should not be cloneable.
     */
    TextureManager(TextureManager& other) = delete;
    /**
     * Singletons should not be assignable.
     */
    void operator=(const TextureManager&) = delete;

    /**
     * This is the static method that controls the access to the singleton
     * instance. On the first run, it creates a singleton object and places it
     * into the static field. On subsequent runs, it returns the client existing
     * object stored in the static field.
     */
    static TextureManager* Instance();


    // --------------------
    std::string getFerFerArgent();

    sf::Texture& getAsteroidTexture();

};


