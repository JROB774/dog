INTERNAL bool InitWindow ()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        LOG_ERROR(ERR_MAX, "Failed to initialize SDL! (%s)", SDL_GetError());
        return false;
    }

    // The window starts off hidden so we don't have a white window displaying whilst all the resources load and systems initialize.
    gWindow.window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, WINDOW_START_W,WINDOW_START_H, SDL_WINDOW_RESIZABLE|SDL_WINDOW_HIDDEN);
    if (!gWindow.window)
    {
        LOG_ERROR(ERR_MAX, "Failed to create window! (%s)", SDL_GetError());
        return false;
    }

    gWindow.renderer = SDL_CreateRenderer(gWindow.window, -1, SDL_RENDERER_ACCELERATED);
    if (!gWindow.renderer)
    {
        LOG_ERROR(ERR_MAX, "Failed to create renderer! (%s)", SDL_GetError());
        return false;
    }

    gWindow.fullscreen = false;

    SDL_SetRenderDrawBlendMode(gWindow.renderer, SDL_BLENDMODE_BLEND);
    SDL_SetWindowMinimumSize(gWindow.window, WINDOW_SCREEN_W,WINDOW_SCREEN_H);

    return true;
}

INTERNAL void QuitWindow ()
{
    SDL_DestroyRenderer(gWindow.renderer);
    SDL_DestroyWindow(gWindow.window);
    SDL_Quit();
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

    // printf("Window Size: %d %d\n", windoww,windowh);

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

    // printf("Viewport: %d %d %d %d\n", viewport.x,viewport.y,viewport.w,viewport.h);

    SDL_RenderSetViewport(gWindow.renderer, &viewport);
}

INTERNAL void SetFullscreen (bool enable)
{
    gWindow.fullscreen = enable;
    SDL_SetWindowFullscreen(gWindow.window, (gWindow.fullscreen) ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
}

INTERNAL bool IsFullscreen ()
{
    return gWindow.fullscreen;
}
