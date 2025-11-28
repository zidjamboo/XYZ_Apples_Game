#pragma once

namespace sf
{
    class Sprite;
}

namespace ApplesGame
{
    struct Vector2D
    {
        float x = 0;
        float y = 0;
    };

    typedef Vector2D Position2D;
    typedef Vector2D Size2D;

    bool IsRectanglesCollide(
        Position2D rect1Position,
        Size2D rect1Size,
        Position2D rect2Position,
        Size2D rect2Size
    );

    int GetRandomInt(const int& min, const int& max);
    float GetRandomFloat(const float& min, const float& max);
    Position2D GetRandomPositionInScreen(const int& screenWidth, const int& screenHeight);

    void setSpriteSize(sf::Sprite& sprite, const Size2D& size);
    void setSpriteRelativeOrigin(sf::Sprite& sprite, const float& originX, const float& originY);
}
