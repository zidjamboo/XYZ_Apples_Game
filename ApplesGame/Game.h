#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Apple.h"
#include "Rock.h"
#include "Background.h"
#include "Math.h"
#include "Constants.h"
#include "Sounds.h"
#include "Textures.h"

namespace ApplesGame
{
    struct Game
    {
        // Player data
        Player player;

        // Apples data
        Apple apples[NUM_APPLES];

        // Rocks data
        Rock rocks[NUM_ROCKS];

        // Global game data
        int numEatenApples = 0;

        // Background
        Background mainBackground;

        // Textures
        Textures textures;

        // Sounds
        Sounds sounds;
    };

    void MoveObject(sf::Sprite& sprite, Position2D& position);
    void RestartGame(Game& game);
    void InitGame(Game& game);
    void UpdateGame(Game& game, float& deltaTime);
    void DrawGame(Game& game, sf::RenderWindow& window);
}
