#include <SDL2/SDL.h>

#define PERSISTENT static
#define GLOBAL     static
#define INTERNAL   static

#if defined(BUILD_DEBUG)
#include <assert.h>
#define ASSERT(e) assert(e)
#else
#define ASSERT()
#endif

GLOBAL constexpr const char* WINDOW_TITLE = "Cover Jam Game";
GLOBAL constexpr int         WINDOW_X     = SDL_WINDOWPOS_CENTERED;
GLOBAL constexpr int         WINDOW_Y     = SDL_WINDOWPOS_CENTERED;
GLOBAL constexpr int         WINDOW_W     = 1280;
GLOBAL constexpr int         WINDOW_H     =  720;
GLOBAL constexpr int         WINDOW_FLAGS = SDL_WINDOW_RESIZABLE|SDL_WINDOW_HIDDEN;

GLOBAL SDL_Window*   window;
GLOBAL SDL_Renderer* renderer;

int main (int argc, char** argv)
{
    SDL_Init(SDL_INIT_EVERYTHING);

    window = SDL_CreateWindow(WINDOW_TITLE,WINDOW_X,WINDOW_Y,WINDOW_W,WINDOW_H,WINDOW_FLAGS);
    ASSERT(window);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    ASSERT(renderer);

    SDL_ShowWindow(window);

    bool running = true;
    while (running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0x00,0x00,0x00,0xFF);
        SDL_RenderClear(renderer);

        // ...

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
