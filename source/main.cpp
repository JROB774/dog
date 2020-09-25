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

    gWindow.running = true;

    InitErrorSystem();
    InitWindow();
    InitMixer();
    InitFrameTimer();

    if (gWindow.running)
    {
        bool reset = true;
        while (reset)
        {
            gWindow.running = true;
            reset = false;

            RandomSeed();
            InitGame();
            ShowWindow();

            while (gWindow.running)
            {
                UpdateKeyboardState();

                SDL_Event event;
                while (SDL_PollEvent(&event))
                {
                    switch (event.type)
                    {
                        #if defined(BUILD_DEBUG)
                        case (SDL_KEYDOWN):
                        {
                            if (event.key.keysym.sym == SDLK_F5)
                            {
                                gWindow.running = false;
                                reset = true;
                            }
                        } break;
                        #endif
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
