#include "Apple.h"
#include "Game.h"

namespace ApplesGame
{
    void InitApples(Apple (&apples)[NUM_APPLES], const sf::Texture& appleTexture)
    {
        for (Apple& apple : apples)
        {
            apple.size = {APPLE_SIZE, APPLE_SIZE};
            apple.sprite.setTexture(appleTexture);
            setSpriteSize(apple.sprite,apple.size);
            setSpriteRelativeOrigin(apple.sprite, CENTER, CENTER);
        }
    }

    void DrawApples(Apple (&apples)[NUM_APPLES], sf::RenderWindow& window)
    {
        for (Apple& apple : apples)
        {
            window.draw(apple.sprite);
        }
    }

    void EatPossibleApples(Game& game)
    {
        for (Apple& apple : game.apples)
        {
            if (IsRectanglesCollide(
                    game.player.position,
                    game.player.size,
                    apple.position,
                    apple.size)
            )
            {
                MoveObject(apple.sprite, apple.position);
                ++game.numEatenApples;
                game.player.speed += ACCELERATION;
            }
        }
    }
}
