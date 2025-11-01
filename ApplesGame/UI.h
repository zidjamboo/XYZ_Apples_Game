#pragma once
#include <SFML/Graphics.hpp>

namespace ApplesGame
{
    struct Fonts
    {
        sf::Font robotoRegular;
    };

    struct UI
    {
        sf::Text score;
    };

    void InitUI(UI& ui, const Fonts& fonts);
    void UpdateScore(UI& ui, const int& newScore);
    void DrawUI(UI& ui, sf::RenderWindow& window);
}
