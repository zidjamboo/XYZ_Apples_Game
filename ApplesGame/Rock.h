#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"
#include "Constants.h"

namespace ApplesGame
{
    struct Rock
    {
        Position2D rockPosition;
        Size2D rocksSize;
        sf::RectangleShape rockShape;
    };

    struct Game;
    void InitRocks(Rock (&rocks)[NUM_ROCKS]);
    void DrawRocks(Rock (&rocks)[NUM_ROCKS], sf::RenderWindow& window);
}
