#include "Background.h"

#include "Constants.h"
#include "Math.h"

namespace ApplesGame
{
    void InitBackground(Background& background, sf::Texture& texture)
    {
        background.sprite.setTexture(texture);
        setSpriteSize(background.sprite, {SCREEN_WIDTH, SCREEN_HEIGHT});
    }

    void DrawBackground(const Background& background, sf::RenderWindow& window)
    {
        window.draw(background.sprite);
    }
}
