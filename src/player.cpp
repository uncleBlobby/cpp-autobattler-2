#include "player.h"
#include "attack.h"

Player::Player(Game &g) : game(g) {};

Player::Player(rl::Vector2 pos, rl::Vector2 dir, Game &g)
    : Actor(pos, dir), game(g) {
    hitpoints = 100;
    collider = rl::Rectangle{pos.x, pos.y, size * 1.0f, size * 1.0f};
};

void Player::Update(float dt) {

    center = rl::Vector2{position.x + (size / 2), position.y + (size / 2)};
    collider = rl::Rectangle{position.x, position.y, size * 1.0f, size * 1.0f};

    direction = rl::Vector2{0, 0};
    if (rl::IsKeyDown(rl::KEY_A))
        direction.x = -1;
    if (rl::IsKeyDown(rl::KEY_D))
        direction.x = +1;
    if (rl::IsKeyDown(rl::KEY_W))
        direction.y = -1;
    if (rl::IsKeyDown(rl::KEY_S))
        direction.y = +1;

    if (rl::IsKeyDown(rl::KEY_LEFT_SHIFT)) {
        speed = 300.0f;
    } else {
        speed = 100.0f;
    }

    position.x += (speed * direction.x) * dt;
    position.y += (speed * direction.y) * dt;

    timeSinceLastShot += dt;
    if (timeSinceLastShot >= shootCooldown) {
        Shoot();
        timeSinceLastShot = 0.0f;
    }
};

void Player::Draw() const {
    rl::DrawRectangle(position.x, position.y, size, size, rl::BLUE);
};

void Player::Shoot() {

    std::vector<rl::Vector2> targets = {};
    targets.push_back(rl::Vector2{-1, 0});
    targets.push_back(rl::Vector2{1, 0});
    targets.push_back(rl::Vector2{0, -1});
    targets.push_back(rl::Vector2{0, 1});

    TargetedProjectileAttack tpa = TargetedProjectileAttack(
        nullptr, position, targets, ProjectileOwnership::PLAYER);

    for (int i = 0; i < tpa.projectileCount; i++) {
        game.entities.push_back(
            std::make_unique<Projectile>(tpa.projectiles[i]));
    }

    // game.entities.push_back(std::make_unique<Projectile>(
    //     center, rl::Vector2{-1, 0}, ProjectileOwnership::PLAYER));
    // game.entities.push_back(std::make_unique<Projectile>(
    //     center, rl::Vector2{1, 0}, ProjectileOwnership::PLAYER));
    // game.entities.push_back(std::make_unique<Projectile>(
    //     center, rl::Vector2{0, -1}, ProjectileOwnership::PLAYER));
    // game.entities.push_back(std::make_unique<Projectile>(
    //     center, rl::Vector2{0, 1}, ProjectileOwnership::PLAYER));
};