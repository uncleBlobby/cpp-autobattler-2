#include "projectile.h"

Projectile::Projectile() {};

Projectile::Projectile(rl::Vector2 startPos, rl::Vector2 dir)
    : GameObject(startPos), direction(dir) {
    speed = 150.0f;
}

void Projectile::Update(float dt) {
    direction = Vector2Normalize(direction);
    position.x += (speed * direction.x) * dt;
    position.y += (speed * direction.y) * dt;

    if (position.y < 0 || position.x < 0 || position.y > 1080 ||
        position.x > 1920) {
        isDead = true;
    }
}

void Projectile::Draw() const {
    rl::DrawCircle(position.x, position.y, 2, rl::BLACK);
}