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
        sf::sleep(sf::milliseconds(16));

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
        EatPossibleApples(game);
        CheckIfGameOver(game);
        DrawGame(game, window);
    }

    return 0;
}
