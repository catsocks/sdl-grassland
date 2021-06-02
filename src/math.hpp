#pragma once

#include <SDL.h>
#include <algorithm>
#include <functional>

constexpr double pi = 3.14159265358979323846;

template <typename T> struct Vec2D {
    T x{};
    T y{};

    inline T angle() const noexcept {
        return std::atan2(y, x);
    }

    inline T length() const noexcept {
        return std::sqrt((x * x) + (y * y));
    }

    inline T distance(const Vec2D &v) const noexcept {
        return (*this - v).length();
    }

    inline bool operator==(const Vec2D &v) const noexcept {
        return x == v.x && y == v.y;
    }

    inline bool operator!=(const Vec2D &v) const noexcept {
        return !(*this == v);
    }

    inline Vec2D operator-(const Vec2D &v) const noexcept {
        return {x - v.x, y - v.y};
    }

    inline Vec2D operator*(const Vec2D &v) const noexcept {
        return {x * v.x, y * v.y};
    }

    inline operator Vec2D<int>() const noexcept {
        return {static_cast<int>(x), static_cast<int>(y)};
    }

    inline operator Vec2D<float>() const noexcept {
        return {static_cast<float>(x), static_cast<float>(y)};
    }
};

using Vec2Di = Vec2D<int>;
using Vec2Df = Vec2D<float>;

// Specialize std::hash for Vec2Di to be used as a key in containers like
// unordered_map.
namespace std {
template <> struct hash<Vec2Di> {
    size_t operator()(const Vec2Di &id) const noexcept {
        return hash<int>()(id.x ^ (id.y << 4));
    }
};
}

float move_towards(float a, float b, float max_delta) noexcept;

template <typename T> struct Rect2D {
    T x{};
    T y{};
    T width{};
    T height{};

    inline Vec2D<T> get_position() const noexcept {
        return {x, y};
    }

    inline Vec2D<T> get_size() const noexcept {
        return {width, height};
    }

    inline Rect2D center(const Rect2D &r) const noexcept {
        return {
            r.x - ((width - r.width) / 2),
            r.y - ((height - r.height) / 2),
            width,
            height,
        };
    }

    inline Rect2D clamp(const Rect2D &r) const noexcept {
        return {
            std::clamp(x, r.x, r.width - width),
            std::clamp(y, r.y, r.height - height),
            width,
            height,
        };
    }

    inline Rect2D move_reverse(const Rect2D &r) const noexcept {
        return {x - r.x, y - r.y, width, height};
    }

    inline Rect2D move_towards(
        const Rect2D &r, float max_dist_delta) const noexcept {
        return {
            ::move_towards(x, r.x, max_dist_delta),
            ::move_towards(y, r.y, max_dist_delta),
            width,
            height,
        };
    }

    inline bool operator==(const Rect2D &r) const noexcept {
        return (x == r.x && y == r.y && width == r.width && height == r.height);
    }

    inline bool operator!=(const Rect2D &r) const noexcept {
        return !(*this == r);
    }

    // TODO: Should floats be rounded?
    inline operator SDL_Rect() const noexcept {
        return {
            static_cast<int>(x),
            static_cast<int>(y),
            static_cast<int>(width),
            static_cast<int>(height),
        };
    }
};

using Rect2Di = Rect2D<int>;
using Rect2Df = Rect2D<float>;
