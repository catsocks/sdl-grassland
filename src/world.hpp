#pragma once

#include <SDL.h>
#include <vector>

#include "grid.hpp"
#include "math.hpp"

// TODO: Can this forward declaration be avoided without a circular dependency?
class Sprite;

struct World {
    Rect rect;
    Grid *grid{};
    std::vector<Sprite *> sprites;

    World(const Vector2 &size);
};
