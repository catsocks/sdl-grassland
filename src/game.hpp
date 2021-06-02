#pragma once

#include <SDL.h>
#include <stdexcept>

#include "input.hpp"
#include "math.hpp"
#include "tilemap.hpp"
#include "tileset.hpp"
#include "util.hpp"
#include "world.hpp"

class Game {
    Vec2Di tile_size{32, 32};
    Vec2Di renderer_size;
    std::unique_ptr<SDL_Window, SDL_WindowDeleter> window;
    std::unique_ptr<SDL_Renderer, SDL_RendererDeleter> renderer;
    Tilemaps tilemaps;
    Tilesets tilesets;
    World world;
    Input input;
    double time{};
    uint64_t counter_time{};

public:
    bool should_quit{};

    Game(const std::string &window_title);

    void update();
};
