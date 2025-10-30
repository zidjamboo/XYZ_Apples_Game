#include "Game.h"
#include <cassert>

namespace
{
    void HandleInput(ApplesGame::PlayerDirection& playerDirection)
    {
        using namespace ApplesGame;
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

    void SwitchDirection(ApplesGame::Player& player, const float& deltaTime)
    {
        using namespace ApplesGame;
        const PlayerDirection& playerDirection = player.playerDirection;
        switch (playerDirection)
        {
        case PlayerDirection::Right:
            {
                player.playerPosition.x += player.playerSpeed * deltaTime;
                break;
            }
        case PlayerDirection::UP:
            {
                player.playerPosition.y -= player.playerSpeed * deltaTime;
                break;
            }
        case PlayerDirection::Left:
            {
                player.playerPosition.x -= player.playerSpeed * deltaTime;
                break;
            }
        case PlayerDirection::Down:
            {
                player.playerPosition.y += player.playerSpeed * deltaTime;
                break;
            }
        }
    }

    void RotatePlayer(ApplesGame::Player& player)
    {
        using namespace ApplesGame;
        const PlayerDirection& playerDirection = player.playerDirection;
        const Size2D playerSize = player.playerSize;
        sf::Sprite& sprite = player.playerSprite;
        if (playerDirection == PlayerDirection::Right)
        {
            setSpriteSize(sprite, playerSize.x, playerSize.y);
            sprite.setRotation(0.f);
        }
        else if (playerDirection == PlayerDirection::Down)
        {
            sprite.setRotation(90.f);
        }
        else if (playerDirection == PlayerDirection::Left)
        {
            setSpriteSize(sprite, playerSize.x, -playerSize.y);
            sprite.setRotation(180.f);
        }
        else if (playerDirection == PlayerDirection::UP)
        {
            sprite.setRotation(270.f);
        }
    }
}

namespace ApplesGame
{
    void MoveObject(sf::Shape& objectShape, Position2D& objectPosition)
    {
        objectPosition = GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);
        objectShape.setPosition(objectPosition.x, objectPosition.y);
    }

    void RestartGame(Game& game)
    {
        game.player.playerPosition.x = SCREEN_WIDTH / 2.f;
        game.player.playerPosition.y = SCREEN_HEIGHT / 2.f;
        game.player.playerSprite.setPosition(game.player.playerPosition.x, game.player.playerPosition.y);
        game.player.playerSpeed = INITIAL_SPEED;
        game.player.playerDirection = PlayerDirection::Right;

        for (Apple& apple : game.apples)
        {
            MoveObject(apple.appleShape, apple.applePosition);
        }

        for (Rock& rock : game.rocks)
        {
            MoveObject(rock.rockShape, rock.rockPosition);
        }
    }

    void InitGame(Game& game)
    {
        assert(game.playerTexture.loadFromFile(RESOURCES_PATH + "/Player.png"));
        InitPlayer(game.player, game);
        InitApples(game.apples);
        InitRocks(game.rocks);
        RestartGame(game);
    }

    void UpdateGame(Game& game, float& deltaTime)
    {
        HandleInput(game.player.playerDirection);
        SwitchDirection(game.player, deltaTime);
        RotatePlayer(game.player);
    }

    void DrawGame(Game& game, sf::RenderWindow& window)
    {
        window.clear();

        DrawPlayer(game.player, window);
        DrawApples(game.apples, window);
        DrawRocks(game.rocks, window);

        window.display();
    }
}
