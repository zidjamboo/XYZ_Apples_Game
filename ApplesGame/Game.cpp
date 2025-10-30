#include "Game.h"
#include <cassert>

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

        for (int i = 0; i < NUM_APPLES; ++i)
        {
            MoveObject(game.apples[i].appleShape, game.apples[i].applePosition);
        }

        for (int i = 0; i < NUM_ROCKS; ++i)
        {
            MoveObject(game.rocks[i].rockShape, game.rocks[i].rockPosition);
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

    void DrawGame(Game& game, sf::RenderWindow& window)
    {
        window.clear();

        DrawPlayer(game.player, window);

        for (int i = 0; i < NUM_APPLES; ++i)
        {
            window.draw(game.apples[i].appleShape);
        }

        for (int i = 0; i < NUM_ROCKS; ++i)
        {
            window.draw(game.rocks[i].rockShape);
        }

        window.display();
    }

    void StartPause(Game& game)
    {
        game.pauseTimeLeft = INITIAL_PAUSE_TIME;
        game.isGameOver = false;
    }

    bool isNeedPause(Game& game, float deltaTime)
    {
        if (game.pauseTimeLeft > 0.f)
        {
            game.pauseTimeLeft -= deltaTime;
            return true;
        }

        return false;
    }

    void CheckIfGameOver(Game& game)
    {
        bool isCollapsedWithRock = false;
        for (int i = 0; i < NUM_ROCKS; ++i)
        {
            if (IsRectanglesCollide(
                    game.player.playerPosition,
                    game.player.playerSize,
                    game.rocks[i].rockPosition,
                    game.rocks[i].rocksSize)
            )
            {
                isCollapsedWithRock = true;
                break;
            }
        }

        if (
            isCollapsedWithRock ||
            game.player.playerPosition.x - game.player.playerSize.x / 2.f < 0 || game.player.playerPosition.x + game.
            player.playerSize.x / 2.f > SCREEN_WIDTH ||
            game.player.playerPosition.y - game.player.playerSize.y / 2.f < 0 || game.player.playerPosition.y + game.
            player.playerSize.y / 2.f > SCREEN_HEIGHT
        )
        {
            game.isGameOver = true;
        }
    }
}
