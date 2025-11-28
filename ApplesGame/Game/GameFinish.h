#pragma once
#include "../GameObjects/Player.h"

namespace ApplesGame
{
    extern bool isGameOver;
    extern bool isWin;
    extern float pauseTimeLeft;

    void StartPause();
    bool IsNeedPause(float deltaTime);
    void CheckIfGameIsOver(Game& game);
}
