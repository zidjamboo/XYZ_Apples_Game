#pragma once
#include <SFML/Audio.hpp>
#include "Player.h"
#include "Rock.h"
#include "Constants.h"

namespace ApplesGame
{
    extern bool isGameOver;
    extern float pauseTimeLeft;

    void StartPause();
    bool isNeedPause(float deltaTime);
    void CheckIfGameIsOver(Game& game);
}
