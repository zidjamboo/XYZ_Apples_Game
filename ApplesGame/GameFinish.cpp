#include "GameFinish.h"
#include "Game.h"

namespace
{
    bool isCollapsedWithRock(ApplesGame::Game& game)
    {
        using namespace ApplesGame;
        for (int i = 0; i < NUM_ROCKS; ++i)
        {
            if (IsRectanglesCollide(
                    game.player.playerPosition, game.player.playerSize,
                    game.rocks[i].rockPosition, game.rocks[i].rocksSize)
            )
            {
                return true;
            }
        }

        return false;
    }

    bool isCollapsedWithBorder(ApplesGame::Game& game)
    {
        using namespace ApplesGame;
        if (game.player.playerPosition.x - game.player.playerSize.x / 2.f < 0 || game.player.playerPosition.x + game.
             player.playerSize.x / 2.f > SCREEN_WIDTH ||
             game.player.playerPosition.y - game.player.playerSize.y / 2.f < 0 || game.player.playerPosition.y + game.
             player.playerSize.y / 2.f > SCREEN_HEIGHT)
        {
            return true;
        }

        return false;
    }
}

namespace ApplesGame
{
    void StartPause(Game& game)
    {
        game.pauseTimeLeft = INITIAL_PAUSE_TIME;
        game.isGameOver = false;
    }

    bool isNeedPause(Game& game, float deltaTime)
    {
        if (game.pauseTimeLeft > 0.f)
        {
            game.pauseTimeLeft -= deltaTime;
            return true;
        }

        return false;
    }

    void CheckIfGameIsOver(Game& game)
    {
        if (isCollapsedWithRock(game) || isCollapsedWithBorder(game))
        {
            game.isGameOver = true;
        }
    }
}
