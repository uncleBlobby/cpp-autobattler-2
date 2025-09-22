#ifndef _ACTOR_H
#define _ACTOR_H

#include "base.h"
#include "gameobject.h"

class Actor : public GameObject {
  protected:
    rl::Vector2 direction;
    float speed;
    int hitpoints;

  public:
    Actor() {};
    Actor(rl::Vector2 pos, rl::Vector2 dir)
        : GameObject(pos), direction(dir) {};

    void Update(float dt) override {};

    void Draw() const override {};

    rl::Vector2 GetPosition() { return position; }
};

#endif