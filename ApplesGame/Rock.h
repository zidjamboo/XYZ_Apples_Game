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

    void InitRocks(Rock (&rocks)[NUM_ROCKS]);
}
