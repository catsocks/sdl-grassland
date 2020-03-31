#pragma once
#include <SDL2/SDL.h>
#include <algorithm>

struct Vector2 {
    float x{}, y{};

    Vector2 operator*(const Vector2 &v) const;
};

struct Rect {
    float x{}, y{};
    int width{}, height{};

    Rect(float x, float y, int width, int height);
    Rect(const Vector2 &pos, const Vector2 &size);

    Rect move_inverse(const Rect &r) const;
    Rect center(const Rect &r) const;
    Rect clamp(const Rect &r) const;
    Rect move_towards(const Rect &r, float max_dist_delta) const;
    bool fits_within(const Rect &r) const;
    // Rect lerp(const Rect &r, float time) const;
    Vector2 distance(const Rect &r) const;

    bool operator==(const Rect &r) const;
    bool operator!=(const Rect &r) const;

    operator SDL_Rect() const;
};
