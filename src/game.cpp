#include "game.h"
#include "player.h"

Game::Game() {
    entities = std::vector<std::unique_ptr<Entity>>{};
    // Player p = Player(rl::Vector2{200, 200}, rl::Vector2{0, 0});

    entities.push_back(
        std::make_unique<Player>(rl::Vector2{200, 200}, rl::Vector2{0, 0}));
};

void Game::Update(float dt) {
    for (auto &e : entities) {
        e->Update(dt);
    }
}

void Game::Draw() const {
    for (const auto &e : entities) {
        e->Draw();
    }
}
