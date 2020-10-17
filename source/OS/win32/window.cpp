INTERNAL bool InitWindow ()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        LOG_ERROR(ERR_MAX, "Failed to initialize SDL! (%s)", SDL_GetError());
        return false;
    }

    gWindow.width = gSettings.window_width;
    gWindow.height = gSettings.window_height;

    // The window starts off hidden so we don't have a white window displaying whilst all the resources load and systems initialize.
    gWindow.window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, gWindow.width,gWindow.height, SDL_WINDOW_RESIZABLE|SDL_WINDOW_HIDDEN);
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

    SDL_SetRenderDrawBlendMode(gWindow.renderer, SDL_BLENDMODE_BLEND);
    SDL_SetWindowMinimumSize(gWindow.window, WINDOW_SCREEN_W,WINDOW_SCREEN_H);

    SetFullscreen(gSettings.fullscreen);

    return true;
}

INTERNAL void QuitWindow ()
{
    SDL_DestroyRenderer(gWindow.renderer);
    SDL_DestroyWindow(gWindow.window);
    SDL_Quit();
}

INTERNAL void ShowWindow ()
{
    SDL_ShowWindow(gWindow.window);
}

INTERNAL void HideWindow ()
{
    SDL_HideWindow(gWindow.window);
}

INTERNAL void SetFullscreen (bool enable)
{
    if (enable) gWindow.width = GetWindowWidth();
    if (enable) gWindow.height = GetWindowHeight();

    gWindow.fullscreen = enable;
    SDL_SetWindowFullscreen(gWindow.window, (gWindow.fullscreen) ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
    SDL_ShowCursor((gWindow.fullscreen) ? SDL_DISABLE : SDL_ENABLE);
}

INTERNAL bool IsFullscreen ()
{
    return gWindow.fullscreen;
}

INTERNAL int GetWindowWidth ()
{
    if (gWindow.fullscreen) return gWindow.width;
    int windoww,windowh;
    SDL_GetWindowSize(gWindow.window, &windoww,&windowh);
    return windoww;
}

INTERNAL int GetWindowHeight ()
{
    if (gWindow.fullscreen) return gWindow.height;
    int windoww,windowh;
    SDL_GetWindowSize(gWindow.window, &windoww,&windowh);
    return windowh;
}

INTERNAL void SetWindowSize (int width, int height)
{
    SDL_SetWindowSize(gWindow.window, width, height);
}
