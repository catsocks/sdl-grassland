// TODO: Add item (e.g. a health potion).
// TODO: Add pet that idles and runs offscreen when attacked.
// TODO: Move companion when the player's movement is blocked by it.
// TODO: Swap the companion for a monster that attacks the player.
// TODO: Better integrate Grid with the game state.
#include <SDL.h>
#include <SDL_image.h>

#include "math.hpp"
#include "player.hpp"
#include "sprite.hpp"
#include "tilemap.hpp"
#include "tileset.hpp"
#include "world.hpp"

constexpr auto TILE_WIDTH = 32;
constexpr auto TILE_HEIGHT = 32;

constexpr auto RENDERER_WIDTH = TILE_WIDTH * 16;
constexpr auto RENDERER_HEIGHT = TILE_HEIGHT * 16;
constexpr auto SCALE_FACTOR = 1.5;

constexpr auto WINDOW_TITLE = "Grassland";
constexpr auto WINDOW_WIDTH = RENDERER_WIDTH * SCALE_FACTOR;
constexpr auto WINDOW_HEIGHT = RENDERER_HEIGHT * SCALE_FACTOR;

int main() {
    // Setup SDL and SDL_image and create a window and a renderer.

    // Initialize SDL with the video subsystem.
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
            "Couldn't initialize SDL: %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    // Initialize SDL_image with PNG support.
    if (IMG_Init(IMG_INIT_PNG) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
            "Couldn't initialize SDL_image: %s", IMG_GetError());
        return EXIT_FAILURE;
    }

    // Create a hidden SDL window.
    SDL_Window *window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_HIDDEN);
    if (!window) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
            "Couldn't create SDL window: %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    // Create a SDL renderer which has presentation synced to VSync.
    SDL_Renderer *renderer
        = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
            "Couldn't create SDL renderer: %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    // Adjust the renderer scale.
    if (SDL_RenderSetScale(renderer, SCALE_FACTOR, SCALE_FACTOR) == -1) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
            "Couldn't set render scale: %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    // Load tilesets and tilemaps from files.

    // Load tilesets with equal tile size from the tilesets folder.
    std::map<std::string, Tileset> tilesets;
    try {
        tilesets = load_tilesets("tilesets", TILE_WIDTH, TILE_HEIGHT);
    } catch (std::exception &e) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't load tilesets: %s",
            e.what());
        return EXIT_FAILURE;
    }

    // Load tilemaps from the tilemaps folder.
    std::map<std::string, Tilemap> tilemaps;
    try {
        tilemaps = load_tilemaps("tilemaps");
    } catch (std::exception &e) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't load tilemaps: %s",
            e.what());
        return EXIT_FAILURE;
    }

    // Render tilemaps with given tilesets.
    auto background = render_tilemap(
        renderer, tilemaps.at("World_Background"), tilesets.at("misc"));
    auto foreground = render_tilemap(
        renderer, tilemaps.at("World_Foreground"), tilesets.at("misc"));

    // Show the window after most costly iitial operations are done.
    SDL_ShowWindow(window);

    uint32_t ticks = 0; // for calculating delta time

    // Begin defining the game state.

    Grid grid(tilemaps.at("World_Background"));
    grid.set_obstacles(tilemaps.at("World_Obstacles"));

    // Create sprites.
    Vec2D tile_size{TILE_WIDTH, TILE_HEIGHT};

    Sprite girl(Vec2D{16, 16} * tile_size, tile_size);
    Sprite npc(Vec2D{17, 2} * tile_size, tile_size);

    girl.kind = Sprite::Kind::girl;

    girl.set_texture(renderer, tilesets.at("girl"));
    npc.set_texture(renderer, tilesets.at("npc"));

    World world(grid.get_size() * tile_size);
    world.grid = &grid;
    world.sprites.insert(world.sprites.end(), {&girl, &npc});

    // The camera will target the girl sprite.
    Rect2D camera(0, 0, RENDERER_WIDTH, RENDERER_HEIGHT);

    while (true) {
        // Calculate delta time in seconds.
        uint32_t last_ticks = ticks;
        ticks = SDL_GetTicks();
        float dt = static_cast<float>(ticks - last_ticks) / 1000;

        if (SDL_QuitRequested()) {
            break;
        }

        // Use player input to control given sprite.
        player_input(world, girl);

        // Update sprites.
        girl.update(dt);
        npc.update(dt);

        npc.move(world, girl);

        // Update camera.
        camera = camera.center(girl.rect);
        camera = camera.clamp(world.rect);

        // Begin compositing.

        // Render tilemaps.
        background.draw(renderer, camera);
        foreground.draw(renderer, camera);

        // Render sprites.
        npc.draw(renderer, camera);
        girl.draw(renderer, camera);

        // Compositing has finished.
        SDL_RenderPresent(renderer);
    }

    // Clean up.

    // Free tileset images.
    for (auto &[key, val] : tilesets) {
        SDL_FreeSurface(val.image);
    }

    // Free sprite textures.
    SDL_DestroyTexture(girl.texture);
    SDL_DestroyTexture(npc.texture);

    // Free rendered tilemap textures and surfaces.
    SDL_DestroyTexture(background.texture);
    SDL_FreeSurface(background.surface);
    SDL_DestroyTexture(foreground.texture);
    SDL_FreeSurface(foreground.surface);

    // Quit SDL.
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}
