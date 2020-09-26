enum MenuItem
{
    MENU_ITEM_PLAYGAME,
    MENU_ITEM_CONTROLS,
    MENU_ITEM_EXITGAME,
    MENU_ITEM_TOTAL
};

INTERNAL void InitMenu ()
{
    gMenuState.mode = MENU_MODE_MAIN;
    gMenuState.selected = MENU_ITEM_PLAYGAME;

    LoadImage(gMenuState.title, "title.bmp");
    LoadImage(gMenuState.help, "help.bmp");
    LoadImage(gMenuState.caret, "caret.bmp");

    LoadAnimation(gMenuState.caret_anim, "caret.anim");
}

INTERNAL void QuitMenu ()
{
    FreeAnimation(gMenuState.caret_anim);

    FreeImage(gMenuState.title);
    FreeImage(gMenuState.help);
    FreeImage(gMenuState.caret);
}

INTERNAL void UpdateMenu (float dt)
{
    bool up     = (IsKeyPressed(SDL_SCANCODE_UP)   || IsKeyPressed(SDL_SCANCODE_W) || IsButtonPressed(SDL_CONTROLLER_BUTTON_DPAD_UP)   || IsLeftStickUpPressed());
    bool down   = (IsKeyPressed(SDL_SCANCODE_DOWN) || IsKeyPressed(SDL_SCANCODE_S) || IsButtonPressed(SDL_CONTROLLER_BUTTON_DPAD_DOWN) || IsLeftStickDownPressed());
    bool action = (IsKeyPressed(SDL_SCANCODE_Z)    || IsKeyPressed(SDL_SCANCODE_X) || IsKeyPressed(SDL_SCANCODE_SPACE)                 || IsButtonPressed(SDL_CONTROLLER_BUTTON_A) || IsButtonPressed(SDL_CONTROLLER_BUTTON_X));

    switch (gMenuState.mode)
    {
        case (MENU_MODE_MAIN):
        {
            if (up   && gMenuState.selected > 0)                 { gMenuState.selected--; ResetAnimation(gMenuState.caret_anim); }
            if (down && gMenuState.selected < MENU_ITEM_TOTAL-1) { gMenuState.selected++; ResetAnimation(gMenuState.caret_anim); }
            if (action)
            {
                switch (gMenuState.selected)
                {
                    case (MENU_ITEM_PLAYGAME): gAppState.state = APP_STATE_GAME; break;
                    case (MENU_ITEM_CONTROLS): gMenuState.mode = MENU_MODE_CONTROLS; break;
                    case (MENU_ITEM_EXITGAME): gWindow.running = false; break;
                }
            }
        } break;
        case (MENU_MODE_CONTROLS):
        {
            if (action) gMenuState.mode = MENU_MODE_MAIN;
        } break;
    }
}

INTERNAL void RenderMenu (float dt)
{
    DrawFill(0.0f,0.0f,WINDOW_SCREEN_W,WINDOW_SCREEN_H, MakeColor(1,1,1));

    UpdateAnimation(gMenuState.caret_anim, dt);

    float tx,ty;

    switch (gMenuState.mode)
    {
        case (MENU_MODE_MAIN):
        {
            tx = roundf((float)WINDOW_SCREEN_W - gMenuState.title.w) / 2;
            ty = 64;

            DrawImage(gMenuState.title, tx,ty);

            std::string play_text = "PLAY GAME";
            std::string controls_text = "CONTROLS";
            std::string exit_text = "EXIT GAME";

            ty = WINDOW_SCREEN_H - 48;

            tx = roundf((float)WINDOW_SCREEN_W - GetTextWidth(gAppState.sfont, exit_text)) / 2;
            if (gMenuState.selected == MENU_ITEM_EXITGAME) DrawImage(gMenuState.caret, tx-12,ty, FLIP_NONE, GetAnimationClip(gMenuState.caret_anim));
            DrawText(gAppState.sfont, exit_text, tx,ty, MakeColor(0,0,0));
            ty -= 16;

            tx = roundf((float)WINDOW_SCREEN_W - GetTextWidth(gAppState.sfont, controls_text)) / 2;
            if (gMenuState.selected == MENU_ITEM_CONTROLS) DrawImage(gMenuState.caret, tx-12,ty, FLIP_NONE, GetAnimationClip(gMenuState.caret_anim));
            DrawText(gAppState.sfont, controls_text, tx,ty, MakeColor(0,0,0));
            ty -= 16;

            tx = roundf((float)WINDOW_SCREEN_W - GetTextWidth(gAppState.sfont, play_text)) / 2;
            if (gMenuState.selected == MENU_ITEM_PLAYGAME) DrawImage(gMenuState.caret, tx-12,ty, FLIP_NONE, GetAnimationClip(gMenuState.caret_anim));
            DrawText(gAppState.sfont, play_text, tx,ty, MakeColor(0,0,0));
            ty -= 16;
        } break;
        case (MENU_MODE_CONTROLS):
        {
            tx = roundf((float)WINDOW_SCREEN_W - gMenuState.help.w) / 2;
            ty = roundf((float)WINDOW_SCREEN_H - gMenuState.help.h) / 2;

            DrawImage(gMenuState.help, tx,ty);
        } break;
    }
}
