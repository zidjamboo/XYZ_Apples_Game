#pragma once
#include <string>
#include <vector>
#include <unordered_map>

#include "SFML/Graphics/RenderWindow.hpp"

namespace ApplesGame
{
    struct Record
    {
        std::string name;
        int score;
    };

    struct Game;

    std::shared_ptr<std::unordered_map<std::string, int>> GenerateLeaderBoardMap();
    void BubbleSort(std::vector<Record>& vector);
    void DrawLeaderBoard(const Game& game, const std::vector<Record>& leaderBoard, sf::RenderWindow& window);
}
