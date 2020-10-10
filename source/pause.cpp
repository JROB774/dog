enum PauseItem
{
    PAUSE_ITEM_RETURN,
    PAUSE_ITEM_RETRY,
    PAUSE_ITEM_MENU,
    PAUSE_ITEM_EXITGAME,
    PAUSE_ITEM_TOTAL
};

INTERNAL void InitPause ()
{
    gPauseState.selected = 0;

    LoadImage(gPauseState.title, "pause.bmp");
    LoadImage(gPauseState.caret, "caret.bmp");

    LoadAnimation(gPauseState.caret_anim, "caret.anim");

    LoadSound(gPauseState.snd_change, "change.wav");
    LoadSound(gPauseState.snd_select, "select.wav");
}

INTERNAL void QuitPause ()
{
    FreeSound(gPauseState.snd_change);
    FreeSound(gPauseState.snd_select);

    FreeAnimation(gPauseState.caret_anim);

    FreeImage(gPauseState.title);
    FreeImage(gPauseState.caret);
}

INTERNAL void UpdatePause (float dt)
{
    if (IsKeyPressed(SDL_SCANCODE_ESCAPE) || IsButtonPressed(SDL_CONTROLLER_BUTTON_START)) Unpause();

    bool up     = (IsKeyPressed(SDL_SCANCODE_UP)   || IsKeyPressed(SDL_SCANCODE_W)     || IsButtonPressed(SDL_CONTROLLER_BUTTON_DPAD_UP)   || IsLeftStickUpPressed());
    bool down   = (IsKeyPressed(SDL_SCANCODE_DOWN) || IsKeyPressed(SDL_SCANCODE_S)     || IsButtonPressed(SDL_CONTROLLER_BUTTON_DPAD_DOWN) || IsLeftStickDownPressed());
    bool action = (IsKeyPressed(SDL_SCANCODE_Z)    || IsKeyPressed(SDL_SCANCODE_SPACE) || IsButtonPressed(SDL_CONTROLLER_BUTTON_A)         || IsButtonPressed(SDL_CONTROLLER_BUTTON_X));
    bool back   = (IsKeyPressed(SDL_SCANCODE_X)    || IsButtonPressed(SDL_CONTROLLER_BUTTON_B));

    if (up)
    {
        if (gPauseState.selected == 0) gPauseState.selected = PAUSE_ITEM_TOTAL-1;
        else gPauseState.selected--;
        ResetAnimation(gPauseState.caret_anim);
        PlaySound(gPauseState.snd_change);
    }
    if (down)
    {
        if (gPauseState.selected == PAUSE_ITEM_TOTAL-1) gPauseState.selected = 0;
        else gPauseState.selected++;
        ResetAnimation(gPauseState.caret_anim);
        PlaySound(gPauseState.snd_change);
    }
    if (action)
    {
        switch (gPauseState.selected)
        {
            case (PAUSE_ITEM_RETURN  ): Unpause(); break;
            case (PAUSE_ITEM_RETRY   ): PlaySound(gPauseState.snd_select); StartFade(FADE_SPECIAL, [](){ RetryGame(); }); break;
            case (PAUSE_ITEM_MENU    ): PlaySound(gPauseState.snd_select); StartFade(FADE_SPECIAL, [](){ EndGame(); }); break;
            case (PAUSE_ITEM_EXITGAME): PlaySound(gPauseState.snd_select); gWindow.running = false; break;
        }
    }
    if (back)
    {
        Unpause();
    }
}

INTERNAL void RenderPause (float dt)
{
    DrawFill(0.0f,0.0f,WINDOW_SCREEN_W,WINDOW_SCREEN_H, MakeColor(1,1,1));

    UpdateAnimation(gPauseState.caret_anim, dt);

    std::string return_text = "RESUME";
    std::string retry_text  = "RETRY";
    std::string menu_text   = "MENU";
    std::string exit_text   = "EXIT";

    float tx = roundf((float)WINDOW_SCREEN_W - gPauseState.title.w) / 2;
    float ty = 48;

    DrawImage(gPauseState.title, tx,ty);

    ty = WINDOW_SCREEN_H - 48;

    tx = roundf((float)WINDOW_SCREEN_W - GetTextWidth(gAppState.sfont, exit_text)) / 2;
    if (gPauseState.selected == PAUSE_ITEM_EXITGAME) DrawImage(gPauseState.caret, tx-12,ty, FLIP_NONE, GetAnimationClip(gPauseState.caret_anim));
    DrawText(gAppState.sfont, exit_text, tx,ty, MakeColor(0,0,0));
    ty -= 16;

    tx = roundf((float)WINDOW_SCREEN_W - GetTextWidth(gAppState.sfont, menu_text)) / 2;
    if (gPauseState.selected == PAUSE_ITEM_MENU) DrawImage(gPauseState.caret, tx-12,ty, FLIP_NONE, GetAnimationClip(gPauseState.caret_anim));
    DrawText(gAppState.sfont, menu_text, tx,ty, MakeColor(0,0,0));
    ty -= 16;

    tx = roundf((float)WINDOW_SCREEN_W - GetTextWidth(gAppState.sfont, retry_text)) / 2;
    if (gPauseState.selected == PAUSE_ITEM_RETRY) DrawImage(gPauseState.caret, tx-12,ty, FLIP_NONE, GetAnimationClip(gPauseState.caret_anim));
    DrawText(gAppState.sfont, retry_text, tx,ty, MakeColor(0,0,0));
    ty -= 16;

    tx = roundf((float)WINDOW_SCREEN_W - GetTextWidth(gAppState.sfont, return_text)) / 2;
    if (gPauseState.selected == PAUSE_ITEM_RETURN) DrawImage(gPauseState.caret, tx-12,ty, FLIP_NONE, GetAnimationClip(gPauseState.caret_anim));
    DrawText(gAppState.sfont, return_text, tx,ty, MakeColor(0,0,0));
    ty -= 16;
}

INTERNAL void Unpause ()
{
    PlaySound(gPauseState.snd_select);
    gAppState.state = APP_STATE_GAME;
    // printf("UNPAUSE!\n");
}

INTERNAL void Pause ()
{
    PlaySound(gPauseState.snd_select);
    gAppState.state = APP_STATE_PAUSE;
    gPauseState.selected = 0;
    // printf("PAUSE!\n");
}
