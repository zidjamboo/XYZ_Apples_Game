#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"

namespace ApplesGame
{
    enum class PlayerDirection
    {
        Right, UP, Left, Down
    };

    struct Player
    {
        Position2D position;
        Size2D size;
        float speed = 0.f;
        PlayerDirection direction = PlayerDirection::Right;
        sf::Sprite sprite;
    };

    struct Game;

    void InitPlayer(Player& player, const sf::Texture& playerTexture);
    void DrawPlayer(Player& player, sf::RenderWindow& window);
}
