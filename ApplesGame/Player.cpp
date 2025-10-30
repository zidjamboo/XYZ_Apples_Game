#include "Player.h"
#include "Math.h"
#include "Constants.h"
#include "Game.h"

namespace ApplesGame
{
    void InitPlayer(Player& player, const Game& game)
    {
        player.playerPosition = {SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f};
        player.playerSize = {PLAYER_SIZE, PLAYER_SIZE};
        player.playerDirection = PlayerDirection::Right;

        player.playerSprite.setTexture(game.playerTexture);
        setSpriteSize(player.playerSprite, PLAYER_SIZE, PLAYER_SIZE);
        setSpriteRelativeOrigin(player.playerSprite, 0.5f, 0.5f);
    }

    void DrawPlayer(Player& player, sf::RenderWindow& window)
    {
        player.playerSprite.setPosition(player.playerPosition.x, player.playerPosition.y);
        window.draw(player.playerSprite);
    }
}
