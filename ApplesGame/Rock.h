#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"
#include "Constants.h"

namespace ApplesGame
{
    struct Rock
    {
        Position2D position;
        Size2D size;
        sf::Sprite sprite;
    };

    struct Game;
    void InitRocks(Rock (&rocks)[NUM_ROCKS], sf::Texture& rockTexture);
    void DrawRocks(Rock (&rocks)[NUM_ROCKS], sf::RenderWindow& window);
}
