#include "input.hpp"

Keybinding::Keybinding(SDL_Scancode scancode, SDL_Keymod modifier_mask)
    : scancode(scancode) {
    if ((modifier_mask & allowed_modifier_mask) != modifier_mask) {
        throw std::invalid_argument("invalid keybinding modifier mask");
    }
    this->modifier_mask = modifier_mask;
}

Input::Input() {
    buttons_keybinding[Button::move_up] = Keybinding(SDL_SCANCODE_W);
    buttons_keybinding[Button::move_down] = Keybinding(SDL_SCANCODE_S);
    buttons_keybinding[Button::move_left] = Keybinding(SDL_SCANCODE_A);
    buttons_keybinding[Button::move_right] = Keybinding(SDL_SCANCODE_D);
    buttons_keybinding[Button::look_up]
        = Keybinding(SDL_SCANCODE_W, KMOD_SHIFT);
    buttons_keybinding[Button::look_down]
        = Keybinding(SDL_SCANCODE_S, KMOD_SHIFT);
    buttons_keybinding[Button::look_left]
        = Keybinding(SDL_SCANCODE_A, KMOD_SHIFT);
    buttons_keybinding[Button::look_right]
        = Keybinding(SDL_SCANCODE_D, KMOD_SHIFT);
}

bool Input::is_down(Button b) const {
    if (buttons_down.find(b) == buttons_down.end()) {
        return false;
    }
    return buttons_down.at(b);
}

void Input::check_event(SDL_KeyboardEvent &e) {
    for (auto &[button, keybinding] : buttons_keybinding) {
        if (e.keysym.scancode != keybinding.scancode) {
            continue;
        }

        auto mod = static_cast<SDL_Keymod>(
            e.keysym.mod & Keybinding::allowed_modifier_mask);
        if (mod == keybinding.modifier_mask
            || (mod & keybinding.modifier_mask) != 0) {
            buttons_down[button] = e.state == SDL_PRESSED;
        } else {
            buttons_down[button] = false;
        }
    }
}
