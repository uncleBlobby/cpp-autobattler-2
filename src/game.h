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
    std::vector<FloatingText> floatingTexts;
    std::vector<Loot> lootDrops;

    // std::vector<Enemy *> activeEnemiesThisFrame;

    Player *player;

    float enemySpawnCooldown = 1.0f;
    float timeSinceLastEnemySpawn = 0.0f;

    Game();

    void Update(float dt);
    void Draw() const;

    void InitPlayer();

    Player &findPlayer();

    void SpawnEnemy();

    std::vector<Enemy *> GetEnemies();

    friend class Enemy;
};

#endif