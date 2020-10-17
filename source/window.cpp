#if defined(PLATFORM_WIN32)
#include "OS/win32/window.cpp"
#elif defined(PLATFORM_WEB)
#include "OS/web/window.cpp"
#endif

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

INTERNAL void SetViewport ()
{
    int windoww,windowh;
    SDL_GetWindowSize(gWindow.window, &windoww,&windowh);

    int sx = (int)floorf(((float)windoww / (float)WINDOW_SCREEN_W));
    int sy = (int)floorf(((float)windowh / (float)WINDOW_SCREEN_H));

    // Determine the smallest scale and use that.
    float scale = (float)((sx < sy) ? sx : sy);

    SDL_RenderSetScale(gWindow.renderer, scale,scale);

    SDL_Rect viewport;

    viewport.x = ((windoww - (WINDOW_SCREEN_W * (int)scale)) / 2) / (int)scale;
    viewport.y = ((windowh - (WINDOW_SCREEN_H * (int)scale)) / 2) / (int)scale;
    viewport.w = WINDOW_SCREEN_W;
    viewport.h = WINDOW_SCREEN_H;

    SDL_RenderSetViewport(gWindow.renderer, &viewport);
}
