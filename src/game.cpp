#include "game.hpp"

Game::Game(const std::string &window_title) {
    // TODO: Adjust the window size to fit a percentage of the screen.
    Vec2Di renderer_size{tile_size.x * 16, tile_size.y * 16};

    auto scale_factor = 1.5;
    int window_width = renderer_size.x * scale_factor;
    int window_height = renderer_size.y * scale_factor;

    // TODO: Let the window be resized.
    auto *window = SDL_CreateWindow(window_title.c_str(),
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_width,
        window_height, SDL_WINDOW_HIDDEN);
    if (window == nullptr) {
        throw std::runtime_error("Couldn't create window");
    }

    auto *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        throw std::runtime_error("Couldn't create renderer");
    }

    if (SDL_RenderSetScale(renderer, scale_factor, scale_factor) == -1) {
        throw std::runtime_error("Couldn't set renderer scale");
    }

    tilemaps = load_tilemaps("tilemaps");
    tilesets = load_tilesets(renderer, "tilesets", tile_size);

    world = World(renderer, tile_size, renderer_size, tilemaps, tilesets);

    this->window = std::unique_ptr<SDL_Window, SDL_WindowDeleter>(window);
    this->renderer
        = std::unique_ptr<SDL_Renderer, SDL_RendererDeleter>(renderer);

    // Show the window only after the game is done initialziing.
    SDL_ShowWindow(window);
}

void Game::update() {
    SDL_Event event{};
    while (SDL_PollEvent(&event) == 1) {
        switch (event.type) {
        case SDL_QUIT:
            should_quit = true;
            break;
        case SDL_KEYDOWN:
        case SDL_KEYUP:
            input.check_event(event.key);
            break;
        }
    }

    if (counter_time == 0) {
        counter_time = SDL_GetPerformanceCounter();
    }

    uint64_t new_counter_time = SDL_GetPerformanceCounter();
    double frame_time = (new_counter_time - counter_time)
        / static_cast<double>(SDL_GetPerformanceFrequency());
    counter_time = new_counter_time;

    int steps = 0;
    while (frame_time > 0 && steps <= 60) {
        double delta_time = fmin(frame_time, 1 / 60.0);
        world.update(input, delta_time);
        frame_time -= delta_time;
        time += delta_time;
        steps++;
    }

    world.render(renderer.get());

    SDL_RenderPresent(renderer.get());
}
