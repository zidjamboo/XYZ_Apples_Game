// ©2023, XYZ School. All rights reserved.
// Authored by Aleksandr Rybalka (polterageist@gmail.com)

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Game.h"
#include "Math.h"
#include "Constants.h"


int main()
{
    using namespace ApplesGame;
    int seed = (int)time(nullptr);
    srand(seed);

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Apples Game");

    Game game;
    InitGame(game);

    int numEatenApples = 0;

    sf::Clock gameClock;
    float lastTime = gameClock.getElapsedTime().asSeconds();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float currentTime = gameClock.getElapsedTime().asSeconds();
        float deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        if (game.isGameOver)
        {
            RestartGame(game);
            StartPause(game);
        }

        if (isNeedPause(game, deltaTime))
        {
            continue;
        }

        UpdateGame(game, deltaTime);

        for (int i = 0; i < NUM_APPLES; ++i)
        {
            if (isCirclesCollide(
                    game.player.playerPosition,
                    {game.player.playerSize.x},
                    game.apples[i].applePosition,
                    game.apples[i].appleSize)
            )
            {
                MoveObject(game.apples[i].appleShape, game.apples[i].applePosition);
                ++game.numEatenApples;
                game.player.playerSpeed += ACCELERATION;
            }
        }

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

        DrawGame(game, window);
    }

    return 0;
}
