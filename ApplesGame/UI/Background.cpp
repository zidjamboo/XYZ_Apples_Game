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
        int targetWidth = static_cast<int>(size.x);
        int targetHeight = static_cast<int>(static_cast<float>(size.x) / SCREEN_FORMAT);
        int yOffset = static_cast<int>(size.y - targetHeight) / 2;
        background.sprite.setTextureRect(sf::IntRect(0, yOffset, targetWidth, targetHeight));
        setSpriteSize(background.sprite, {SCREEN_WIDTH, SCREEN_HEIGHT});
    }

    void DrawBackground(const Background& background, sf::RenderWindow& window)
    {
        window.draw(background.sprite);
    }
}
