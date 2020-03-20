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

// Implement hash function so Location can be put into an unordered_set.
namespace std {
    template <> struct hash<Location> {
        std::size_t operator()(const Location &id) const noexcept {
            return std::hash<int>()(id.x ^ (id.y << 4));
        }
    };
}

struct Grid {
    static constexpr std::array<Location, 4> DIRECTIONS = {
        Location{1, 0}, Location{0, -1}, Location{-1, 0}, Location{0, 1}};

    int width{}, height{};
    std::unordered_set<Location> obstacles;

    Grid(int width, int height) : width(width), height(height) {}

    bool in_bounds(Location id) const;
    bool passable(Location id) const;
    std::vector<Location> neighbors(Location id) const;
};

void set_grid_obstacles(Grid &grid, Tilemap &tilemap);

std::unordered_map<Location, Location>
breadth_first_search(const Grid &grid, Location start, Location goal);

std::vector<Location>
reconstruct_path(Location start, Location goal,
                 std::unordered_map<Location, Location> came_from);
