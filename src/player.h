#ifndef _PLAYER_H
#define _PLAYER_H

#include "actor.h"
#include "base.h"

class Player : public Actor {
  protected:
    float shootCooldown = 2.0f;
    float timeSinceLastShot = 0.0f;

  public:
    Player();

    Player(rl::Vector2 pos, rl::Vector2 dir);

    void Update(float dt) override;

    void Shoot() {};

    void Draw() const override;
};

#endif