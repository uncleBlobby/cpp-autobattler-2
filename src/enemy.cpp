#include "enemy.h"
#include "game.h"
#include "player.h"
#include "projectile.h"

// Enemy::Enemy() {};

Enemy::Enemy(rl::Vector2 pos, rl::Vector2 dir, Player &p, Game &g)
    : Actor(pos, dir), player(p), game(g) {
    speed = 95.0f;
    hitpoints = 50;
    collider = rl::Rectangle{pos.x, pos.y, size * 1.0f, size * 1.0f};
};

void Enemy::Update(float dt) {

    center = rl::Vector2{position.x + (size / 2), position.y + (size / 2)};
    collider = rl::Rectangle{position.x, position.y, size * 1.0f, size * 1.0f};

    // move toward player
    direction = GetDirectionToPlayer();
    direction = Vector2Normalize(direction);

    position.x += (speed * direction.x) * dt;
    position.y += (speed * direction.y) * dt;

    // std::cout << "enemy position: " << position.x << ":" << position.y
    //           << std::endl;

    timeSinceLastShot += dt;
    if (timeSinceLastShot >= shootCooldown) {
        Shoot();
        timeSinceLastShot = 0.0f;
    }
};

void Enemy::Draw() const {
    rl::DrawRectangle(position.x, position.y, size, size, rl::RED);
};

void Enemy::Shoot() {
    game.entities.push_back(std::make_unique<Projectile>(
        center, GetDirectionToPlayer(), ProjectileOwnership::ENEMY));
};

rl::Vector2 Enemy::GetDirectionToPlayer() {
    rl::Vector2 dir = Vector2Sub(player.GetPosition(), position);
    return dir;
};

// void Enemy::SetPlayerRef(Player &p) { player = p; }

// Player *Enemy::findPlayer(Game &game) {
//     for (const auto &e : game.entities) {
//         if (auto player = dynamic_cast<Player *>(e.get())) {
//             return player;
//         }
//     }
// };