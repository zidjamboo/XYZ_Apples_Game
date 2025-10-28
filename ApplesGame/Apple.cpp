#include "Apple.h"

void InitApples(Apple(& apples)[20])
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
