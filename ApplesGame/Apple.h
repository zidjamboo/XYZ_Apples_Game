#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"
#include "Constants.h"

namespace ApplesGame
{
    struct Apple
    {
        Position2D applePosition;
        CircleSize appleSize;
        sf::CircleShape appleShape;
    };

    void InitApples(Apple (&apples)[NUM_APPLES]);
}
