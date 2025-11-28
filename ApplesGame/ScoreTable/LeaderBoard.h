#pragma once
#include <string>
#include <vector>

#include "SFML/Graphics/RenderWindow.hpp"

namespace ApplesGame
{
    struct Record
    {
        std::string name;
        int score;
    };

    struct Game;

    void BubbleSort(std::vector<Record> vector);
    void DrawLeaderBoard(const Game& game, const std::vector<Record>& leaderBoard, sf::RenderWindow& window);
}
