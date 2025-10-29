#include "Player.h"
#include "Math.h"
#include "Constants.h"

namespace ApplesGame
{
    void InitPlayer(Player& player)
    {
        player.playerPosition = {SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f};
        player.playerSize = {PLAYER_SIZE, PLAYER_SIZE};
        player.playerDirection = PlayerDirection::Right;

        player.playerShape.setSize(sf::Vector2f(player.playerSize.x, player.playerSize.y));
        player.playerShape.setFillColor(sf::Color::Red);
        player.playerShape.setOrigin(player.playerSize.x / 2.f, player.playerSize.y / 2.f);
    }
}
