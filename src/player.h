#ifndef _PLAYER_H
#define _PLAYER_H

#include "actor.h"
#include "base.h"
#include "game.h"

class Player : public Actor {
  protected:
    float shootCooldown = 2.0f;
    float timeSinceLastShot = 0.0f;
    Game &game;

  public:
    rl::Vector2 center =
        rl::Vector2{position.x + (size / 2), position.y + (size / 2)};
    int size = 25;
    Player(Game &g);

    Player(rl::Vector2 pos, rl::Vector2 dir, Game &g);

    void Update(float dt) override;

    void Shoot();

    void Draw() const override;
};

#endif