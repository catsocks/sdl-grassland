#include "sprite.hpp"

Sprite::Sprite(const Tileset &tileset)
    : tileset(tileset) {
    tile_rect.width = tileset.tile_size.x;
    tile_rect.height = tileset.tile_size.y;
    set_tile(Sprite::Tile::front, 1);
}

void Sprite::set_tile(Tile tile, int variant) {
    SDL_assert(variant < tile_variant_count);
    this->tile = tile;
    this->tile_variant = variant;
    tile_rect.y = static_cast<int>(tile) * tile_rect.height;
    tile_rect.x = tile_variant * tile_rect.width;
}

void Sprite::rotate_tile(Tile tile) {
    set_tile(
        tile, (tile_variant < tile_variant_count - 1) ? tile_variant + 1 : 0);
}

void Sprite::render(SDL_Renderer *renderer, const Rect2Df &dest) const {
    SDL_Rect src = tile_rect;
    SDL_Rect dest_rect = dest;
    SDL_RenderCopy(renderer, tileset.texture.get(), &src, &dest_rect);
}
