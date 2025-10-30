#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Apple.h"
#include "Rock.h"
#include "Math.h"
#include "Constants.h"

namespace ApplesGame
{
    struct Game
    {
        // Player data
        Player player;

        //Apples data
        Apple apples[NUM_APPLES];

        //Rocks data
        Rock rocks[NUM_ROCKS];

        //Global game data
        int numEatenApples = 0;
        bool isGameOver = false;
        float pauseTimeLeft = 0.f;

        // textures
        sf::Texture playerTexture;
    };

    void MoveObject(sf::Shape& objectShape, Position2D& objectPosition);
    void RestartGame(Game& game);
    void InitGame(Game& game);
    void UpdateGame(Game& game, float& deltaTime);
    void DrawGame(Game& game, sf::RenderWindow& window);
    void StartPause(Game& game);
    bool isNeedPause(Game& game, float deltaTime);
}
