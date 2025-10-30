#include "Game.h"
#include <SFML/Audio.hpp>
#include <cassert>

#include "Textures.h"

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

    void RotatePlayer(ApplesGame::Player& player)
    {
        using namespace ApplesGame;
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

namespace ApplesGame
{
    void MoveObject(sf::Sprite& sprite, Position2D& position)
    {
        position = GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);
        sprite.setPosition(position.x, position.y);
    }

    void RestartGame(Game& game)
    {
        game.player.position.x = SCREEN_WIDTH / 2.f;
        game.player.position.y = SCREEN_HEIGHT / 2.f;
        game.player.sprite.setPosition(game.player.position.x, game.player.position.y);
        game.player.speed = INITIAL_SPEED;
        game.player.direction = PlayerDirection::Right;

        for (Apple& apple : game.apples)
        {
            MoveObject(apple.sprite, apple.position);
        }

        for (Rock& rock : game.rocks)
        {
            MoveObject(rock.sprite, rock.position);
        }
    }

    void InitGame(Game& game)
    {
        // Init textures
        assert(game.textures.player.loadFromFile(RESOURCES_PATH + "\\Player.png"));
        assert(game.textures.apple.loadFromFile(RESOURCES_PATH + "\\Apple.png"));
        assert(game.textures.rock.loadFromFile(RESOURCES_PATH + "\\Rock.png"));

        // Init sounds
        sf::SoundBuffer& appleEatBuffer = game.sounds.appleEatBuffer;
        assert(appleEatBuffer.loadFromFile(RESOURCES_PATH + "\\AppleEat.wav"));
        game.sounds.appleEatSound.setBuffer(appleEatBuffer);

        sf::SoundBuffer& deathBuffer = game.sounds.deathBuffer;
        assert(deathBuffer.loadFromFile(RESOURCES_PATH + "\\Death.wav"));
        game.sounds.deathSound.setBuffer(deathBuffer);

        sf::Sound ds(deathBuffer);
        ds.play();

        // Init game
        InitPlayer(game.player, game.textures.player);
        InitApples(game.apples, game.textures.apple);
        InitRocks(game.rocks, game.textures.rock);

        RestartGame(game);
    }

    void UpdateGame(Game& game, float& deltaTime)
    {
        HandleInput(game.player.direction);
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
