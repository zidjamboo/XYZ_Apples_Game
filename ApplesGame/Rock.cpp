#include "Rock.h"

void InitRocks(Rock(& rocks)[3])
{
    for (int i = 0; i < NUM_ROCKS; ++i)
    {
        Rock& rock = rocks[i];
        rock.rocksSize = {ROCK_SIZE, ROCK_SIZE};
        sf::RectangleShape& rockShape = rock.rockShape;
        rockShape.setSize(sf::Vector2f(rock.rocksSize.x, rock.rocksSize.y));
        rockShape.setFillColor(sf::Color::Cyan);
        rockShape.setOrigin(rock.rocksSize.x / 2.f, rock.rocksSize.y / 2.f);
    }
}
