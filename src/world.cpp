#include "world.hpp"

World::World(SDL_Renderer *renderer, const Vec2Di &tile_size,
    const Vec2Di &renderer_size, const Tilemaps &tilemaps,
    const Tilesets &tilesets)
    : tile_size(tile_size) {
    background = TilemapRender(
        renderer, tilemaps.at("World_Background"), tilesets.at("misc"));
    foreground = TilemapRender(
        renderer, tilemaps.at("World_Foreground"), tilesets.at("misc"));

    size = tilemaps.at("World_Background").size * tile_size;

    camera = Rect2Df{0, 0, static_cast<float>(renderer_size.x),
        static_cast<float>(renderer_size.y)};

    entities.insert({
        "girl",
        Entity(Vec2Di{16, 16} * tile_size, tilesets.at("girl")),
    });
    entities.insert({
        "boy",
        Entity(Vec2Di{17, 2} * tile_size, tilesets.at("boy")),
    });

    grid = Grid(size, tile_size);

    for (const auto &[key, val] : tilemaps.at("World_Obstacles").map) {
        grid.static_obstacles.insert(key * tile_size);
    }
}

void World::update(const Input &input, double dt) {
    update_grid();

    Entity &girl = entities.at("girl");
    handle_player_input(input, girl);

    Entity &boy = entities.at("boy");
    boy.follow(grid, girl);

    girl.update(dt);
    boy.update(dt);

    camera = camera.center(girl.rect);
    camera = camera.clamp(
        Rect2Df{0, 0, static_cast<float>(size.x), static_cast<float>(size.y)});
}

void World::render(SDL_Renderer *renderer) {
    background.render(renderer, camera);
    foreground.render(renderer, camera);

    entities.at("boy").render(renderer, camera);
    entities.at("girl").render(renderer, camera);
}

void World::update_grid() {
    grid.movable_obstacles.clear();

    for (auto &[key, val] : entities) {
        grid.movable_obstacles.insert(val.grid_position);
    }
}

void World::handle_player_input(const Input &input, Entity &entity) {
    if (input.is_down(Button::look_up)) {
        entity.look(Entity::Direction::down);
    } else if (input.is_down(Button::look_left)) {
        entity.look(Entity::Direction::left);
    } else if (input.is_down(Button::look_right)) {
        entity.look(Entity::Direction::right);
    } else if (input.is_down(Button::look_down)) {
        entity.look(Entity::Direction::up);
    }

    if (input.is_down(Button::move_up)) {
        entity.move(grid, Entity::Direction::down);
    } else if (input.is_down(Button::move_left)) {
        entity.move(grid, Entity::Direction::left);
    } else if (input.is_down(Button::move_right)) {
        entity.move(grid, Entity::Direction::right);
    } else if (input.is_down(Button::move_down)) {
        entity.move(grid, Entity::Direction::up);
    }
}
