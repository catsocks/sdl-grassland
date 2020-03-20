#include "tileset.hpp"

void Tileset::set_image(SDL_Surface *surface) {
    image = surface;
    cols = surface->w / tile_width;
}

SDL_Rect Tileset::at(int index) {
    return {
        index % cols * tile_width,
        index / cols * tile_height,
        tile_width,
        tile_height,
    };
}

Tileset load_tileset(const fs::path &path, int tile_width, int tile_height) {
    Tileset tileset(tile_width, tile_height);
    SDL_Surface *surface = IMG_Load(path.c_str());
    if (!surface) {
        throw std::runtime_error(std::string("Couldn't load tileset image: ") +
                                 IMG_GetError());
    }
    tileset.set_image(surface);
    return tileset;
}

std::map<std::string, Tileset> load_tilesets(const fs::path &folder,
                                             int tile_width, int tile_height) {
    std::map<std::string, Tileset> tilesets;
    for (auto &entry : fs::directory_iterator(folder)) {
        if (entry.is_directory()) {
            continue;
        }

        tilesets.insert_or_assign(
            entry.path().stem(),
            load_tileset(entry.path(), tile_width, tile_height));
    }
    return tilesets;
}
