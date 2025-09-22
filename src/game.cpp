#include "game.h"

Game::Game() {

    srand(time(0));

    // Initialize empty entities array;
    entities = std::vector<std::unique_ptr<Entity>>{};
    // TODO:
    // FIX THE ALLOCATIONS
    entities.reserve(1000000);

    // Initialize player;
    entities.push_back(
        std::make_unique<Player>(rl::Vector2{200, 200}, rl::Vector2{0, 0}));

    // Player &p = findPlayer();
    player = &findPlayer();

    entities.push_back(std::make_unique<Enemy>(
        rl::Vector2{250, 250}, rl::Vector2{0, 0}, *player, *this));
};

void Game::Update(float dt) {

    // std::cout << "game.entities.size(): " << entities.size() << std::endl;
    std::cout << "capacity=" << entities.capacity()
              << " size=" << entities.size() << std::endl;

    for (auto &e : entities) {
        if (auto player = dynamic_cast<Player *>(e.get())) {
            player->Update(dt);
        }
        if (auto enemy = dynamic_cast<Enemy *>(e.get())) {
            enemy->Update(dt);
        }
        if (auto proj = dynamic_cast<Projectile *>(e.get())) {
            proj->Update(dt);
        }
        // e->Update(dt);
    }

    entities.erase(std::remove_if(entities.begin(), entities.end(),
                                  [](auto &e) { return e->isDead; }),
                   entities.end());

    timeSinceLastEnemySpawn += dt;
    if (timeSinceLastEnemySpawn >= enemySpawnCooldown) {
        SpawnEnemy();
        timeSinceLastEnemySpawn = 0.0f;
    }
}

void Game::Draw() const {
    for (const auto &e : entities) {
        if (auto player = dynamic_cast<Player *>(e.get())) {
            player->Draw();
        }
        if (auto enemy = dynamic_cast<Enemy *>(e.get())) {
            enemy->Draw();
        }
        if (auto proj = dynamic_cast<Projectile *>(e.get())) {
            proj->Draw();
        }
        // e->Draw();
    }

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

Player &Game::findPlayer() {
    for (const auto &e : entities) {
        if (auto player = dynamic_cast<Player *>(e.get())) {
            return *player;
        }
    }
}
