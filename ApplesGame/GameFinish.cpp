#include "Game/GameFinish.h"
#include "Game/Game.h"
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
    bool isGameOver = false;
    float pauseTimeLeft = 0.f;

    void StartPause()
    {
        pauseTimeLeft = INITIAL_PAUSE_TIME;
        isGameOver = false;
    }

    bool isNeedPause(float deltaTime)
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
        if (isCollapsedWithRock(game.player, game.rocks) || isCollapsedWithBorder(game.player))
        {
            isGameOver = true;
            game.finalScore = game.numEatenApples;
            game.sounds.deathSound.play();
        }
    }
}
