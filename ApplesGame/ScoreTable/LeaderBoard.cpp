#include "LeaderBoard.h"

#include <SFML/Graphics/Text.hpp>
#include "../Game/Game.h"

constexpr size_t SCORE_ROW_LENGTH = 20;

namespace
{
    std::shared_ptr<sf::Text> InitScoreRow(const ApplesGame::Game& game, const ApplesGame::Record& record)
    {
        std::shared_ptr<sf::Text> text = std::make_shared<sf::Text>();
        text->setFont(game.fonts.robotoBold);
        text->setCharacterSize(24);
        text->setFillColor(sf::Color::Yellow);

        const std::string& name = record.name;
        const std::string score = std::to_string(record.score);
        const size_t dotsCount = SCORE_ROW_LENGTH - name.length() - score.length();
        std::string dots = std::string(dotsCount, '.');

        text->setString(name + dots + score);

        return text;
    }
}

namespace ApplesGame
{
    void BubbleSort(std::vector<Record> vector)
    {
        for (size_t i = 0; i < vector.size(); i++)
        {
            for (size_t j = i + 1; j < vector.size(); j++)
            {
                if (vector[i].score > vector[j].score)
                {
                    Record& tmp = vector[i];
                    vector[i] = vector[j];
                    vector[j] = tmp;
                }
            }
        }
    }

    void DrawLeaderBoard(const Game& game, const std::vector<Record>& leaderBoard, sf::RenderWindow& window)
    {
        float i = 1;
        for (const Record& record : leaderBoard)
        {
            std::shared_ptr<sf::Text> text = InitScoreRow(game, record);
            text->setPosition(30.f, 30 * i);
            window.draw(*text);
            i++;
        }
    }
}
