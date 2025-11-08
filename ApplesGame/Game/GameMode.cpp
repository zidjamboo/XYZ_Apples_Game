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

    void InitText(sf::Text& text, const ApplesGame::Game& game, const sf::String& string)
    {
        text.setFont(game.fonts.robotoRegular);
        text.setCharacterSize(32);
        text.setString(string);
    }

    void InitCheckMark(sf::Sprite& checkmark, const ApplesGame::Game& game)
    {
        checkmark.setTexture(game.textures.checkmark);
        ApplesGame::setSpriteSize(checkmark, {CHECKMARK_SIZE, CHECKMARK_SIZE});
    }
}

namespace ApplesGame
{
    bool isNeedSetupGame = true;

    void InitGameMode(Game& game)
    {
        background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
        background.setFillColor(sf::Color::Black);
        background.setPosition(0.f, 0.f);

        InitText(infinite, game, "Infinite");
        InitText(acceleration, game, "Acceleration");
        InitText(hardMode, game, "HardMode");
        infinite.setPosition(10.f, 5.f);
        acceleration.setPosition(10.f, 45.f);
        hardMode.setPosition(10.f, 85.f);

        InitCheckMark(infiniteCheckmark, game);
        InitCheckMark(accelerationCheckmark, game);
        InitCheckMark(hardModeCheckmark, game);
        infiniteCheckmark.setPosition(200.f, 10.f);
        accelerationCheckmark.setPosition(200.f, 50.f);
        hardModeCheckmark.setPosition(200.f, 90.f);
    }

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
