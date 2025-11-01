#pragma once
#include <SFML/Graphics.hpp>

namespace ApplesGame
{
    struct Background
    {
        sf::Sprite sprite;

    };

    void InitBackground(Background& background, sf::Texture& texture);
    void DrawBackground(const Background& background, sf::RenderWindow& window);
}
