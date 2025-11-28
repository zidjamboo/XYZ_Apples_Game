#include "LeaderBoard.h"

#include <SFML/Graphics/Text.hpp>
#include "../Game/Game.h"

constexpr size_t SCORE_ROW_LENGTH = 20;
constexpr int BOT_SCORE_MIN = 0;
constexpr int BOT_SCORE_MAX = 100;

namespace
{
    std::shared_ptr<std::vector<ApplesGame::Record>> leaderboardPtr;

    void BubbleSort(std::vector<ApplesGame::Record>& vector)
    {
        for (size_t i = 0; i < vector.size(); i++)
        {
            for (size_t j = i + 1; j < vector.size(); j++)
            {
                if (vector[i].score < vector[j].score)
                {
                    std::swap(vector[i], vector[j]);
                }
            }
        }
    }

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
    std::shared_ptr<std::unordered_map<std::string, int>> GenerateLeaderBoardMap()
    {
        const auto map = std::make_shared<std::unordered_map<std::string, int>>();
        map->insert({"Alice", GetRandomInt(BOT_SCORE_MIN, BOT_SCORE_MAX)});
        map->insert({"Bob", GetRandomInt(BOT_SCORE_MIN, BOT_SCORE_MAX)});
        map->insert({"Carol", GetRandomInt(BOT_SCORE_MIN, BOT_SCORE_MAX)});
        map->insert({"Dave", GetRandomInt(BOT_SCORE_MIN, BOT_SCORE_MAX)});

        return map;
    }

    void UpdateLeaderboard(const Game& game)
    {
        std::unordered_map<std::string, int>& leaderboardMap = *game.leaderboardMap;
        leaderboardMap["Player"] = std::max(game.finalScore, leaderboardMap["Player"]);

        std::vector<Record> leaderboard;
        leaderboard.reserve(leaderboardMap.size());
        for (const auto& pair: leaderboardMap)
        {
            leaderboard.push_back({pair.first, pair.second});
        }
        BubbleSort(leaderboard);
        leaderboardPtr = std::make_shared<std::vector<Record>>(leaderboard);
    }

    void DrawLeaderboard(const Game& game, sf::RenderWindow& window)
    {
        float i = 1;
        std::vector<Record>& lb = *leaderboardPtr;
        for (const Record& record : *leaderboardPtr)
        {
            std::shared_ptr<sf::Text> text = InitScoreRow(game, record);
            text->setPosition(30.f, 30 * i);
            window.draw(*text);
            i++;
        }
    }
}
