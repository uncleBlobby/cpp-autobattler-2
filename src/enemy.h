#ifndef _ENEMY_H
#define _ENEMY_H

#include "actor.h"
#include "base.h"

class Game;
class Player;

class Enemy : public Actor {

  protected:
    float shootCooldown = 2.0f;
    float timeSinceLastShot = 0.0f;
    Game &game;
    Player &player;

  public:
    rl::Vector2 center =
        rl::Vector2{position.x + (size / 2), position.y + (size / 2)};
    int size = 25;
    Enemy(rl::Vector2 pos, rl::Vector2 dir, Player &p, Game &g);

    void Update(float dt) override;

    void Draw() const override;

    void Shoot();

    rl::Vector2 GetDirectionToPlayer();

    void SetPlayerRef(Player &p);

    // Player *findPlayer(Game &game);
};

#endif