#pragma once

#include <SDL.h>

#include "tileset.hpp"

class Sprite {
    Tileset tileset;
    Rect2Di tile_rect;
    int tile_variant{};

public:
    // The defintion of Tile and the value of tile_variant_count is determined
    // by the format of the character tilesets.
    enum class Tile { front, left, right, back };

    // For each tile in Tile there are 3 variants.
    static const int tile_variant_count = 3;

    Sprite(const Tileset &tileset);

    void set_tile(Tile tile, int variant = 0);
    void rotate_tile(Tile tile);

    void render(SDL_Renderer *renderer, const Rect2Df &dest) const;

private:
    Tile tile{};
};
