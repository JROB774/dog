#include "main_web.hpp"

void main_loop ()
{
    UpdateInputState();

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        HandleInputEvents(event);
    }

    ClearWindow(MakeColor(1,1,1));
    SetViewport();

    UpdateApplication(gTimer.delta_time);
    RenderApplication(gTimer.delta_time);

    RefreshWindow();
    CapFramerate();
}

int main (int argc, char** argv)
{
    SetupAssetPath();
    LoadSettings();
    InitWindow();
    InitMixer();
    InitFrameTimer();

    RandomSeed();
    InitApplication();

    emscripten_set_main_loop(main_loop, -1, 1);

    return 0;
}
