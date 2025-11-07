#pragma once
#include <SFML/Graphics.hpp>

namespace ApplesGame
{
    struct Fonts
    {
        sf::Font robotoRegular;
        sf::Font robotoBold;
    };

    struct UI
    {
        sf::Text score;
        sf::Text finalScore;
    };

    void InitUI(UI& ui, const Fonts& fonts);
    void UpdateScore(UI& ui, const int& newScore);
    void UpdateFinalScore(UI& ui, const int& finalScore);
    void DrawScore(UI& ui, sf::RenderWindow& window);
    void DrawFinalScore(UI& ui, sf::RenderWindow& window);
}
