#include "tilemap.hpp"

Tilemap load_tilemap(const std::filesystem::path &path) {
    Tilemap tilemap;
    std::ifstream file(path);
    std::string row;
    while (std::getline(file, row)) {
        std::stringstream ss(row);
        std::string column;
        int columns = 0;
        while (std::getline(ss, column, ',')) {
            int tile = std::stoi(column);
            if (tile != -1) {
                tilemap.map.insert({{columns, tilemap.size.y}, tile});
            }
            columns += 1;
        }
        if (tilemap.size.x == 0) {
            tilemap.size.x = columns;
        } else if (tilemap.size.x != columns) {
            throw std::runtime_error(
                "Couldn't load a tilemap with rows of unequal length");
        }
        tilemap.size.y += 1;
    }
    return tilemap;
}

Tilemaps load_tilemaps(const std::filesystem::path &folder) {
    Tilemaps tilemaps;
    for (auto &entry : std::filesystem::directory_iterator(folder)) {
        if (entry.is_directory() || entry.path().extension() != ".csv") {
            continue;
        }

        tilemaps.insert({entry.path().stem(), load_tilemap(entry.path())});
    }
    return tilemaps;
}

TilemapRender::TilemapRender(
    SDL_Renderer *renderer, const Tilemap &tilemap, const Tileset &tileset) {
    auto *surface = SDL_CreateRGBSurfaceWithFormat(0,
        tilemap.size.x * tileset.tile_size.x,
        tilemap.size.y * tileset.tile_size.y, 32, SDL_PIXELFORMAT_RGBA32);
    if (surface == nullptr) {
        throw std::runtime_error(
            std::string("Couldn't create surface: ") + SDL_GetError());
    }

    // Draw tilemap with given tileset.
    for (int y = 0; y < tilemap.size.y; y++) {
        for (int x = 0; x < tilemap.size.x; x++) {
            auto tile = tilemap.map.find({x, y});
            if (tile == tilemap.map.end()) {
                continue;
            }
            SDL_Rect src = tileset.at(tile->second);
            SDL_Rect dest{x * src.w, y * src.h, src.w, src.h};
            SDL_BlitSurface(tileset.surface.get(), &src, surface, &dest);
        }
    }

    auto *texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == nullptr) {
        throw std::runtime_error(
            std::string("Couldn't create texture: ") + SDL_GetError());
    }

    this->surface = std::unique_ptr<SDL_Surface, SDL_SurfaceDeleter>(surface);
    this->texture = std::unique_ptr<SDL_Texture, SDL_TextureDeleter>(texture);
}

void TilemapRender::render(
    SDL_Renderer *renderer, const Rect2Df &source) const {
    SDL_Rect src = source;
    SDL_RenderCopy(renderer, texture.get(), &src, nullptr);
}
