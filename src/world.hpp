#pragma once

#include <SDL.h>
#include <string>
#include <unordered_map>

#include "entity.hpp"
#include "grid.hpp"
#include "tilemap.hpp"
#include "tileset.hpp"

class World {
    Vec2Di tile_size;
    TilemapRender background;
    TilemapRender foreground;
    Vec2Di size;
    Rect2Df camera;
    std::unordered_map<std::string, Entity> entities;
    Grid grid;

public:
    World() = default;
    World(SDL_Renderer *renderer, const Vec2Di &tile_size,
        const Vec2Di &renderer_size, const Tilemaps &tilemaps,
        const Tilesets &tilesets);

    void update(const Input &input, double dt);
    void render(SDL_Renderer *renderer);

private:
    void update_grid();
    void handle_player_input(const Input &input, Entity &entity);
};
