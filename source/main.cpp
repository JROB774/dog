#include "main.hpp"

int main (int argc, char** argv)
{
    SDL_Init(SDL_INIT_EVERYTHING);

    InitWindow("Cover Jam Game", 1280, 720);
    ShowWindow();

    bool running = true;
    while (running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
        }

        ClearWindow(MakeColor(0,0,0));
        RefreshWindow();
    }

    QuitWindow();

    SDL_Quit();

    return 0;
}
