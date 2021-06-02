#pragma once

#include "grid.hpp"
#include "input.hpp"
#include "math.hpp"
#include "sprite.hpp"
#include "tileset.hpp"

class Entity {
    Sprite sprite;
    Rect2Df target_rect;
    std::vector<Vec2Di> follow_path;
    Vec2Di follow_path_goal;

public:
    enum class Direction { up, left, right, down };

    Rect2Df rect;
    Vec2Di grid_position;

    Entity(const Vec2Di &position, const Tileset &tileset);

    void look(Direction direction);
    bool move(const Grid &grid, Direction direction);
    void follow(const Grid &grid, const Entity &target);
    void update(double dt);
    void render(SDL_Renderer *renderer, const Rect2Df &camera);

private:
    bool sees(const Entity &target) const;
    static Direction direction_from_angle(Vec2Df v);
};
