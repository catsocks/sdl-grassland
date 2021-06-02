#pragma once

#include <SDL.h>
#include <algorithm>

struct Vec2D {
    float x{}, y{};

    Vec2D operator*(const Vec2D &v) const;
};

struct Rect2D {
    float x{};
    float y{};
    float width{};
    float height{};

    Rect2D(float x, float y, float width, float height);
    Rect2D(const Vec2D &pos, const Vec2D &size);

    Rect2D move_inverse(const Rect2D &r) const;
    Rect2D center(const Rect2D &r) const;
    Rect2D clamp(const Rect2D &r) const;
    Rect2D move_towards(const Rect2D &r, float max_dist_delta) const;
    bool fits_within(const Rect2D &r) const;
    // Rect lerp(const Rect &r, float time) const;
    Vec2D distance(const Rect2D &r) const;

    bool operator==(const Rect2D &r) const;
    bool operator!=(const Rect2D &r) const;

    operator SDL_Rect() const;
};
