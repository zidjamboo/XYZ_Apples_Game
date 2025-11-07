// ©2023, XYZ School. All rights reserved.
// Authored by Aleksandr Rybalka (polterageist@gmail.com)

#include <SFML/Graphics.hpp>
#include "Game.h"
#include "GameFinish.h"
#include "../Settings/Constants.h"


int main()
{
    using namespace ApplesGame;
    int seed = (int)time(nullptr);
    srand(seed);

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Apples Game");

    Game game;
    InitGame(game);

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

        if (isGameOver)
        {
            RestartGame(game);
            StartPause();
        }

        if (isNeedPause(deltaTime))
        {
            continue;
        }

        UpdateGame(game, deltaTime);
        DrawGame(game, window);
    }

    DeinitializeGame(game);

    return 0;
}
