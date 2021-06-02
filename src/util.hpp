#pragma once

#include <SDL.h>

struct SDL_WindowDeleter {
    inline void operator()(SDL_Window *w) const noexcept {
        SDL_DestroyWindow(w);
    }
};

struct SDL_RendererDeleter {
    inline void operator()(SDL_Renderer *r) const noexcept {
        SDL_DestroyRenderer(r);
    }
};

struct SDL_SurfaceDeleter {
    inline void operator()(SDL_Surface *s) const noexcept {
        SDL_FreeSurface(s);
    }
};

struct SDL_TextureDeleter {
    inline void operator()(SDL_Texture *t) const noexcept {
        SDL_DestroyTexture(t);
    }
};
