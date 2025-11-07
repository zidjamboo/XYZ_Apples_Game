#pragma once
#include <SFML/Audio.hpp>

namespace ApplesGame
{
    struct Sounds
    {
        sf::SoundBuffer appleEatBuffer;
        sf::Sound appleEatSound;

        sf::SoundBuffer deathBuffer;
        sf::Sound deathSound;
    };
}
