#pragma once

#include <SDL.h>

#include "grid.hpp"
#include "math.hpp"
#include "tileset.hpp"
#include "world.hpp"

class Sprite {
    static constexpr auto INITIAL_WALK_CYCLE = 1;
    static constexpr auto WALK_CYCLES = 3; // assumption about tilesets
    static constexpr auto SIGHT = 6; // range of sight in tiles

public:
    enum class Kind { npc, girl };

    // Direction order is important for drawing sprites.
    enum class Direction { down, left, right, up };

    Rect rect;
    Rect dest;
    Kind kind{};
    Direction direction{};
    int walk_cycle = INITIAL_WALK_CYCLE;

    SDL_Texture *texture{};

    Sprite(const Vector2 &pos, const Vector2 &size);

    void set_texture(SDL_Renderer *renderer, Tileset &ts);

    bool sees(const Vector2 &distance);
    void look(Direction dir, bool reset_walk_cycle = false);
    void look(const Sprite &target, bool reset_walk_cycle = false);
    void move(World &world, Direction dir, bool ignore_obstacles = false);
    void move(World &world, const Sprite &target);

    void update(float dt);

    void draw(SDL_Renderer *renderer, const Rect &camera);
};
