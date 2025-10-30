#include "Rock.h"
#include "Game.h"

namespace ApplesGame
{
    void InitRocks(Rock (&rocks)[NUM_ROCKS], sf::Texture& rockTexture)
    {
        for (Rock& rock : rocks)
        {
            rock.size = {ROCK_SIZE, ROCK_SIZE};
            rock.sprite.setTexture(rockTexture);
            setSpriteSize(rock.sprite, rock.size);
            setSpriteRelativeOrigin(rock.sprite, CENTER, CENTER);
        }
    }

    void DrawRocks(Rock (&rocks)[NUM_ROCKS], sf::RenderWindow& window)
    {
        for (Rock& rock : rocks)
        {
            window.draw(rock.sprite);
        }
    }
}
