#include "tileset.hpp"

Tileset::Tileset(SDL_Renderer *renderer, SDL_Surface *surface, Vec2Di tile_size)
    : tile_size(tile_size) {
    columns = surface->w / tile_size.x;

    auto *texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == nullptr) {
        throw std::runtime_error(
            std::string("Couldn't create texture: ") + SDL_GetError());
    }

    this->surface = std::unique_ptr<SDL_Surface, SDL_SurfaceDeleter>(surface);
    this->texture = std::unique_ptr<SDL_Texture, SDL_TextureDeleter>(texture);
}

Rect2Di Tileset::at(int idx) const {
    return {
        (idx % columns) * tile_size.x,
        (idx / columns) * tile_size.y,
        tile_size.x,
        tile_size.y,
    };
}

Tileset load_tileset(SDL_Renderer *renderer, const std::filesystem::path &path,
    Vec2Di tile_size) {
    auto *surface = IMG_Load(path.c_str());
    if (surface == nullptr) {
        throw std::runtime_error(
            std::string("Couldn't load tileset: ") + IMG_GetError());
    }
    return Tileset(renderer, surface, tile_size);
}

Tilesets load_tilesets(SDL_Renderer *renderer,
    const std::filesystem::path &folder, Vec2Di tile_size) {
    Tilesets tilesets;
    for (const auto &entry : std::filesystem::directory_iterator(folder)) {
        if (entry.is_directory()) {
            continue;
        }

        const auto &path = entry.path();
        tilesets.insert({path.stem(), load_tileset(renderer, path, tile_size)});
    }
    return tilesets;
}
