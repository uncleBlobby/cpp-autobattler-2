#include "game.h"

Game::Game() {

    srand(time(0));

    // Initialize empty entities array;
    entities = std::vector<std::unique_ptr<Entity>>{};
    floatingTexts = std::vector<FloatingText>{};
    // TODO:
    // FIX THE ALLOCATIONS
    entities.reserve(1000000);

    // Initialize player;

    // Player &p = findPlayer();
    // player = &findPlayer();

    // entities.push_back(std::make_unique<Enemy>(
    //     rl::Vector2{250, 250}, rl::Vector2{0, 0}, *player, *this));
};

void Game::InitPlayer() {
    entities.push_back(std::make_unique<Player>(rl::Vector2{200, 200},
                                                rl::Vector2{0, 0}, *this));

    player = &findPlayer();
}

void Game::Update(float dt) {

    std::vector<Enemy *> activeEnemies = std::vector<Enemy *>{};

    for (auto &e : entities) {
        if (auto enemy = dynamic_cast<Enemy *>(e.get())) {
            activeEnemies.push_back(enemy);
            //     enemy->Update(dt);
        }
    }

    for (auto &e : entities) {
        // if (auto player = dynamic_cast<Player *>(e.get())) {
        //     player->Update(dt);
        // }
        // if (auto enemy = dynamic_cast<Enemy *>(e.get())) {
        //     enemy->Update(dt);
        // }

        e->Update(dt);

        if (auto proj = dynamic_cast<Projectile *>(e.get())) {
            // proj->Update(dt);
            if (proj->owner == ProjectileOwnership::ENEMY) {
                if (rl::CheckCollisionCircleRec(proj->GetPosition(),
                                                proj->GetRadius(),
                                                player->GetCollider())) {
                    proj->isDead = true;

                    floatingTexts.push_back(
                        CreateFloatingText(player->GetPosition(), 10));
                }
            }

            if (proj->owner == ProjectileOwnership::PLAYER) {

                for (auto enemy : activeEnemies) {
                    if (rl::CheckCollisionCircleRec(proj->GetPosition(),
                                                    proj->GetRadius(),
                                                    enemy->GetCollider())) {
                        // std::cout << "hit enemy" << std::endl;
                        proj->isDead = true;

                        floatingTexts.push_back(
                            CreateFloatingText(enemy->GetPosition(), 10));
                        enemy->TakeDamage(10);

                        if (enemy->GetRemainingHP() <= 0) {
                            enemy->isDead = true;
                        }
                    }
                }
                //     // loop through all enemies and check collisions
                //     if (rl::CheckCollisionCircleRec(proj->GetPosition(),
                //                                     proj->GetRadius(),
                //                                     player->GetCollider())) {
                //         proj->isDead = true;
                //     }
            }
        }
    }

    for (auto &ft : floatingTexts) {
        ft.lifetime -= dt;
        // ft.position.y += ft.velocityY * dt;
        // ft.alpha = std::max(0.0f, ft.lifetime);
        if (ft.lifetime < 0)
            ft.lifetime = 0;
        float t = 1.0f - (ft.lifetime / ft.totalLifetime);
        t = std::clamp(t, 0.0f, 1.0f);
        float ease = EaseOutQuad(t);
        rl::Vector2 origin = ft.basePosition;
        rl::Vector2 offset = {ft.velocity.x * ease, ft.velocity.y * ease};
        rl::Vector2 currentPos = Vector2Add(origin, offset);
        float fontSize = LERP(ft.startSize, ft.endSize, ease);
        rl::Color c = ft.color;
        c.a = (unsigned char)(255 * (ft.lifetime / ft.totalLifetime));
        rl::DrawText(ft.text.c_str(), (int)currentPos.x, (int)currentPos.y,
                     (int)fontSize, c);
    }

    entities.erase(std::remove_if(entities.begin(), entities.end(),
                                  [](auto &e) { return e->isDead; }),
                   entities.end());

    floatingTexts.erase(
        std::remove_if(floatingTexts.begin(), floatingTexts.end(),
                       [](const FloatingText &ft) { return ft.lifetime <= 0; }),
        floatingTexts.end());

    timeSinceLastEnemySpawn += dt;
    if (timeSinceLastEnemySpawn >= enemySpawnCooldown) {
        SpawnEnemy();
        timeSinceLastEnemySpawn = 0.0f;
    }
}

void Game::Draw() const {
    for (const auto &e : entities) {
        // if (auto player = dynamic_cast<Player *>(e.get())) {
        //     player->Draw();
        // }
        // if (auto enemy = dynamic_cast<Enemy *>(e.get())) {
        //     enemy->Draw();
        // }
        // if (auto proj = dynamic_cast<Projectile *>(e.get())) {
        //     proj->Draw();
        // }
        e->Draw();
    }

    // for (const auto &ft : floatingTexts) {

    //     rl::DrawText(ft.text.c_str(), (int)currentPos.x, (int)currentPos.y,
    //                  (int)fontSize, c);
    // }

    rl::DrawText(std::format("FPS:\t\t\t{}", rl::GetFPS()).c_str(), 5, 5, 16,
                 rl::BLACK);
    rl::DrawText(std::format("ENTITIES:\t{}", entities.size()).c_str(), 5,
                 5 + 16, 16, rl::BLACK);
    rl::DrawText(std::format("PLAYER_POS:\t{},{}", player->GetPosition().x,
                             player->GetPosition().y)
                     .c_str(),
                 5, 5 + 32, 16, rl::BLACK);
}

void Game::SpawnEnemy() {
    rl::Vector2 randomSpawnPoint = PositionJustOutsideScreen();
    entities.push_back(std::make_unique<Enemy>(

        randomSpawnPoint, rl::Vector2{0, 0}, *player, *this));
}

std::vector<Enemy *> Game::GetEnemies() {
    std::vector<Enemy *> enemies;
    for (auto &e : entities) {
        if (auto enemy = dynamic_cast<Enemy *>(e.get())) {
            enemies.push_back(enemy);
        }
    }

    return enemies;
}

Player &Game::findPlayer() {
    for (const auto &e : entities) {
        if (auto player = dynamic_cast<Player *>(e.get())) {
            return *player;
        }
    }
}
