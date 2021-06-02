#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <filesystem>
#include <map>
#include <string>
#include <vector>

namespace fs = std::filesystem;

class Tileset {
    int cols{};

public:
    int tile_width{}, tile_height{};
    SDL_Surface *image{};

    Tileset(int tile_width, int tile_height);

    void set_image(SDL_Surface *surface);

    SDL_Rect at(int index);
};

Tileset load_tileset(const fs::path &path, int tile_width, int tile_height);
std::map<std::string, Tileset> load_tilesets(
    const fs::path &folder, int tile_width, int tile_height);
