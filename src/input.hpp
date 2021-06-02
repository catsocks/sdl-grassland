#pragma once

#include <SDL.h>
#include <stdexcept>
#include <unordered_map>

enum class Button {
    move_up,
    move_down,
    move_left,
    move_right,
    look_up,
    look_down,
    look_left,
    look_right,
};

struct Keybinding {
    SDL_Scancode scancode{};
    SDL_Keymod modifier_mask{};

    static constexpr SDL_Keymod allowed_modifier_mask
        = static_cast<SDL_Keymod>(KMOD_CTRL | KMOD_SHIFT | KMOD_ALT);

    Keybinding() = default;
    Keybinding(SDL_Scancode scancode, SDL_Keymod modifier_mask = KMOD_NONE);
};

class Input {
    std::unordered_map<Button, Keybinding> buttons_keybinding;
    std::unordered_map<Button, bool> buttons_down;

public:
    Input();

    bool is_down(Button b) const;

    void check_event(SDL_KeyboardEvent &event);
};
