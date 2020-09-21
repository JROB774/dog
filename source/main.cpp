#include "main.hpp"

int main (int argc, char** argv)
{
    SDL_Init(SDL_INIT_EVERYTHING);

    Map test;

    InitWindow("Cover Jam Game", 320,240);
    LoadMap(test, "assets/maptest.bmp");

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

        ClearWindow(MakeColor(0.5f,0.5f,0.5f));
        DrawMap(test);
        RefreshWindow();
    }

    FreeMap(test);
    QuitWindow();

    SDL_Quit();

    return 0;
}
