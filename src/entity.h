#ifndef _ENTITY_H
#define _ENTITY_H

class Entity {
  public:
    bool isDead;
    virtual ~Entity() = default;
    virtual void Update(float dt) = 0;
    virtual void Draw() const = 0;
};

#endif