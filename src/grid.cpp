#include "grid.hpp"

bool operator==(Location a, Location b) { return a.x == b.x && a.y == b.y; }

bool operator!=(Location a, Location b) { return !(a == b); }

bool operator<(Location a, Location b) {
    return std::tie(a.x, a.y) < std::tie(b.x, b.y);
}

bool Grid::in_bounds(Location id) const {
    return 0 <= id.x && id.x < width && 0 <= id.y && id.y < height;
}

bool Grid::passable(Location id) const {
    return obstacles.find(id) == obstacles.end();
}

std::vector<Location> Grid::neighbors(Location id) const {
    std::vector<Location> results;

    for (Location dir : DIRECTIONS) {
        Location next{id.x + dir.x, id.y + dir.y};
        if (in_bounds(next) && passable(next)) {
            results.push_back(next);
        }
    }

    if ((id.x + id.y) % 2 == 0) {
        // aesthetic improvement on square grids
        std::reverse(results.begin(), results.end());
    }

    return results;
}

void set_grid_obstacles(Grid &grid, Tilemap &tilemap) {
    for (int x = 0; x < tilemap.width; x++) {
        for (int y = 0; y < tilemap.height; y++) {
            auto tile = tilemap.at(x, y);
            if (tile.has_value()) {
                grid.obstacles.insert(Location{x, y});
            }
        }
    }
}

std::unordered_map<Location, Location>
breadth_first_search(const Grid &grid, Location start, Location goal) {
    std::queue<Location> frontier;
    frontier.push(start);

    std::unordered_map<Location, Location> came_from;
    came_from[start] = start;

    while (!frontier.empty()) {
        Location current = frontier.front();
        frontier.pop();

        if (current == goal) {
            break;
        }

        for (Location next : grid.neighbors(current)) {
            if (came_from.find(next) == came_from.end()) {
                frontier.push(next);
                came_from[next] = current;
            }
        }
    }
    return came_from;
}

std::vector<Location>
reconstruct_path(Location start, Location goal,
                 std::unordered_map<Location, Location> came_from) {
    std::vector<Location> path;
    Location current = goal;
    while (current != start) {
        path.push_back(current);
        current = came_from[current];
    }
    std::reverse(path.begin(), path.end());
    return path;
}
