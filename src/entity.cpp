#include "entity.hpp"

Entity::Entity(const Vec2Di &position, const Tileset &tileset)
    : sprite(tileset) {
    rect.x = position.x;
    rect.y = position.y;
    rect.width = tileset.tile_size.x;
    rect.height = tileset.tile_size.y;
    target_rect = rect;
    grid_position = rect.get_position();
}

void Entity::look(Direction direction) {
    if (rect == target_rect) {
        switch (direction) {
        case Direction::up:
            sprite.set_tile(Sprite::Tile::front, 1);
            break;
        case Direction::left:
            sprite.set_tile(Sprite::Tile::left, 1);
            break;
        case Direction::right:
            sprite.set_tile(Sprite::Tile::right, 1);
            break;
        case Direction::down:
            sprite.set_tile(Sprite::Tile::back, 1);
            break;
        }
    }
}

bool Entity::move(const Grid &grid, Direction direction) {
    if (rect != target_rect) {
        return false;
    }
    Rect2Df dest = target_rect;
    Sprite::Tile tile{};
    switch (direction) {
    case Direction::up:
        dest.y += target_rect.height;
        tile = Sprite::Tile::front;
        break;
    case Direction::left:
        dest.x -= target_rect.width;
        tile = Sprite::Tile::left;
        break;
    case Direction::right:
        dest.x += target_rect.width;
        tile = Sprite::Tile::right;
        break;
    case Direction::down:
        dest.y -= target_rect.height;
        tile = Sprite::Tile::back;
        break;
    }
    Vec2Di dest_position = dest.get_position();
    if (grid.passable(dest_position) && grid.in_bounds(dest_position)) {
        target_rect = dest;
        sprite.rotate_tile(tile);
        return true;
    }
    look(direction);
    return false;
}

void Entity::follow(const Grid &grid, const Entity &target) {
    auto too_close = grid_position.distance(target.grid_position)
        <= rect.get_size().length();
    if (too_close) {
        look(direction_from_angle(target.grid_position - grid_position));
        return;
    }

    if (!sees(target)) {
        return;
    }

    if (follow_path_goal != target.grid_position) {
        auto neighbors = grid.passable_neighbors(target.grid_position);
        if (neighbors.empty()) {
            return;
        }

        std::sort(neighbors.begin(), neighbors.end(),
            [this](const Vec2Di &v1, const Vec2Di &v2) {
                return v1.distance(grid_position) < v2.distance(grid_position);
            });

        follow_path_goal = target.grid_position;
        follow_path = grid.find_path(grid_position, neighbors.front());
    }

    if (follow_path.empty()) {
        return;
    }

    auto direction = direction_from_angle(follow_path.back() - grid_position);
    if (move(grid, direction)) {
        follow_path.pop_back();
    }
}

void Entity::update(double dt) {
    grid_position = target_rect.get_position();

    rect = rect.move_towards(target_rect, dt * 150);
}

void Entity::render(SDL_Renderer *renderer, const Rect2Df &camera) {
    sprite.render(renderer, rect.move_reverse(camera));
}

bool Entity::sees(const Entity &target) const {
    float sight_distance = 4 * rect.get_size().length();
    return rect.get_position().distance(target.rect.get_position())
        <= sight_distance;
}

Entity::Direction Entity::direction_from_angle(Vec2Df v) {
    float angle = v.angle();
    int quadrant
        = static_cast<int>(std::round((4 * (angle / (2 * pi))) + 4)) % 4;
    std::array directions{
        Direction::right, Direction::up, Direction::left, Direction::down};
    return directions.at(quadrant);
}
