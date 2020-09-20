#include "main.hpp"

int main (int argc, char** argv)
{
    SDL_Init(SDL_INIT_EVERYTHING);

    Image test;

    InitWindow("Cover Jam Game", 640,360);
    LoadImage(test, "assets/test.bmp");

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
        DrawImage(test, 20,30);
        RefreshWindow();
    }

    FreeImage(test);
    QuitWindow();

    SDL_Quit();

    return 0;
}
