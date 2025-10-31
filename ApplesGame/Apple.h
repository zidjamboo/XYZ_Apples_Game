#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"
#include "Constants.h"

namespace ApplesGame
{
    struct Apple
    {
        Position2D position;
        Size2D size;
        sf::Sprite sprite;
    };

    struct Game;
    void InitApples(Apple (&apples)[NUM_APPLES], const sf::Texture& appleTexture);
    void DrawApples(Apple (&apples)[NUM_APPLES], sf::RenderWindow& window);
}
