#pragma once

namespace ApplesGame
{
    struct Game;
    void StartPause(Game& game);
    bool isNeedPause(Game& game, float deltaTime);
    void CheckIfGameIsOver(Game& game);
}
