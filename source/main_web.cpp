#include "main_web.hpp"

static SDL_Window* gWindow;
static SDL_Renderer* gRenderer;

void main_loop ()
{
    // @Incomplete: ...
}

int main (int argc, char** argv)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(600, 400, 0, &gWindow, &gRenderer);
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
    emscripten_set_main_loop(main_loop, -1, 1);

    return 0;
}
