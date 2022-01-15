#include "main_web.hpp"

void main_loop ()
{
    static U64 performanceFrequency = SDL_GetPerformanceFrequency();
    static U64 lastCounter = SDL_GetPerformanceCounter();
    static U64 endCounter = 0;
    static U64 elapsedCounter = 0;

    static float updateTimer = 0.0f;

    float updateRate = 1.0f / (float)60.0f;

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        HandleInputEvents(event);
    }

    bool updated = false;
    while (updateTimer >= updateRate)
    {
        UpdateInputState();
        ClearWindow(MakeColor(1,1,1));
        SetViewport();
        UpdateApplication(updateRate);
        RenderApplication(updateRate);
        updateTimer -= updateRate;
        updated = true;
    }

    endCounter = SDL_GetPerformanceCounter();
    elapsedCounter = endCounter - lastCounter;
    lastCounter = SDL_GetPerformanceCounter();

    updateTimer += (float)elapsedCounter / (float)performanceFrequency;

    if (updated)
    {
        RefreshWindow();
    }
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
