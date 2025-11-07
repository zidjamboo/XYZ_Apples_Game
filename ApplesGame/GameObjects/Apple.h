#pragma once
#include <SFML/Graphics.hpp>
#include "../Math/Math.h"

namespace ApplesGame
{
    struct Apple
    {
        Position2D position;
        Size2D size;
        sf::Sprite sprite;
    };

    struct ApplesArray
    {
        Apple* arr = nullptr;
        int size = 0;
    };

    struct Game;
    void InitApples(ApplesArray& apples, const sf::Texture& appleTexture);
    void DrawApples(const ApplesArray& apples, sf::RenderWindow& window);
}
