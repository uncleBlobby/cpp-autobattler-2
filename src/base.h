#ifndef _BASE_H
#define _BASE_H

#include <cmath>
#include <cstdlib>
#include <ctime>
#include <format>
#include <iostream>
#include <vector>

namespace rl {
extern "C" {
#include <raylib.h>
}
} // namespace rl

inline rl::Vector2 Vector2Sub(rl::Vector2 v1, rl::Vector2 v2) {
    rl::Vector2 result = rl::Vector2{v1.x - v2.x, v1.y - v2.y};
    return result;
}

inline rl::Vector2 Vector2Add(rl::Vector2 v1, rl::Vector2 v2) {
    return rl::Vector2{v1.x + v2.x, v1.y + v2.y};
}

inline rl::Vector2 Vector2LERP(rl::Vector2 v1, rl::Vector2 v2, float amount) {
    rl::Vector2 result = rl::Vector2{0, 0};
    result.x = v1.x + amount * (v2.x - v1.x);
    result.y = v1.y + amount * (v2.y - v1.y);

    return result;
}

inline float LERP(float f1, float f2, float amount) {
    float result = f1 + amount * (f2 - f1);
    return result;
}

inline rl::Vector2 Vector2Normalize(rl::Vector2 input) {
    float mag = sqrt(pow(input.x, 2) + pow(input.y, 2));
    rl::Vector2 norm = rl::Vector2{input.x / mag, input.y / mag};
    return norm;
}

inline rl::Vector2 PositionJustOutsideScreen() {
    const int width = 1920;
    const int height = 1080;
    int perim = 2 * (width + height);

    int random_number = 0 + (rand() % (perim - 0 + 1));

    if (random_number > 0 && random_number < width) {
        return rl::Vector2{float(width - random_number), height};
    }

    if (random_number > width && random_number < (width + height)) {
        return rl::Vector2{0, float(random_number - width)};
    }

    if (random_number > (width + height) &&
        random_number < (2 * width + height)) {
        return rl::Vector2{float(random_number - (width + height)), 0};
    }

    if (random_number > (2 * width + height) &&
        random_number < (2 * width + 2 * height)) {
        return rl::Vector2{
            float(width),
            float(height - (random_number - (2 * width + height)))};
    }
}

struct FloatingText {
    rl::Vector2 basePosition;
    std::string text;
    float lifetime;
    float totalLifetime;
    float startSize;
    float endSize;
    // float alpha;
    rl::Vector2 velocity;
    rl::Color color;
    const rl::Vector2 *ownerPos = nullptr;
};

inline FloatingText CreateFloatingText(rl::Vector2 startPos, int damage) {
    FloatingText ft;
    // ft.position = rl::Vector2{startPos.x, startPos.y - 25};
    ft.basePosition = rl::Vector2{startPos.x, startPos.y - 25};
    ft.text = std::to_string(damage);
    ft.lifetime = ft.totalLifetime = 1.0f;
    ft.startSize = 40.0f;
    ft.endSize = 10.0f;
    // ft.alpha = 1.0f;
    ft.color = rl::BLACK;
    ft.velocity = rl::Vector2{0, -40};
    return ft;
}

inline FloatingText CreateFloatingEXPText(rl::Vector2 startPos, int expAmount) {
    FloatingText ft;
    // ft.position = rl::Vector2{startPos.x, startPos.y - 25};
    ft.basePosition = rl::Vector2{startPos.x, startPos.y - 25};
    ft.text = "+";
    ft.text += std::to_string(expAmount);
    ft.text += "EXP";
    ft.lifetime = ft.totalLifetime = 1.0f;
    ft.startSize = 40.0f;
    ft.endSize = 10.0f;
    // ft.alpha = 1.0f;
    ft.color = rl::GREEN;
    ft.velocity = rl::Vector2{0, -40};
    return ft;
}

inline float EaseOutQuad(float t) { return 1 - (1 - t) * (1 - t); }

struct Loot {
    rl::Vector2 position;
    float radius;
    int xpValue;
    bool collected = false;
    rl::Color color = rl::GREEN;
};

inline Loot CreateLootExpItem(rl::Vector2 spawnPos) {
    Loot gem;
    gem.position = spawnPos;
    gem.radius = 8.0f;
    gem.xpValue = 10;
    return gem;
}

#endif