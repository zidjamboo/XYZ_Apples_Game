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

    ApplesGame::GameMode selectedMode = ApplesGame::GameMode::INFINITE;

    sf::Int32 lastClickTime = 0;

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

    void UpdateTextColor(sf::Text& text, const bool& isSelected)
    {
        if (isSelected)
        {
            text.setFillColor(sf::Color::Yellow);
        }
        else
        {
            text.setFillColor(sf::Color::White);
        }
    }
}

namespace ApplesGame
{
    bool isNeedSetupGame = true;

    void SetFlagEnabled(const GameMode& flag, const bool& enabled = true)
    {
        if (enabled)
        {
            gameMode |= 1 << static_cast<uint8_t>(flag);
        }
        else
        {
            gameMode &= ~(1 << static_cast<uint8_t>(flag));
        }
    }

    bool IsFlagEnabled(const GameMode& flag)
    {
        return gameMode & 1 << static_cast<int>(flag);
    }

    void DropSettingsToDefaults()
    {
        isNeedSetupGame = true;
        SetFlagEnabled(GameMode::INFINITE, false);
        SetFlagEnabled(GameMode::ACCELERATION, false);
        SetFlagEnabled(GameMode::HARD_MODE, false);
    }

    void InitSetupMenu(const Game& game)
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

    void UpdateSetupMenu(const sf::Clock& clock, const sf::Event& event)
    {
        if (event.type == sf::Event::KeyReleased)
        {
            lastClickTime = 0;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            isNeedSetupGame = false;
        }

        sf::Int32 clickTime = clock.getElapsedTime().asMilliseconds();
        if (clickTime - lastClickTime < 500)
        {
            return;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            lastClickTime = clickTime;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
        {
            SetFlagEnabled(selectedMode, !IsFlagEnabled(selectedMode));
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            int selectedIndex = static_cast<int>(selectedMode);
            ++selectedIndex;
            if (selectedIndex > 2)
            {
                selectedIndex = 0;
            }

            selectedMode = static_cast<GameMode>(selectedIndex);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            int selectedIndex = static_cast<int>(selectedMode);
            --selectedIndex;
            if (selectedIndex < 0)
            {
                selectedIndex = 2;
            }

            selectedMode = static_cast<GameMode>(selectedIndex);
        }

        UpdateTextColor(infinite, selectedMode == GameMode::INFINITE);
        UpdateTextColor(acceleration, selectedMode == GameMode::ACCELERATION);
        UpdateTextColor(hardMode, selectedMode == GameMode::HARD_MODE);
    }

    void DrawSetupMenu(sf::RenderWindow& window)
    {
        window.draw(background);
        window.draw(infinite);
        window.draw(acceleration);
        window.draw(hardMode);

        if (IsFlagEnabled(GameMode::INFINITE))
        {
            window.draw(infiniteCheckmark);
        }
        if (IsFlagEnabled(GameMode::ACCELERATION))
        {
            window.draw(accelerationCheckmark);
        }
        if (IsFlagEnabled(GameMode::HARD_MODE))
        {
            window.draw(hardModeCheckmark);
        }
    }
}
