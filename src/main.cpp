#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <optional>

#include "game.hpp"

int main(int argc, char *argv[]) {
    // SDL needs that main take argc and argv when compiling for Windows.
    (void)argc;
    (void)argv;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
            "Couldn't initialize SDL: %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    if (IMG_Init(IMG_INIT_PNG) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
            "Couldn't initialize SDL_image: %s", IMG_GetError());
        return EXIT_FAILURE;
    }

    Game game("Grassland");

    while (!game.should_quit) {
        game.update();
    }

    IMG_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}
