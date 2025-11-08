#include "Apple.h"
#include <SFML/Audio.hpp>
#include "../Game/Game.h"
#include "../Game/GameMode.h"

namespace ApplesGame
{
    void InitApples(ApplesArray& apples, const sf::Texture& appleTexture)
    {
        int applesArraySize = 20;
        if ((IsFlagEnabled(GameMode::INFINITE) && !IsFlagEnabled(GameMode::HARDMODE)) ||
            (!IsFlagEnabled(GameMode::INFINITE) && IsFlagEnabled(GameMode::HARDMODE)))
        {
            applesArraySize = 50;
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
