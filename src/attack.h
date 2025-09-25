#ifndef _ATTACK_H
#define _ATTACK_H

#include "base.h"
#include "gameobject.h"
#include "projectile.h"

class ProjectileAttack {
  public:
    int projectileCount;
    int projectileBaseDamage;
    int projectileRadius;

    // replace below with array of Projectile class...

    std::vector<Projectile> projectiles;

    // std::vector<rl::Vector2> projectileDirections;
    // std::vector<rl::Vector2> projectilePositions;
    float coolDownTime;
    float velocity;
    rl::Vector2 startPosition;
    GameObject &target;
    ProjectileOwnership po;
    // rl::Color projectileColor;

    // Standard single projectile targeted attack
    ProjectileAttack(GameObject &targ, rl::Vector2 startPos,
                     ProjectileOwnership po)
        : target(targ) {
        projectileCount = 1;
        projectileBaseDamage = 5;
        projectileRadius = 5;
        velocity = 200.0f;
        startPosition = startPos;

        projectiles = std::vector<Projectile>{};

        for (size_t i = 0; i < projectileCount; i++) {
            projectiles.push_back(Projectile(
                startPosition,
                GetDirectionToTarget(target.GetPosition(), startPos), po));
        }

        // projectileDirections = std::vector<rl::Vector2>{};
        coolDownTime = 2.0f;
        // projectileDirections.push_back(
        //     GetDirectionToTarget(target.GetPosition(), startPos));
        // projectilePositions.push_back(startPos);
        // projectileColor = rl::BLACK;
    };

    void Update(float dt) {

        // // normalized directions

        // std::vector<rl::Vector2> normDirs = {};

        // for (size_t i = 0; i < projectileCount; i++) {
        //     normDirs.push_back(Vector2Normalize(projectileDirections[i]));

        //     projectilePositions[i].x += (velocity * normDirs[i].x) * dt;
        //     projectilePositions[i].y += (velocity * normDirs[i].y) * dt;
        // }

        for (size_t i = 0; i < projectiles.size(); i++) {
            projectiles[i].Update(dt);
        }
    };
    void Draw() const {

        // for (size_t i = 0; i < projectileCount; i++) {
        //     rl::DrawCircleV(projectilePositions[i], projectileRadius,
        //                     projectileColor);
        // }

        for (size_t i = 0; i < projectiles.size(); i++) {
            projectiles[i].Draw();
        }
    };
};

#endif