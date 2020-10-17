#include "main_web.hpp"

void main_loop ()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        // @Incomplete: ...
    }

    ClearWindow(MakeColor(0,0,0));
    SetViewport();

    RefreshWindow();
    CapFramerate();
}

int main (int argc, char** argv)
{
    InitFrameTimer();
    InitWindow();

    emscripten_set_main_loop(main_loop, -1, 1);

    return 0;
}
