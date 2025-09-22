#include "game.h"

Game::Game() {
    // Initialize empty entities array;
    entities = std::vector<std::unique_ptr<Entity>>{};
    // TODO:
    // FIX THE ALLOCATIONS
    entities.reserve(1000000);

    // Initialize player;
    entities.push_back(
        std::make_unique<Player>(rl::Vector2{200, 200}, rl::Vector2{0, 0}));

    Player &p = findPlayer();

    entities.push_back(std::make_unique<Enemy>(rl::Vector2{250, 250},
                                               rl::Vector2{0, 0}, p, *this));
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
}

Player &Game::findPlayer() {
    for (const auto &e : entities) {
        if (auto player = dynamic_cast<Player *>(e.get())) {
            return *player;
        }
    }
}
