#pragma once
#include <SFML/Audio.hpp>
#include "../GameObjects/Player.h"
#include "../GameObjects/Rock.h"
#include "../Settings/Constants.h"

namespace ApplesGame
{
    extern bool isGameOver;
    extern float pauseTimeLeft;

    void StartPause();
    bool isNeedPause(float deltaTime);
    void CheckIfGameIsOver(Game& game);
}
