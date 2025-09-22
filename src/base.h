#ifndef _BASE_H
#define _BASE_H

#include <cmath>
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

#endif