#include "math.hpp"

float move_towards(float a, float b, float max_delta) noexcept {
    if (std::abs(b - a) <= max_delta) {
        return b;
    }
    return a + std::copysign(max_delta, b - a);
}
