#include "main.hpp"

INTERNAL void QuitApplication ()
{
    QuitGame();
    QuitMixer();
    QuitInput();
    QuitWindow();

    QuitErrorSystem();
}

int main (int argc, char** argv)
{
    ErrorTerminateCallback = QuitApplication;

    gWindow.running = true;

    InitErrorSystem();
    InitWindow();
    InitMixer();
    InitInput();
    InitFrameTimer();

    if (gWindow.running)
    {
        gWindow.reset = true;
        while (gWindow.reset)
        {
            gWindow.running = true;
            gWindow.reset = false;

            RandomSeed();
            InitGame();
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

                UpdateGame(gTimer.delta_time);
                RenderGame(gTimer.delta_time);

                CapFramerate();

                RefreshWindow();
            }

            QuitGame();
        }
    }

    QuitApplication();

    return 0;
}
