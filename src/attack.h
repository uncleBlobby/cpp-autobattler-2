#ifndef _ATTACK_H
#define _ATTACK_H

#include "base.h"
#include "gameobject.h"
#include "projectile.h"

class TargetedProjectileAttack {
  public:
    int projectileCount;
    // int projectileBaseDamage;
    std::vector<Projectile> projectiles;
    float coolDownTime;
    float velocity; // ? already exists on projectile class -- do we need a
                    // modifier for the whole attack?
    rl::Vector2 startPosition;
    GameObject *target;
    ProjectileOwnership po;
    // rl::Color projectileColor;

    // Standard single projectile targeted attack
    TargetedProjectileAttack(GameObject *targ, rl::Vector2 startPos,
                             ProjectileOwnership po)
        : target(targ) {
        projectileCount = 1;
        velocity = 200.0f;
        startPosition = startPos;

        projectiles = std::vector<Projectile>{};

        for (int i = 0; i < projectileCount; i++) {
            projectiles.push_back(Projectile(
                startPosition,
                GetDirectionToTarget(target->GetPosition(), startPos), po));
        }
        coolDownTime = 2.0f;
    };

    TargetedProjectileAttack(GameObject *targ, rl::Vector2 startPos,
                             std::vector<rl::Vector2> targetArray,
                             ProjectileOwnership po) {
        if (target == nullptr) {
            projectileCount = targetArray.size();
            velocity = 200.0f;
            startPosition = startPos;

            projectiles = std::vector<Projectile>{};

            for (int i = 0; i < projectileCount; i++) {
                projectiles.push_back(Projectile(
                    startPosition,
                    GetDirectionToTarget(targetArray.at(i), startPos), po));
            }

            coolDownTime = 2.0f;
        }
    }

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