#include "GameFinish.h"
#include "Game.h"
#include "SFML/Audio/Sound.hpp"

namespace
{
    bool isCollapsedWithRock(ApplesGame::Game& game)
    {
        using namespace ApplesGame;
        for (int i = 0; i < NUM_ROCKS; ++i)
        {
            if (IsRectanglesCollide(
                    game.player.position, game.player.size,
                    game.rocks[i].position, game.rocks[i].size)
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
        if (game.player.position.x - game.player.size.x / 2.f < 0 || game.player.position.x + game.
             player.size.x / 2.f > SCREEN_WIDTH ||
             game.player.position.y - game.player.size.y / 2.f < 0 || game.player.position.y + game.
             player.size.y / 2.f > SCREEN_HEIGHT)
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
            game.sounds.deathSound.play();
        }
    }
}
