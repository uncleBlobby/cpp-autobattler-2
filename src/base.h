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

    // bottom side
    if (0 < random_number < (width)) {
        return rl::Vector2{float(width - random_number), height};
    }

    if (width < random_number < (width + height)) {
        return rl::Vector2{0, float(random_number - width)};
    }

    if ((width + height) < random_number < (2 * width + height)) {
        return rl::Vector2{float(random_number - (width + height)), 0};
    }

    if ((2 * width + height) < random_number < (2 * width + 2 * height)) {
        return rl::Vector2{
            float(width),
            float(height - (random_number - (2 * width + height)))};
    }
}

#endif