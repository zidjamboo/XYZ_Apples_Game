#include "Math.h"
#include <cstdlib>

namespace ApplesGame
{
    bool IsRectanglesCollide(
        Position2D rect1Position, Size2D rect1Size, Position2D rect2Position, Size2D rect2Size)
    {
        float dx = (float)fabs(rect1Position.x - rect2Position.x);
        float dy = (float)fabs(rect1Position.y - rect2Position.y);

        return dx <= (rect1Size.x + rect2Size.x) / 2 && dy <= (rect1Size.y + rect2Size.y) / 2;
    }

    bool isCirclesCollide(
        Position2D circle1Position, CircleSize circle1Size, Position2D circle2Position, CircleSize circle2Size)
    {
        float dx = circle1Position.x - circle2Position.x;
        float dy = circle1Position.y - circle2Position.y;
        float squareDistance = dx * dx + dy *dy;

        float diameterSum = circle1Size.diameter + circle2Size.diameter;
        float squareRadiusSum = diameterSum * diameterSum / 4;

        return squareDistance <= squareRadiusSum;
    }

    float GetRandomFloat(const float& min, const float& max)
    {
        return min + rand() / (float)RAND_MAX * max;
    }

    Position2D GetRandomPositionInScreen(const int& screenWidth, const int& screenHeight)
    {
        Position2D result;

        result.x = GetRandomFloat(0, (float)screenWidth);
        result.y = GetRandomFloat(0, (float)screenHeight);

        return result;
    }

}
