#include "tilemap.hpp"

std::optional<int> Tilemap::at(int x, int y) {
    return tiles.at(y * width + x);
}

Tilemap load_tilemap(const fs::path &path) {
    Tilemap tilemap;
    std::ifstream file(path);

    for (std::string line; std::getline(file, line);) {
        int rowlen = 0;
        std::stringstream ss(line);
        for (std::string item; std::getline(ss, item, ',');) {
            int col = std::stoi(item);
            tilemap.tiles.push_back(
                (col == -1) ? std::nullopt : std::optional<int>{col});
            rowlen += 1;
        }

        if (tilemap.width == 0) {
            tilemap.width = rowlen;
        } else if (tilemap.width != rowlen) {
            throw std::runtime_error("tilemap has unequal row lengths");
        }
        tilemap.height += 1;
    }
    return tilemap;
}

std::map<std::string, Tilemap> load_tilemaps(const fs::path &folder) {
    std::map<std::string, Tilemap> tilemaps;
    for (auto &entry : fs::directory_iterator(folder)) {
        if (entry.is_directory()) {
            continue;
        }

        tilemaps.insert_or_assign(
            entry.path().stem(), load_tilemap(entry.path()));
    }
    return tilemaps;
}

TilemapRender::TilemapRender()
    : surface(nullptr)
    , texture(nullptr) { }

void TilemapRender::draw(SDL_Renderer *renderer, const Rect2D &camera) {
    SDL_Rect rect = camera;
    SDL_RenderCopy(renderer, texture, &rect, nullptr);
}

TilemapRender render_tilemap(SDL_Renderer *renderer, Tilemap &tm, Tileset &ts) {
    TilemapRender render;

    // Create surface.
    render.surface = SDL_CreateRGBSurfaceWithFormat(0, tm.width * ts.tile_width,
        tm.height * ts.tile_height, 32, SDL_PIXELFORMAT_RGBA32);
    if (!render.surface) {
        throw std::runtime_error(
            std::string("couldn't create surface: ") + SDL_GetError());
    }

    // Draw tilemap with given tileset.
    for (int y = 0; y < tm.height; y++) {
        for (int x = 0; x < tm.width; x++) {
            auto tile = tm.at(x, y);
            if (tile.has_value()) {
                auto src = ts.at(tile.value());
                SDL_Rect dest{
                    x * src.w, y * src.h, ts.tile_width, ts.tile_height};
                SDL_BlitSurface(ts.image, &src, render.surface, &dest);
            }
        }
    }

    render.texture = SDL_CreateTextureFromSurface(renderer, render.surface);
    if (!render.texture) {
        throw std::runtime_error(
            std::string("couldn't create texture: ") + SDL_GetError());
    }

    return render;
}
