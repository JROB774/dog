#include <sstream>

INTERNAL bool InitWindow (std::string title, int w, int h)
{
    // The window starts off hidden so we don't have a white window displaying whilst all the resources load and systems initialize.
    gWindow.window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, w,h, SDL_WINDOW_RESIZABLE|SDL_WINDOW_HIDDEN);
    ASSERT(gWindow.window);
    gWindow.renderer = SDL_CreateRenderer(gWindow.window, -1, SDL_RENDERER_ACCELERATED);
    ASSERT(gWindow.renderer);
    SDL_SetWindowMinimumSize(gWindow.window, w,h);

    gWindow.screenw = w;
    gWindow.screenh = h;

    return true;
}

INTERNAL void QuitWindow ()
{
    SDL_DestroyRenderer(gWindow.renderer);
    SDL_DestroyWindow(gWindow.window);
}

INTERNAL void ClearWindow (Color color)
{
    SDL_Color c = ColorToSDLColor(color);
    SDL_SetRenderDrawColor(gWindow.renderer, c.r,c.g,c.b,c.a);
    SDL_RenderClear(gWindow.renderer);
}

INTERNAL void RefreshWindow ()
{
    SDL_RenderPresent(gWindow.renderer);
}

INTERNAL void ShowWindow ()
{
    SDL_ShowWindow(gWindow.window);
}

INTERNAL void HideWindow ()
{
    SDL_HideWindow(gWindow.window);
}

INTERNAL void SetViewport ()
{
    int windoww,windowh;
    SDL_GetWindowSize(gWindow.window, &windoww,&windowh);

    int sx = (int)roundf(((float)windoww / (float)gWindow.screenw));
    int sy = (int)roundf(((float)windowh / (float)gWindow.screenh));

    // Determine the smallest scale and use that.
    float scale = (float)((sx < sy) ? sx : sy);

    SDL_RenderSetScale(gWindow.renderer, scale,scale);

    SDL_Rect viewport;

    viewport.x = ((windoww - (gWindow.screenw * (int)scale)) / 2) / (int)scale;
    viewport.y = ((windowh - (gWindow.screenh * (int)scale)) / 2) / (int)scale;
    viewport.w = gWindow.screenw;
    viewport.h = gWindow.screenh;

    SDL_RenderSetViewport(gWindow.renderer, &viewport);
}
