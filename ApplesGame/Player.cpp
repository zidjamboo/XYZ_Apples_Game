#include "Player.h"
#include "Math.h"
#include "Constants.h"
#include "Game.h"

namespace ApplesGame
{
    void InitPlayer(Player& player, const sf::Texture& playerTexture)
    {
        player.position = {SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f};
        player.size = {PLAYER_SIZE, PLAYER_SIZE};
        player.direction = PlayerDirection::Right;

        player.sprite.setTexture(playerTexture);
        setSpriteSize(player.sprite, player.size);
        setSpriteRelativeOrigin(player.sprite, CENTER, CENTER);
    }

    void DrawPlayer(Player& player, sf::RenderWindow& window)
    {
        player.sprite.setPosition(player.position.x, player.position.y);
        window.draw(player.sprite);
    }
}
