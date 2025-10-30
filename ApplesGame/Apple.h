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

    struct Game;
    void InitApples(Apple (&apples)[NUM_APPLES]);
    void DrawApples(Game& game, sf::RenderWindow& window);
    void EatPossibleApples(Game& game);
}
