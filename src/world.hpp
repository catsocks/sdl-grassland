#pragma once
#include "grid.hpp"
#include "math.hpp"
#include <SDL2/SDL.h>
#include <vector>

// TODO: Can this forward declaration be avoided without a circular dependency?
class Sprite;

struct World {
    Rect rect;
    Grid *grid{};
    std::vector<Sprite *> sprites;

    World(const Vector2 &size);
};
