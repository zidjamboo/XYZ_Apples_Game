#include "Background.h"
#include <SFML/Graphics.hpp>

#include "../Settings/Constants.h"
#include "../Math/Math.h"

namespace ApplesGame
{
    void InitBackground(Background& background, const sf::Texture& texture)
    {
        sf::Vector2u size = texture.getSize();
        background.sprite.setTexture(texture);
        unsigned int targetWidth = size.x;
        unsigned int targetHeight = size.x * 3 / 4;
        int yOffset = (size.y - targetHeight) / 2;
        background.sprite.setTextureRect(sf::IntRect(0, yOffset, targetWidth, targetHeight));
        setSpriteSize(background.sprite, {SCREEN_WIDTH, SCREEN_HEIGHT});
    }

    void DrawBackground(const Background& background, sf::RenderWindow& window)
    {
        window.draw(background.sprite);
    }
}
