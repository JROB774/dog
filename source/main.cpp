#include "main.hpp"

int main (int argc, char** argv)
{
    gWindow.running = false;

    SDL_Init(SDL_INIT_EVERYTHING);

    InitWindow("DOG", 320,240);
    InitGame();

    InitFrameTimer();

    ShowWindow();

    gWindow.running = true;
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

    QuitGame();
    QuitWindow();

    SDL_Quit();

    return 0;
}
