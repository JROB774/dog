INTERNAL bool InitWindow ()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        LOG_ERROR(ERR_MAX, "Failed to initialize SDL! (%s)", SDL_GetError());
        return false;
    }

    // These will never change or be used when in the web build of the game!
    gWindow.width = WINDOW_START_W;
    gWindow.height = WINDOW_START_H;
    gWindow.running = true;
    gWindow.fullscreen = false;

    if (SDL_CreateWindowAndRenderer(WINDOW_START_W,WINDOW_START_H, 0, &gWindow.window, &gWindow.renderer) < 0)
    {
        LOG_ERROR(ERR_MAX, "Failed to create window and/or renderer! (%s)", SDL_GetError());
        return false;
    }

    SDL_SetRenderDrawBlendMode(gWindow.renderer, SDL_BLENDMODE_BLEND);

    return true;
}

INTERNAL void QuitWindow ()
{
    // Nothing...
}

INTERNAL void ShowWindow ()
{
    // Nothing...
}

INTERNAL void HideWindow ()
{
    // Nothing...
}

INTERNAL void SetFullscreen (bool enable)
{
    // Nothing...
}

INTERNAL bool IsFullscreen ()
{
    return false;
}

INTERNAL int GetWindowWidth ()
{
    return WINDOW_START_W;
}

INTERNAL int GetWindowHeight ()
{
    return WINDOW_START_H;
}

INTERNAL void SetWindowSize (int width, int height)
{
    // Nothing...
}
