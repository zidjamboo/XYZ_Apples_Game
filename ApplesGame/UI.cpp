#include "UI.h"

namespace ApplesGame
{
    void InitUI(UI& ui, const Fonts& fonts)
    {
        sf::Text& score = ui.score;
        score.setFont(fonts.robotoRegular);
        score.setCharacterSize(24);
        score.setFillColor(sf::Color::Yellow);
        score.setPosition(10.f, 10.f);
    }

    void UpdateScore(UI& ui, const int& newScore)
    {
        ui.score.setString("Score: " + std::to_string(newScore));
    }

    void DrawUI(UI& ui, sf::RenderWindow& window)
    {
        window.draw(ui.score);
    }
}
