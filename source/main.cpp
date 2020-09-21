#include "main.hpp"

int main (int argc, char** argv)
{
    SDL_Init(SDL_INIT_EVERYTHING);

    InitWindow("Cover Jam Game", 640,480);
    InitAudio();
    InitGame();

    InitFrameTimer();

    ShowWindow();

    bool running = true;
    while (running)
    {
        UpdateKeyboardState();

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {

            if (event.type == SDL_QUIT)
            {
                running = false;
            }
        }

        ClearWindow(MakeColor(1,1,1));

        UpdateGame(gTimer.delta_time);
        RenderGame(gTimer.delta_time);

        CapFramerate();
        RefreshWindow();
    }

    QuitGame();
    QuitAudio();
    QuitWindow();

    SDL_Quit();

    return 0;
}
