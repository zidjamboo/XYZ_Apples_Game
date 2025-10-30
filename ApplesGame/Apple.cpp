#include "Apple.h"
#include "Game.h"

namespace ApplesGame
{
    void InitApples(Apple (&apples)[20])
    {
        for (int i = 0; i < NUM_APPLES; ++i)
        {
            Apple& apple = apples[i];
            apple.appleSize.diameter = APPLE_SIZE;
            sf::CircleShape& appleShape = apple.appleShape;
            appleShape.setRadius(apple.appleSize.diameter / 2.f);
            appleShape.setFillColor(sf::Color::Green);
            appleShape.setOrigin(apple.appleSize.diameter / 2.f, apple.appleSize.diameter / 2.f);
        }
    }

    void DrawApples(Game& game, sf::RenderWindow& window)
    {
        for (int i = 0; i < NUM_APPLES; ++i)
        {
            window.draw(game.apples[i].appleShape);
        }
    }

    void EatPossibleApples(Game& game)
    {
        for (int i = 0; i < NUM_APPLES; ++i)
        {
            if (isCirclesCollide(
                    game.player.playerPosition,
                    {game.player.playerSize.x},
                    game.apples[i].applePosition,
                    game.apples[i].appleSize)
            )
            {
                MoveObject(game.apples[i].appleShape, game.apples[i].applePosition);
                ++game.numEatenApples;
                game.player.playerSpeed += ACCELERATION;
            }
        }
    }
}
