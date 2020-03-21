// TODO: Location should be part of Grid.
// TODO: Location operator functions should be part of itself.
#pragma once
#include "math.hpp"
#include "tilemap.hpp"
#include <algorithm>
#include <array>
#include <cstdlib>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

struct Location {
    int x{}, y{};
};

bool operator==(Location a, Location b);
bool operator!=(Location a, Location b);
bool operator<(Location a, Location b);

Location make_location(const Rect &r);

// Implement hash function so Location can be put into an unordered_set.
namespace std {
    template <> struct hash<Location> {
        size_t operator()(const Location &id) const noexcept {
            return hash<int>()(id.x ^ (id.y << 4));
        }
    };
}

struct Grid {
    int width{}, height{};
    std::unordered_set<Location> obstacles;

    Grid(const Tilemap &base) : width(base.width), height(base.height) {}

    bool in_bounds(Location id) const;
    bool passable(Location id) const;
    std::vector<Location> neighbors(Location id) const;

    void set_obstacles(Tilemap &tilemap);
    Vector2 get_size() const;
};

std::unordered_map<Location, Location>
breadth_first_search(const Grid &grid, Location start, Location goal);

std::vector<Location>
reconstruct_path(Location start, Location goal,
                 std::unordered_map<Location, Location> came_from);
