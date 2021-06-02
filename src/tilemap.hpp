#pragma once

#include <filesystem>
#include <fstream>
#include <optional>
#include <sstream>
#include <unordered_map>

#include "math.hpp"
#include "tileset.hpp"
#include "util.hpp"

// TODO: Support multiple layers.
struct Tilemap {
    Vec2Di size;
    std::unordered_map<Vec2Di, int> map;
};

using Tilemaps = std::unordered_map<std::string, Tilemap>;

Tilemap load_tilemap(const std::filesystem::path &path);
Tilemaps load_tilemaps(const std::filesystem::path &folder);

struct TilemapRender {
    std::unique_ptr<SDL_Surface, SDL_SurfaceDeleter> surface;
    std::unique_ptr<SDL_Texture, SDL_TextureDeleter> texture;

    TilemapRender() = default;
    TilemapRender(
        SDL_Renderer *renderer, const Tilemap &tilemap, const Tileset &tileset);

    void render(SDL_Renderer *renderer, const Rect2Df &source) const;
};
