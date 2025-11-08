#pragma once
#include <SFML/Graphics.hpp>
#include "../GameObjects/Player.h"
#include "../GameObjects/Apple.h"
#include "../GameObjects/Rock.h"
#include "../UI/Background.h"
#include "../Math/Math.h"
#include "../Settings/Constants.h"
#include "../Settings/Sounds.h"
#include "../Settings/Textures.h"
#include "../UI/UI.h"

namespace ApplesGame
{
    struct Game
    {
        // Player data
        Player player;

        // Apples data
        ApplesArray apples;

        // Rocks data
        Rock rocks[NUM_ROCKS];

        // Global game data
        int numEatenApples = 0;
        int finalScore = 0;

        // Background
        Background mainBackground;
        Background winBackground;
        Background deathBackground;

        // Textures
        Textures textures;

        // Sounds
        Sounds sounds;

        // UI
        Fonts fonts;
        UI ui;

        // Flags
        bool isNeedSettings = true;
    };

    void MoveObject(sf::Sprite& sprite, Position2D& position);
    void RestartGame(Game& game);
    void InitGame(Game& game);
    void UpdateGame(Game& game, float& deltaTime);
    void DrawGame(Game& game, sf::RenderWindow& window);
    void DeinitializeGame(Game& game);
}
