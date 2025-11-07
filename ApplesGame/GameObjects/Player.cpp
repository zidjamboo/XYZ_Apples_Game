#include "Player.h"
#include "Math.h"
#include "../Settings/Constants.h"
#include "../Game/Game.h"

namespace ApplesGame
{
    void InitPlayer(Player& player, const sf::Texture& playerTexture)
    {
        player.position = {SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f};
        player.size = {PLAYER_SIZE, PLAYER_SIZE};
        player.direction = PlayerDirection::Right;

        player.sprite.setTexture(playerTexture);
        setSpriteSize(player.sprite, player.size);
        setSpriteRelativeOrigin(player.sprite, CENTER, CENTER);
    }

    void DrawPlayer(Player& player, sf::RenderWindow& window)
    {
        player.sprite.setPosition(player.position.x, player.position.y);
        window.draw(player.sprite);
    }

    void HandleInput(PlayerDirection& playerDirection)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            playerDirection = PlayerDirection::Right;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            playerDirection = PlayerDirection::UP;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            playerDirection = PlayerDirection::Left;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            playerDirection = PlayerDirection::Down;
        }
    }

    void SwitchDirection(Player& player, const float& deltaTime)
    {
        const PlayerDirection& playerDirection = player.direction;
        switch (playerDirection)
        {
        case PlayerDirection::Right:
            {
                player.position.x += player.speed * deltaTime;
                break;
            }
        case PlayerDirection::UP:
            {
                player.position.y -= player.speed * deltaTime;
                break;
            }
        case PlayerDirection::Left:
            {
                player.position.x -= player.speed * deltaTime;
                break;
            }
        case PlayerDirection::Down:
            {
                player.position.y += player.speed * deltaTime;
                break;
            }
        }
    }

    void RotatePlayer(Player& player)
    {
        const PlayerDirection& playerDirection = player.direction;
        const Size2D playerSize = player.size;
        sf::Sprite& sprite = player.sprite;
        if (playerDirection == PlayerDirection::Right)
        {
            setSpriteSize(sprite, playerSize);
            sprite.setRotation(0.f);
        }
        else if (playerDirection == PlayerDirection::Down)
        {
            sprite.setRotation(90.f);
        }
        else if (playerDirection == PlayerDirection::Left)
        {
            setSpriteSize(sprite, {playerSize.x, -playerSize.y});
            sprite.setRotation(180.f);
        }
        else if (playerDirection == PlayerDirection::UP)
        {
            sprite.setRotation(270.f);
        }
    }
}
