#include "main.hpp"

int main (int argc, char** argv)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    initAudio();

    InitWindow("DOG", 320,240);
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

        ClearWindow(MakeColor(0,0,0));
        SetViewport();

        UpdateGame(gTimer.delta_time);
        RenderGame(gTimer.delta_time);

        CapFramerate();

        RefreshWindow();
    }

    QuitGame();
    QuitWindow();

    endAudio();
    SDL_Quit();

    return 0;
}
