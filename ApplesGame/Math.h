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

    struct CircleSize
    {
        float diameter = 0.f;
    };

    typedef Vector2D Position2D;
    typedef Vector2D Size2D;

    bool IsRectanglesCollide(
        Position2D rect1Position,
        Size2D rect1Size,
        Position2D rect2Position,
        Size2D rect2Size
    );

    bool isCirclesCollide(
        Position2D circle1Position,
        CircleSize circle1Size,
        Position2D circle2Position,
        CircleSize circle2Size
    );

    float GetRandomFloat(const float& min, const float& max);
    Position2D GetRandomPositionInScreen(const int& screenWidth, const int& screenHeight);

    void setSpriteSize(sf::Sprite& sprite, const float& desiredWidth, const float& desiredHeight);
    void setSpriteRelativeOrigin(sf::Sprite& sprite, const float& originX, const float& originY);
}
