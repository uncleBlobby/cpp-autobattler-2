#ifndef _PROJECTILE_H
#define _PROJECTILE_H

#include "gameobject.h"

enum ProjectileOwnership { PLAYER, ENEMY };

class Projectile : public GameObject {
  protected:
    rl::Vector2 targetPosition;
    rl::Vector2 direction;
    float speed;
    float radius;

  public:
    ProjectileOwnership owner;
    Projectile();
    Projectile(rl::Vector2 startPos, rl::Vector2 dir, ProjectileOwnership po);

    void Update(float dt) override;

    void Draw() const override;

    float GetRadius() const;
};

#endif
