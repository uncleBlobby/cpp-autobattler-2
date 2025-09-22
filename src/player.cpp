#include "player.h"

Player::Player() {};

Player::Player(rl::Vector2 pos, rl::Vector2 dir) : Actor(pos, dir) {};

void Player::Update(float dt) {
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
    rl::DrawRectangle(position.x, position.y, 10, 10, rl::BLUE);
};