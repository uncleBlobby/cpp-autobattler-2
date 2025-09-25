#ifndef _ACTOR_H
#define _ACTOR_H

#include "base.h"
#include "gameobject.h"

class Actor : public GameObject {
  protected:
    rl::Vector2 direction;
    float speed;
    int hitpoints;
    rl::Rectangle collider;

  public:
    // float timeSinceHit;
    Actor() {};
    Actor(rl::Vector2 pos, rl::Vector2 dir)
        : GameObject(pos), direction(dir) {};

    void Update(__attribute__((unused)) float dt) override {};

    void Draw() const override {};

    rl::Vector2 GetPosition() { return position; }

    const rl::Vector2 &GetPositionRef() const { return position; }

    rl::Rectangle GetCollider() { return collider; }

    void TakeDamage(int amount) { hitpoints -= amount; }

    int GetRemainingHP() { return hitpoints; }
};

#endif