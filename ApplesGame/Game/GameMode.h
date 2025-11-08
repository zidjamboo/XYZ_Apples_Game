#pragma once
#include <cstdint>
#include <SFML/Graphics.hpp>

namespace ApplesGame
{
    extern bool isNeedSetupGame;

    enum class GameMode : std::uint8_t
    {
        INFINITE = 0,
        ACCELERATION = 1,
        HARDMODE = 2
    };

    struct Game;
    void SetFlagEnabled(const GameMode& flag, const bool& enabled);
    bool IsFlagEnabled(const GameMode& flag);
    void DropSettingsToDefaults();
    void InitSetupMenu(const Game& game);
    void UpdateSetupMenu(const sf::Clock& clock, const sf::Event& event);
    void DrawSetupMenu(sf::RenderWindow& window);
}
