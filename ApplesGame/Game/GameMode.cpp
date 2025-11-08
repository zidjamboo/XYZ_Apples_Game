#include "GameMode.h"

namespace
{
    std::uint8_t gameMode = 0;
}

namespace ApplesGame
{
    void InitGameMode()
    {
        SetFlagEnabled(GameMode::INFINITE, false);
        SetFlagEnabled(GameMode::ACCELERATION, true);
        SetFlagEnabled(GameMode::HARDMODE, true);
    }

    void SetFlagEnabled(const GameMode& flag, const bool& enabled = true)
    {
        if (enabled)
        {
            gameMode |= static_cast<uint8_t>(flag);
        }
        else
        {
            gameMode &= ~static_cast<uint8_t>(flag);
        }
    }

    bool IsFlagEnabled(const GameMode& flag)
    {
        return gameMode & static_cast<int>(flag);
    }
}
