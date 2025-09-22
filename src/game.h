#ifndef _GAME_H
#define _GAME_H

#include "base.h"
#include "enemy.h"
#include "entity.h"
#include "player.h"
#include "projectile.h"
#include <memory>

class Game {
  public:
    std::vector<std::unique_ptr<Entity>> entities;

    Game();

    void Update(float dt);
    void Draw() const;

    Player &findPlayer();

    friend class Enemy;
};

#endif