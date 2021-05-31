#include "sprite.hpp"

Sprite::Sprite(const Vector2 &pos, const Vector2 &size)
    : rect(pos, size)
    , dest(rect) { }

void Sprite::set_texture(SDL_Renderer *renderer, Tileset &ts) {
    texture = SDL_CreateTextureFromSurface(renderer, ts.image);
    if (!texture) {
        throw std::runtime_error(
            std::string("Couldn't create texture: ") + SDL_GetError());
    }
}

void Sprite::look(Direction dir, bool reset_walk_cycle) {
    direction = dir;
    if (reset_walk_cycle) {
        walk_cycle = INITIAL_WALK_CYCLE;
    }
}

bool Sprite::sees(const Vector2 &distance) {
    if (distance.x > rect.width * SIGHT) {
        return false;
    }
    if (distance.y > rect.height * SIGHT) {
        return false;
    }
    return true;
}

void Sprite::look(const Sprite &target, bool reset_walk_cycle) {
    auto dist = rect.distance(target.rect);
    if (!sees(dist)) {
        return;
    }

    if (dist.y > dist.x) {
        if (rect.y > target.rect.y) {
            look(Direction::up, reset_walk_cycle);
        } else if (rect.y < target.rect.y) {
            look(Direction::down, reset_walk_cycle);
        }
    } else if (dist.x > dist.y) {
        if (rect.x > target.rect.x) {
            look(Direction::left, reset_walk_cycle);
        } else if (rect.x < target.rect.x) {
            look(Direction::right, reset_walk_cycle);
        }
    }
}

void Sprite::move(World &world, Direction dir, bool ignore_obstacles) {
    if (rect != dest) {
        return;
    }

    auto new_dest = rect;
    switch (dir) {
    case Direction::down:
        new_dest.y += new_dest.height;
        break;
    case Direction::left:
        new_dest.x -= new_dest.width;
        break;
    case Direction::right:
        new_dest.x += new_dest.width;
        break;
    case Direction::up:
        new_dest.y -= new_dest.height;
        break;
    }

    if (!world.rect.fits_within(new_dest)) {
        look(dir, true);
        return;
    }

    // TODO: Make this part of Grid's passable member.
    // TODO: Remove weak assumption that kind member will be unique among
    // sprites.
    for (auto &s : world.sprites) {
        if (s->kind != kind && s->dest.x == new_dest.x
            && s->dest.y == new_dest.y) {
            look(dir, true);
            return;
        }
    }

    if (!ignore_obstacles) {
        auto new_loc = make_location(new_dest);
        if (!world.grid->passable(new_loc)) {
            look(dir, true);
            return;
        }
    }

    look(dir);
    dest = new_dest;
    walk_cycle = (walk_cycle + 1) % WALK_CYCLES;
}

void Sprite::move(World &world, const Sprite &target) {
    if (rect != dest) {
        return;
    }

    if (!sees(rect.distance(target.rect))) {
        return;
    }

    auto start = make_location(dest);
    auto goal = make_location(target.dest);

    auto came_from = breadth_first_search(*world.grid, start, goal);
    auto path = reconstruct_path(start, goal, came_from);

    if (start == goal || path.size() < 3) {
        look(target, true);
        return;
    }

    auto next_loc = path.begin();
    if (next_loc->x * rect.width > rect.x) {
        move(world, Direction::right, true);
    } else if (rect.x > next_loc->x * rect.width) {
        move(world, Direction::left, true);
    }

    if (next_loc->y * rect.height > rect.y) {
        move(world, Direction::down, true);
    } else if (rect.y > next_loc->y * rect.height) {
        move(world, Direction::up, true);
    }
}

void Sprite::update(float dt) {
    // TODO: Ease-out movement when the sprite stops continiously moving.
    // TODO: Change walk cycle while the sprite moves.
    // TODO: Reset walk cycle when sprite stops moving.
    rect = rect.move_towards(dest, dt * 150);
}

void Sprite::draw(SDL_Renderer *renderer, const Rect &camera) {
    SDL_Rect src{walk_cycle * rect.width,
        rect.height * static_cast<int>(direction), rect.width, rect.height};

    SDL_Rect renderer_dest = rect.move_inverse(camera);
    SDL_RenderCopy(renderer, texture, &src, &renderer_dest);
}
