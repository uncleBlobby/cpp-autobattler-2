#ifndef _GAME_H
#define _GAME_H

#include "base.h"
#include "entity.h"
#include <memory>

class Game {
  public:
    std::vector<std::unique_ptr<Entity>> entities;

    Game();

    void Update(float dt);
    void Draw() const;
};

#endif