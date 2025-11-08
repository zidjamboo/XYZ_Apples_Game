#pragma once
#include <SFML/Audio.hpp>
#include "../GameObjects/Player.h"
#include "../GameObjects/Rock.h"
#include "../Settings/Constants.h"

namespace ApplesGame
{
    extern bool isGameOver;
    extern bool isWin;
    extern float pauseTimeLeft;

    void StartPause();
    bool IsNeedPause(float deltaTime);
    void CheckIfGameIsOver(Game& game);
}
