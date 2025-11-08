#pragma once
#include <cstdint>

namespace ApplesGame
{
    enum class GameMode : std::uint8_t
    {
        INFINITE = 1 << 0,
        ACCELERATION = 1 << 1,
        HARDMODE = 1 << 2
    };

    void InitGameMode();
    void SetFlagEnabled(const GameMode& flag, const bool& enabled);
    bool IsFlagEnabled(const GameMode& flag);
}
