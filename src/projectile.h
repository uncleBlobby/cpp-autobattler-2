#ifndef _PROJECTILE_H
#define _PROJECTILE_H

#include "gameobject.h"

class Projectile : public GameObject {
  protected:
    rl::Vector2 targetPosition;
    rl::Vector2 direction;
    float speed;

  public:
    Projectile();
    Projectile(rl::Vector2 startPos, rl::Vector2 dir);

    void Update(float dt) override;

    void Draw() const override;
};

#endif
