#include "main_win32.hpp"

INTERNAL void QuitSystems ()
{
    QuitGame();
    QuitMixer();
    QuitInput();
    QuitWindow();

    QuitErrorSystem();
}

int main (int argc, char** argv)
{
    ErrorTerminateCallback = QuitSystems;

    gWindow.running = true;

    InitErrorSystem();
    SetupAssetPath();
    LoadSettings();
    InitWindow();
    InitMixer();
    InitFrameTimer();

    RandomSeed();
    InitApplication();
    ShowWindow();

    while (gWindow.running)
    {
        UpdateInputState();

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            HandleInputEvents(event);
            switch (event.type)
            {
                case (SDL_QUIT):
                {
                    gWindow.running = false;
                } break;
            }
        }

        ClearWindow(MakeColor(0,0,0));
        SetViewport();

        UpdateApplication(gTimer.delta_time);
        RenderApplication(gTimer.delta_time);

        CapFramerate();

        RefreshWindow();
    }

    QuitApplication();
    QuitSystems();

    return 0;
}
