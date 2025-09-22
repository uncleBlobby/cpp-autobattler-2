#ifndef _ENEMY_H
#define _ENEMY_H

#include "actor.h"
#include "base.h"

class Enemy : public Actor {

  protected:
    float shootCooldown = 2.0f;
    float timeSinceLastShot = 0.0f;

  public:
    Enemy(rl::Vector2 pos, rl::Vector2 dir) : Actor(pos, dir) {};

    void Update(float dt) override {};

    void Draw() const override;

    void Shoot() {};

    // rl::Vector2 GetDirectionToPlayer();
};

#endif