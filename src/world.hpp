// TODO: Can the usage of raw pointers be avoided?
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

    World(int width, int height) : rect({0, 0, width, height}) {}
};
