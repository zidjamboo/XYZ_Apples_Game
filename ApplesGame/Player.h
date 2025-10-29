#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"

namespace ApplesGame
{
    enum class PlayerDirection
    {
        Right = 0,
        UP,
        Left,
        Down
    };

    struct Player
    {
        Position2D playerPosition;
        Size2D playerSize;
        float playerSpeed = 0.f;
        PlayerDirection playerDirection = PlayerDirection::Right;
        sf::RectangleShape playerShape;
    };

    void InitPlayer(Player& player);
}
