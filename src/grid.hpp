#pragma once

#include <array>
#include <queue>
#include <unordered_map>
#include <unordered_set>

#include "math.hpp"
#include "tilemap.hpp"

class Grid {
    Vec2Di size;
    Vec2Di tile_size;
    std::array<Vec2Di, 4> directions;

public:
    std::unordered_set<Vec2Di> static_obstacles;
    std::unordered_set<Vec2Di> movable_obstacles;

    Grid() = default;
    Grid(const Vec2Di &size, const Vec2Di &tile_size);

    std::vector<Vec2Di> find_path(
        const Vec2Di &start, const Vec2Di &goal) const;

    bool passable(const Vec2Di &position) const;
    bool in_bounds(const Vec2Di &position) const noexcept;
    std::vector<Vec2Di> passable_neighbors(const Vec2Di &position) const;

private:
    std::unordered_map<Vec2Di, Vec2Di> breadth_first_search(
        const Vec2Di &start, const Vec2Di &goal) const;
};
