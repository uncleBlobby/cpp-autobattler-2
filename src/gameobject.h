#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H

#include "base.h"
#include "entity.h"

class GameObject : public Entity {
  protected:
    rl::Vector2 position;
    // rl::Texture2D texture;

  public:
    GameObject() {};
    GameObject(rl::Vector2 pos) : position(pos) {};

    rl::Vector2 GetPosition() { return position; }

    void Update(float dt) override {}

    void Draw() const override {}
};

#endif