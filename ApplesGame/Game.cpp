#include "Game.h"
#include <cassert>

namespace
{
    void HandleInput(ApplesGame::Game& game)
    {
        using namespace ApplesGame;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            game.player.playerDirection = PlayerDirection::Right;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            game.player.playerDirection = PlayerDirection::UP;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            game.player.playerDirection = PlayerDirection::Left;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            game.player.playerDirection = PlayerDirection::Down;
        }
    }

    void SwitchDirection(ApplesGame::Game& game, const float& deltaTime)
    {
        using namespace ApplesGame;
        switch (game.player.playerDirection)
        {
        case PlayerDirection::Right:
            {
                game.player.playerPosition.x += game.player.playerSpeed * deltaTime;
                break;
            }
        case PlayerDirection::UP:
            {
                game.player.playerPosition.y -= game.player.playerSpeed * deltaTime;
                break;
            }
        case PlayerDirection::Left:
            {
                game.player.playerPosition.x -= game.player.playerSpeed * deltaTime;
                break;
            }
        case PlayerDirection::Down:
            {
                game.player.playerPosition.y += game.player.playerSpeed * deltaTime;
                break;
            }
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
        HandleInput(game);
        SwitchDirection(game, deltaTime);
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
