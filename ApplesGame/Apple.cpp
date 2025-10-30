#include "Apple.h"
#include "Game.h"

namespace ApplesGame
{
    void InitApples(Apple (&apples)[20])
    {
        for (Apple& apple : apples)
        {
            apple.appleSize.diameter = APPLE_SIZE;
            sf::CircleShape& appleShape = apple.appleShape;
            appleShape.setRadius(apple.appleSize.diameter / 2.f);
            appleShape.setFillColor(sf::Color::Green);
            appleShape.setOrigin(apple.appleSize.diameter / 2.f, apple.appleSize.diameter / 2.f);
        }
    }

    void DrawApples(Apple (&apples)[NUM_APPLES], sf::RenderWindow& window)
    {
        for (Apple& apple : apples)
        {
            window.draw(apple.appleShape);
        }
    }

    void EatPossibleApples(Game& game)
    {
        for (Apple& apple : game.apples)
        {
            if (isCirclesCollide(
                    game.player.playerPosition,
                    {game.player.playerSize.x},
                    apple.applePosition,
                    apple.appleSize)
            )
            {
                MoveObject(apple.appleShape, apple.applePosition);
                ++game.numEatenApples;
                game.player.playerSpeed += ACCELERATION;
            }
        }
    }
}
