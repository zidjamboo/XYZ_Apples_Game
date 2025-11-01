#include "Game.h"
#include <SFML/Audio.hpp>
#include <cassert>
#include "Background.h"
#include "Textures.h"
#include "GameFinish.h"

namespace
{
    using namespace ApplesGame;

    void EatPossibleApples(Game& game)
    {
        for (Apple& apple : game.apples)
        {
            if (IsRectanglesCollide(
                    game.player.position,
                    game.player.size,
                    apple.position,
                    apple.size)
            )
            {
                MoveObject(apple.sprite, apple.position);
                ++game.numEatenApples;
                game.player.speed += ACCELERATION;

                game.sounds.appleEatSound.play();
            }
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

        game.numEatenApples = 0;

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
        assert(game.textures.mainBackground.loadFromFile(RESOURCES_PATH + "\\Background.jpg"));
        assert(game.textures.deathBackground.loadFromFile(RESOURCES_PATH + "\\GameOverBackground.jpg"));

        // Init sounds
        sf::SoundBuffer& appleEatBuffer = game.sounds.appleEatBuffer;
        assert(appleEatBuffer.loadFromFile(RESOURCES_PATH + "\\AppleEat.wav"));
        game.sounds.appleEatSound.setBuffer(appleEatBuffer);

        // Init fonts
        assert(game.fonts.robotoRegular.loadFromFile(RESOURCES_PATH + "\\Fonts\\Roboto-Regular.ttf"));

        sf::SoundBuffer& deathBuffer = game.sounds.deathBuffer;
        assert(deathBuffer.loadFromFile(RESOURCES_PATH + "\\Death.wav"));
        game.sounds.deathSound.setBuffer(deathBuffer);

        sf::Sound ds(deathBuffer);
        ds.play();

        // Init game
        InitPlayer(game.player, game.textures.player);
        InitApples(game.apples, game.textures.apple);
        InitRocks(game.rocks, game.textures.rock);
        InitBackground(game.mainBackground, game.textures.mainBackground);
        InitBackground(game.deathBackground, game.textures.deathBackground);
        InitUI(game.ui, game.fonts);

        RestartGame(game);
    }

    void UpdateGame(Game& game, float& deltaTime)
    {
        HandleInput(game.player.direction);
        SwitchDirection(game.player, deltaTime);
        RotatePlayer(game.player);
        EatPossibleApples(game);
        UpdateScore(game.ui, game.numEatenApples);
        CheckIfGameIsOver(game.sounds.deathSound, game.player, game.rocks);
    }

    void DrawGame(Game& game, sf::RenderWindow& window)
    {
        window.clear();

        if (!isGameOver)
        {
            DrawBackground(game.mainBackground, window);
            DrawPlayer(game.player, window);
            DrawApples(game.apples, window);
            DrawRocks(game.rocks, window);
            DrawUI(game.ui, window);
        }
        else
        {
            DrawBackground(game.deathBackground, window);
        }

        window.display();
    }
}
