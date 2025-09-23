#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H

#include "base.h"
#include "entity.h"

class GameObject : public Entity {
  protected:
    
    // rl::Texture2D texture;

  public:
    rl::Vector2 position;
    GameObject() {};
    GameObject(rl::Vector2 pos) : position(pos) {};

    rl::Vector2 GetPosition() { return position; }

    void Update(float dt) override {}

    void Draw() const override {}
};

#endif