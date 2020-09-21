#include "main.hpp"

int main (int argc, char** argv)
{
    SDL_Init(SDL_INIT_EVERYTHING);

    Map test;
    
    InitWindow("Cover Jam Game", 640,480);
    LoadMap(test, "assets/maptest.bmp");

    ShowWindow();

    DogCreate();

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
        DrawMap(test);
        DogDraw();
        RefreshWindow();
    }

    FreeMap(test);
    QuitWindow();

    SDL_Quit();

    return 0;
}
