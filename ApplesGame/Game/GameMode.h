#pragma once
#include <cstdint>
#include <SFML/Graphics.hpp>

namespace ApplesGame
{
    extern bool isNeedSetupGame;

    enum class GameMode : std::uint8_t
    {
        INFINITE = 1 << 0,
        ACCELERATION = 1 << 1,
        HARDMODE = 1 << 2
    };

    struct Game;
    void InitGameMode(Game& game);
    void SetFlagEnabled(const GameMode& flag, const bool& enabled);
    bool IsFlagEnabled(const GameMode& flag);
    void DropSettingsToDefaults();
    void DrawSetupMenu(sf::RenderWindow& window);
}
