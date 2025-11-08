#include "GameMode.h"

#include "Game.h"
#include "../Settings/Constants.h"

namespace
{
    constexpr int CHECKMARK_SIZE = 35;

    std::uint8_t gameMode = 0;
    sf::RectangleShape background;

    sf::Text infinite;
    sf::Text acceleration;
    sf::Text hardMode;

    sf::Sprite infiniteCheckmark;
    sf::Sprite accelerationCheckmark;
    sf::Sprite hardModeCheckmark;

    void InitText(
        sf::Text& text,
        const ApplesGame::Game& game,
        const sf::String& string,
        const ApplesGame::Position2D position)
    {
        text.setFont(game.fonts.robotoRegular);
        text.setCharacterSize(32);
        text.setString(string);
        text.setPosition(position.x, position.y);
    }

    void InitCheckMark(sf::Sprite& checkmark, const ApplesGame::Game& game, ApplesGame::Position2D position)
    {
        checkmark.setTexture(game.textures.checkmark);
        ApplesGame::setSpriteSize(checkmark, {CHECKMARK_SIZE, CHECKMARK_SIZE});
        checkmark.setPosition(position.x, position.y);
    }
}

namespace ApplesGame
{
    bool isNeedSetupGame = true;

    void SetFlagEnabled(const GameMode& flag, const bool& enabled = true)
    {
        if (enabled)
        {
            gameMode |= static_cast<uint8_t>(flag);
        }
        else
        {
            gameMode &= ~static_cast<uint8_t>(flag);
        }
    }

    bool IsFlagEnabled(const GameMode& flag)
    {
        return gameMode & static_cast<int>(flag);
    }

    void DropSettingsToDefaults()
    {
        isNeedSetupGame = true;
        SetFlagEnabled(GameMode::INFINITE, false);
        SetFlagEnabled(GameMode::ACCELERATION, false);
        SetFlagEnabled(GameMode::HARDMODE, false);
    }

    void InitGameMode(const Game& game)
    {
        background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
        background.setFillColor(sf::Color::Black);
        background.setPosition(0.f, 0.f);

        InitText(infinite, game, "Infinite", {10.f, 10.f});
        InitText(acceleration, game, "Acceleration", {10.f, 50.f});
        InitText(hardMode, game, "HardMode", {10.f, 90.f});

        InitCheckMark(infiniteCheckmark, game, {200.f, 15.f});
        InitCheckMark(accelerationCheckmark, game, {200.f, 55.f});
        InitCheckMark(hardModeCheckmark, game, {200.f, 95.f});
    }

    void DrawSetupMenu(sf::RenderWindow& window)
    {
        window.draw(background);
        window.draw(infinite);
        window.draw(acceleration);
        window.draw(hardMode);
        window.draw(infiniteCheckmark);
        window.draw(accelerationCheckmark);
        window.draw(hardModeCheckmark);
    }
}
