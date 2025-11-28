#include "Apple.h"
#include <SFML/Audio.hpp>
#include "../Game/Game.h"
#include "../Game/GameMode.h"

namespace ApplesGame
{
    void InitApples(ApplesArray& apples, const sf::Texture& appleTexture)
    {
        bool test = IsFlagEnabled(GameMode::HARD_MODE);
        int applesArraySize = GetRandomInt(NUM_APPLES_MIN, NUM_APPLES_MAX);
        if ((IsFlagEnabled(GameMode::INFINITE) && !IsFlagEnabled(GameMode::HARD_MODE)) ||
            (!IsFlagEnabled(GameMode::INFINITE) && IsFlagEnabled(GameMode::HARD_MODE)))
        {
            applesArraySize = NUM_APPLES_MAX;
        }
        apples.arr = new Apple[applesArraySize];
        apples.size = applesArraySize;

        for (int i = 0; i < apples.size; ++i)
        {
            Apple& apple = apples.arr[i];
            apple.size = {APPLE_SIZE, APPLE_SIZE};
            apple.sprite.setTexture(appleTexture);
            setSpriteSize(apple.sprite,apple.size);
            setSpriteRelativeOrigin(apple.sprite, CENTER, CENTER);
        }
    }

    void DrawApples(const ApplesArray& apples, sf::RenderWindow& window)
    {
        for (int i = 0; i < apples.size; ++i)
        {
            Apple& apple = apples.arr[i];
            if (!apple.isEaten)
            {
                window.draw(apple.sprite);
            }
        }
    }
}
