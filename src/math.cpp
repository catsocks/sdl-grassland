#include "math.hpp"

// float lerp(float a, float b, float t) { return (a * (1.0 - t)) + (b * t); }

template <typename T> int sign(T val) { return (T(0) < val) - (val < T(0)); }

float move_towards(float a, float b, float max_delta) {
    if (abs(b - a) <= max_delta) {
        return b;
    }
    return a + sign(b - a) * max_delta;
}

Rect Rect::move(const Rect &r) const {
    return {x - r.x, y - r.y, width, height};
}

Rect Rect::center(const Rect &r) const {
    return {
        r.x - (width - r.width) / 2,
        r.y - (height - r.height) / 2,
        width,
        height,
    };
}

Rect Rect::clamp(const Rect &r) const {
    float new_x = x, new_y = y;
    if (width >= r.width) {
        new_x = r.x + r.width / 2 - width / 2;
    } else if (x < r.x) {
        new_x = r.x;
    } else if (x + width > r.x + r.width) {
        new_x = r.x + r.width - width;
    }

    if (height >= r.height) {
        new_y = r.y + r.height / 2 - height / 2;
    } else if (y < r.y) {
        new_y = r.y;
    } else if (y + height > r.y + r.height) {
        new_y = r.y + r.height - height;
    }

    return {new_x, new_y, width, height};
}

// Rect Rect::lerp(const Rect &r, float time) const {
//     return {
//         ::lerp(x, r.x, time),
//         ::lerp(y, r.y, time),
//         width,
//         height,
//     };
// }

Rect Rect::move_towards(const Rect &r, float max_dist_delta) const {
    return {
        ::move_towards(x, r.x, max_dist_delta),
        ::move_towards(y, r.y, max_dist_delta),
        width,
        height,
    };
}

bool Rect::fits_within(const Rect &r) const {
    return (x <= r.x) && (y <= r.y) && (x + width >= r.x + r.width) &&
           (y + height >= r.y + r.height) && (x + width > r.x) &&
           (y + height > r.y);
}

Vector2 Rect::distance(const Rect &r) const {
    return {abs(x - r.x), abs(y - r.y)};
}

// bool Rect::operator ==(const Rect &r) const {
//     return (x == r.x && y == r.y && width == r.width && height == r.height);
// }

bool Rect::operator!=(const Rect &r) const {
    return (x != r.x || y != r.y || width != r.width || height != r.height);
}

Rect::operator SDL_Rect() const {
    return {static_cast<int>(x), static_cast<int>(y), width, height};
}
