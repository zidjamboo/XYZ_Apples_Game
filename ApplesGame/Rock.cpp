#include "Rock.h"
#include "Game.h"

namespace ApplesGame
{
    void InitRocks(Rock (&rocks)[3])
    {
        for (Rock& rock : rocks)
        {
            rock.rocksSize = {ROCK_SIZE, ROCK_SIZE};
            sf::RectangleShape& rockShape = rock.rockShape;
            rockShape.setSize(sf::Vector2f(rock.rocksSize.x, rock.rocksSize.y));
            rockShape.setFillColor(sf::Color::Cyan);
            rockShape.setOrigin(rock.rocksSize.x / 2.f, rock.rocksSize.y / 2.f);
        }
    }

    void DrawRocks(Rock (&rocks)[NUM_ROCKS], sf::RenderWindow& window)
    {
        for (Rock& rock : rocks)
        {
            window.draw(rock.rockShape);
        }
    }
}
