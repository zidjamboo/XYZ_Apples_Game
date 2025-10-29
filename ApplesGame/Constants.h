#pragma once
#include <string>

namespace ApplesGame
{
    const std::string RESOURCES_PATH = "Resources/";
    constexpr int SCREEN_WIDTH = 800;
    constexpr int SCREEN_HEIGHT = 600;

    constexpr float INITIAL_SPEED = 100.f;
    constexpr float ACCELERATION = 20.f;

    constexpr float PLAYER_SIZE = 20.f;

    constexpr int NUM_APPLES = 20;
    constexpr float APPLE_SIZE = 20.f;

    constexpr int NUM_ROCKS = 3;
    constexpr float ROCK_SIZE = 40.f;

    constexpr float INITIAL_PAUSE_TIME = 3.f;
}
