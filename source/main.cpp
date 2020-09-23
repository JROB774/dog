#include "main.hpp"

INTERNAL void QuitApplication ()
{
    QuitGame();
    QuitMixer();
    QuitWindow();
    QuitErrorSystem();
}

int main (int argc, char** argv)
{
    ErrorTerminateCallback = QuitApplication;
    ErrorMaximumCallback = QuitApplication;

    gWindow.running = true;

    InitErrorSystem();
    InitWindow("DOG", 320,240);
    InitMixer();
    InitGame();

    InitFrameTimer();

    ShowWindow();

    while (gWindow.running)
    {
        UpdateKeyboardState();

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                gWindow.running = false;
            }
        }

        ClearWindow(MakeColor(0,0,0));
        SetViewport();

        UpdateGame(gTimer.delta_time);
        RenderGame(gTimer.delta_time);

        CapFramerate();

        RefreshWindow();
    }

    QuitApplication();

    return 0;
}
