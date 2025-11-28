#include "Game.h"
#include <SFML/Audio.hpp>
#include <cassert>
#include "../UI/Background.h"
#include "../Settings/Textures.h"
#include "GameFinish.h"
#include "GameMode.h"
#include "../ScoreTable/LeaderBoard.h"

namespace
{
    using namespace ApplesGame;

    void EatPossibleApples(Game& game)
    {
        for (int i = 0; i < game.apples.size; ++i)
        {
            Apple& apple = game.apples.arr[i];

            if (apple.isEaten)
            {
                continue;
            }

            if (IsRectanglesCollide(
                    game.player.position,
                    game.player.size,
                    apple.position,
                    apple.size)
            )
            {
                if (IsFlagEnabled(GameMode::INFINITE))
                {
                MoveObject(apple.sprite, apple.position);
                }
                else
                {
                    apple.isEaten = true;
                }

                ++game.numEatenApples;

                if (IsFlagEnabled(GameMode::ACCELERATION))
                {
                    game.player.speed += ACCELERATION;
                }

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

        InitApples(game.apples, game.textures.apple);

        for (int i = 0; i < game.apples.size; ++i)
        {
            Apple& apple = game.apples.arr[i];
            MoveObject(apple.sprite, apple.position);
        }

        for (Rock& rock : game.rocks)
        {
            MoveObject(rock.sprite, rock.position);
        }

        isGameOver = false;
    }

    void InitGame(Game& game)
    {
        // Init textures
        assert(game.textures.player.loadFromFile(RESOURCES_PATH + "\\Player.png"));
        assert(game.textures.apple.loadFromFile(RESOURCES_PATH + "\\Apple.png"));
        assert(game.textures.rock.loadFromFile(RESOURCES_PATH + "\\Rock.png"));
        assert(game.textures.mainBackground.loadFromFile(RESOURCES_PATH + "\\Background.jpg"));
        assert(game.textures.winBackground.loadFromFile(RESOURCES_PATH + "\\WinBackground.jpg"));
        assert(game.textures.deathBackground.loadFromFile(RESOURCES_PATH + "\\GameOverBackground.jpg"));
        assert(game.textures.checkmark.loadFromFile(RESOURCES_PATH + "\\Checkmark.jpg"));

        // Init sounds
        sf::SoundBuffer& appleEatBuffer = game.sounds.appleEatBuffer;
        assert(appleEatBuffer.loadFromFile(RESOURCES_PATH + "\\AppleEat.wav"));
        game.sounds.appleEatSound.setBuffer(appleEatBuffer);

        // Init fonts
        assert(game.fonts.robotoRegular.loadFromFile(RESOURCES_PATH + "\\Fonts\\Roboto-Regular.ttf"));
        assert(game.fonts.robotoBold.loadFromFile(RESOURCES_PATH + "\\Fonts\\Roboto-Bold.ttf"));

        sf::SoundBuffer& deathBuffer = game.sounds.deathBuffer;
        assert(deathBuffer.loadFromFile(RESOURCES_PATH + "\\Death.wav"));
        game.sounds.deathSound.setBuffer(deathBuffer);

        sf::Sound ds(deathBuffer);
        ds.play();

        // Init game
        InitSetupMenu(game);
        InitPlayer(game.player, game.textures.player);
        InitRocks(game.rocks, game.textures.rock);
        InitBackground(game.mainBackground, game.textures.mainBackground);
        InitBackground(game.winBackground, game.textures.winBackground);
        InitBackground(game.deathBackground, game.textures.deathBackground);
        InitUI(game.ui, game.fonts);
    }

    void UpdateGame(Game& game, const float& deltaTime)
    {
        HandleInput(game.player.direction);
        SwitchDirection(game.player, deltaTime);
        RotatePlayer(game.player);
        EatPossibleApples(game);
        UpdateScore(game.ui, game.numEatenApples);
        CheckIfGameIsOver(game);
        if (isGameOver)
        {
            UpdateFinalScore(game.ui, game.finalScore);
        }
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
            DrawScore(game.ui, window);
        }
        else if (!isWin)
        {
            DrawBackground(game.deathBackground, window);
            std::unordered_map<std::string, int>& leaderBoardMap = *game.leaderBoardMap;
            leaderBoardMap["Player"] = game.finalScore;

            std::vector<Record> leaderBoard;
            for (const auto& pair: leaderBoardMap)
            {
                leaderBoard.push_back({pair.first, pair.second});
            }
            BubbleSort(leaderBoard);
            DrawLeaderBoard(game, leaderBoard, window);
        } else
        {
            DrawBackground(game.winBackground, window);
        }

        window.display();
    }

    void DeinitializeGame(Game& game)
    {
        delete[] game.apples.arr;
    }
}
