#include "player.hpp"

void player_input(World &world, Sprite &sprite) {
    auto pressed_keys = SDL_GetKeyboardState(nullptr);

    Sprite::Direction dir;
    if (pressed_keys[SDL_SCANCODE_UP]) {
        dir = Sprite::Direction::up;
    } else if (pressed_keys[SDL_SCANCODE_DOWN]) {
        dir = Sprite::Direction::down;
    } else if (pressed_keys[SDL_SCANCODE_LEFT]) {
        dir = Sprite::Direction::left;
    } else if (pressed_keys[SDL_SCANCODE_RIGHT]) {
        dir = Sprite::Direction::right;
    } else {
        return;
    }

    if (SDL_GetModState() & KMOD_SHIFT) {
        sprite.look(dir, true);
    } else {
        sprite.move(world, dir);
    }
}
