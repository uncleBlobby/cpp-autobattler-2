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
    Player *player;

    float enemySpawnCooldown = 1.0f;
    float timeSinceLastEnemySpawn = 0.0f;

    Game();

    void Update(float dt);
    void Draw() const;

    Player &findPlayer();

    void SpawnEnemy();

    friend class Enemy;
};

#endif