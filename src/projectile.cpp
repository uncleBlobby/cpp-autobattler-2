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
}

void Projectile::Draw() const {
    rl::DrawCircle(position.x, position.y, 2, rl::BLACK);
}