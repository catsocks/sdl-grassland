#include "grid.hpp"

Grid::Grid(const Vec2Di &size, const Vec2Di &tile_size)
    : size(size)
    , tile_size(tile_size) {
    directions = std::array{Vec2Di{tile_size.x, 0}, Vec2Di{-tile_size.x, 0},
        Vec2Di{0, -tile_size.y}, Vec2Di{0, tile_size.y}};
}

std::vector<Vec2Di> Grid::find_path(
    const Vec2Di &start, const Vec2Di &goal) const {
    auto came_from = breadth_first_search(start, goal);

    std::vector<Vec2Di> path;
    Vec2Di current = goal;
    while (current != start && came_from.find(current) != came_from.end()) {
        path.push_back(current);
        current = came_from[current];
    }

    return path;
}

bool Grid::passable(const Vec2Di &position) const {
    return static_obstacles.find(position) == static_obstacles.end()
        && movable_obstacles.find(position) == movable_obstacles.end();
}

bool Grid::in_bounds(const Vec2Di &position) const noexcept {
    return 0 <= position.x && position.x < size.x && 0 <= position.y
        && position.y < size.y;
}

std::vector<Vec2Di> Grid::passable_neighbors(const Vec2Di &position) const {
    std::vector<Vec2Di> neighbors;

    for (auto d : directions) {
        Vec2Di next{position.x + d.x, position.y + d.y};
        if (in_bounds(next) && passable(next)) {
            neighbors.push_back(next);
        }
    }

    // For straighter paths.
    if ((position.x + position.y) % 2 == 0) {
        std::reverse(neighbors.begin(), neighbors.end());
    }

    return neighbors;
}

std::unordered_map<Vec2Di, Vec2Di> Grid::breadth_first_search(
    const Vec2Di &start, const Vec2Di &goal) const {
    std::queue<Vec2Di> frontier;
    frontier.push(start);

    std::unordered_map<Vec2Di, Vec2Di> came_from;
    came_from[start] = start;

    while (!frontier.empty()) {
        auto current = frontier.front();
        frontier.pop();

        if (current == goal) {
            break;
        }

        for (auto next : passable_neighbors(current)) {
            if (came_from.find(next) == came_from.end()) {
                frontier.push(next);
                came_from[next] = current;
            }
        }
    }

    return came_from;
}
