#include "Math.h"

#include <cmath>
#include <cstdlib>
#include <SFML/Graphics.hpp>

namespace ApplesGame
{
    bool IsRectanglesCollide(
        Position2D rect1Position, Size2D rect1Size, Position2D rect2Position, Size2D rect2Size)
    {
        float dx = std::fabs(rect1Position.x - rect2Position.x);
        float dy = std::fabs(rect1Position.y - rect2Position.y);

        return dx <= (rect1Size.x + rect2Size.x) / 2 && dy <= (rect1Size.y + rect2Size.y) / 2;
    }

    float GetRandomFloat(const float& min, const float& max)
    {
        return min + static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * max;
    }

    Position2D GetRandomPositionInScreen(const int& screenWidth, const int& screenHeight)
    {
        Position2D result;

        result.x = GetRandomFloat(0, static_cast<float>(screenWidth));
        result.y = GetRandomFloat(0, static_cast<float>(screenHeight));

        return result;
    }

    void setSpriteSize(sf::Sprite& sprite, const Size2D& size)
    {
        sf::FloatRect localBounds = sprite.getLocalBounds();
        sf::Vector2f scale = { size.x / localBounds.width , size.y / localBounds.height};
        sprite.setScale(scale);
    }

    void setSpriteRelativeOrigin(sf::Sprite& sprite, const float& originX, const float& originY)
    {
        sf::FloatRect localBounds = sprite.getLocalBounds();
        sprite.setOrigin(localBounds.width * originX, localBounds.height * originY);
    }
}
