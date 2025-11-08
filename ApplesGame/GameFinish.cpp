#include "Game/GameFinish.h"
#include "Game/Game.h"
#include "Game/GameMode.h"
#include "SFML/Audio/Sound.hpp"

namespace
{
    using namespace ApplesGame;

    bool isCollapsedWithRock(const Player& player, const Rock (&rocks)[NUM_ROCKS])
    {
        for (const Rock& rock : rocks)
        {
            if (IsRectanglesCollide(
                    player.position, player.size,
                    rock.position, rock.size)
            )
            {
                return true;
            }
        }

        return false;
    }

    bool isCollapsedWithBorder(const Player& player)
    {
        if (player.position.x - player.size.x / 2.f < 0 || player.position.x +
             player.size.x / 2.f > SCREEN_WIDTH ||
             player.position.y - player.size.y / 2.f < 0 || player.position.y +
             player.size.y / 2.f > SCREEN_HEIGHT)
        {
            return true;
        }

        return false;
    }
}

namespace ApplesGame
{
    bool isGameOver = true;
    bool isWin = false;
    float pauseTimeLeft = 0.f;

    void StartPause()
    {
        pauseTimeLeft = INITIAL_PAUSE_TIME;
    }

    bool IsNeedPause(float deltaTime)
    {
        if (pauseTimeLeft > 0.f)
        {
            pauseTimeLeft -= deltaTime;
            return true;
        }

        return false;
    }

    void CheckIfGameIsOver(Game& game)
    {
        if (!IsFlagEnabled(GameMode::INFINITE) && game.apples.size == game.numEatenApples)
        {
            isWin = true;
            isGameOver = true;
            isNeedSetupGame = true;
            game.finalScore = game.numEatenApples;

            StartPause();

            return;
        }

        if (isCollapsedWithRock(game.player, game.rocks) || isCollapsedWithBorder(game.player))
        {
            isWin = false;
            isGameOver = true;
            isNeedSetupGame = true;
            game.finalScore = game.numEatenApples;
            game.sounds.deathSound.play();

            StartPause();
        }
    }
}
