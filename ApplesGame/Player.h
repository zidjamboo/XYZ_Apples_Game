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
        Position2D playerPosition;
        Size2D playerSize;
        float playerSpeed = 0.f;
        PlayerDirection playerDirection = PlayerDirection::Right;
        sf::Sprite playerSprite;
    };

    struct Game;

    void InitPlayer(Player& player, const Game& game);
    void DrawPlayer(Player& player, sf::RenderWindow& window);
}
