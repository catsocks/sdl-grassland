#pragma once

#include <SDL.h>
#include <filesystem>
#include <fstream>
#include <map>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

#include "math.hpp"
#include "tileset.hpp"

namespace fs = std::filesystem;

class Tilemap {
public:
    int width{}, height{};
    std::vector<std::optional<int>> tiles;

    std::optional<int> at(int x, int y);
};

Tilemap load_tilemap(const fs::path &filepath);
std::map<std::string, Tilemap> load_tilemaps(const fs::path &folder);

struct TilemapRender {
    SDL_Surface *surface;
    SDL_Texture *texture;

    TilemapRender();

    void draw(SDL_Renderer *renderer, const Rect &camera);
};

TilemapRender render_tilemap(SDL_Renderer *renderer, Tilemap &tm, Tileset &ts);
