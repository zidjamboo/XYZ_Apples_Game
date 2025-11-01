#include "UI.h"

namespace ApplesGame
{
    constexpr int SCORE_FONT_SIZE = 24;
    constexpr int FINAL_SCORE_FONT_SIZE = 96;

    void InitUI(UI& ui, const Fonts& fonts)
    {
        sf::Text& score = ui.score;
        score.setFont(fonts.robotoRegular);
        score.setCharacterSize(SCORE_FONT_SIZE);
        score.setFillColor(sf::Color::Yellow);
        score.setPosition(10.f, 10.f);

        sf::Text& finalScore = ui.finalScore;
        finalScore.setFont(fonts.robotoBold);
        finalScore.setCharacterSize(FINAL_SCORE_FONT_SIZE);
        finalScore.setFillColor(sf::Color::Yellow);
        finalScore.setPosition(270.f, 430.f);
    }

    void UpdateScore(UI& ui, const int& newScore)
    {
        ui.score.setString("Score: " + std::to_string(newScore));
    }

    void UpdateFinalScore(UI& ui, const int& finalScore)
    {
        const char* space = finalScore < 10 ? " " : "";
        ui.finalScore.setString(space + std::to_string(finalScore));
    }

    void DrawScore(UI& ui, sf::RenderWindow& window)
    {
        window.draw(ui.score);
    }

    void DrawFinalScore(UI& ui, sf::RenderWindow& window)
    {
        window.draw(ui.finalScore);
    }
}
