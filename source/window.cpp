INTERNAL bool InitWindow (const char* title, int w, int h)
{
    // The window starts off hidden so we don't have a white window displaying whilst all the resources load and systems initialize.
    gWindow.window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, w,h, SDL_WINDOW_RESIZABLE|SDL_WINDOW_HIDDEN);
    ASSERT(gWindow.window);
    gWindow.renderer = SDL_CreateRenderer(gWindow.window, -1, SDL_RENDERER_ACCELERATED);
    ASSERT(gWindow.renderer);

    return true;
}

INTERNAL void QuitWindow ()
{
    SDL_DestroyRenderer(gWindow.renderer);
    SDL_DestroyWindow(gWindow.window);
}

INTERNAL void ClearWindow (u8 r, u8 g, u8 b, u8 a)
{
    SDL_SetRenderDrawColor(gWindow.renderer, r,g,b,a);
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
