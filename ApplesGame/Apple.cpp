#include "Apple.h"
#include <SFML/Audio.hpp>
#include "Game.h"

namespace ApplesGame
{
    void InitApples(ApplesArray& apples, const sf::Texture& appleTexture)
    {
        apples.arr = new Apple[20];
        apples.size = 20;

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
            window.draw(apple.sprite);
        }
    }
}
