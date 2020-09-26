INTERNAL void InitMenu ()
{
    LoadImage(gMenuState.title, "title.bmp");
    LoadImage(gMenuState.help, "help.bmp");
}

INTERNAL void QuitMenu ()
{
    FreeImage(gMenuState.title);
    FreeImage(gMenuState.help);
}

INTERNAL void UpdateMenu (float dt)
{
    if (IsKeyPressed(SDL_SCANCODE_Z)  || IsKeyPressed(SDL_SCANCODE_SPACE)  || IsButtonPressed(SDL_CONTROLLER_BUTTON_A))
    {
        gAppState.state = APP_STATE_GAME;
    }
}

INTERNAL void RenderMenu (float dt)
{
    DrawFill(0.0f,0.0f,WINDOW_SCREEN_W,WINDOW_SCREEN_H, MakeColor(1,1,1));

    float tx,ty;

    tx = roundf((float)WINDOW_SCREEN_W - gMenuState.title.w) / 2;
    ty = 64;

    DrawImage(gMenuState.title, tx,ty);

    std::string play_text = "PLAY GAME";

    tx = roundf((float)WINDOW_SCREEN_W - GetTextWidth(gAppState.sfont, play_text)) / 2;
    ty = WINDOW_SCREEN_H - 76;

    DrawText(gAppState.sfont, play_text, tx,ty, MakeColor(0,0,0));
}
