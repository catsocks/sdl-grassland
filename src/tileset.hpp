#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <filesystem>
#include <map>
#include <string>
#include <vector>

#include "math.hpp"
#include "util.hpp"

class Tileset {
    int columns{};

public:
    std::shared_ptr<SDL_Surface> surface;
    std::shared_ptr<SDL_Texture> texture;
    Vec2Di tile_size;

    Tileset(SDL_Renderer *renderer, SDL_Surface *surface, Vec2Di tile_size);

    Rect2Di at(int idx) const;
};

using Tilesets = std::unordered_map<std::string, Tileset>;

Tileset load_tileset(SDL_Renderer *renderer, const std::filesystem::path &path,
    Vec2Di tile_size);
Tilesets load_tilesets(SDL_Renderer *renderer,
    const std::filesystem::path &folder, Vec2Di tile_size);
