enum MenuItem
{
    MENU_ITEM_PLAYGAME,
    MENU_ITEM_CONTROLS,
    MENU_ITEM_SETTINGS,
    MENU_ITEM_EXITGAME,
    MENU_ITEM_TOTAL
};

enum MenuSettingsItem
{
    MENU_ITEM_SETTINGS_FULLSCREEN,
    MENU_ITEM_SETTINGS_SOUND,
    MENU_ITEM_SETTINGS_MUSIC,
    MENU_ITEM_SETTINGS_BACK,
    MENU_ITEM_SETTINGS_TOTAL
};

INTERNAL void InitMenu ()
{
    gMenuState.mode = MENU_MODE_MAINMENU;
    gMenuState.selected = 0;

    LoadImage(gMenuState.title, "title.bmp");
    LoadImage(gMenuState.help, "help.bmp");
    LoadImage(gMenuState.caret, "caret.bmp");

    LoadAnimation(gMenuState.caret_anim, "caret.anim");

    LoadSound(gMenuState.snd_change, "change.wav");
    LoadSound(gMenuState.snd_select, "select.wav");
}

INTERNAL void QuitMenu ()
{
    FreeSound(gMenuState.snd_change);
    FreeSound(gMenuState.snd_select);

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
        case (MENU_MODE_MAINMENU):
        {
            if (up)
            {
                if (gMenuState.selected == 0) gMenuState.selected = MENU_ITEM_TOTAL-1;
                else gMenuState.selected--;
                ResetAnimation(gMenuState.caret_anim);
                PlaySound(gMenuState.snd_change);
            }
            if (down)
            {
                if (gMenuState.selected == MENU_ITEM_TOTAL-1) gMenuState.selected = 0;
                else gMenuState.selected++;
                ResetAnimation(gMenuState.caret_anim);
                PlaySound(gMenuState.snd_change);
            }
            if (action)
            {
                PlaySound(gMenuState.snd_select);
                switch (gMenuState.selected)
                {
                    case (MENU_ITEM_PLAYGAME): gAppState.state = APP_STATE_GAME; break;
                    case (MENU_ITEM_CONTROLS): gMenuState.mode = MENU_MODE_CONTROLS; break;
                    case (MENU_ITEM_SETTINGS): gMenuState.mode = MENU_MODE_SETTINGS; gMenuState.selected = 0; break;
                    case (MENU_ITEM_EXITGAME): gWindow.running = false; break;
                }
            }
        } break;
        case (MENU_MODE_CONTROLS):
        {
            if (action) gMenuState.mode = MENU_MODE_MAINMENU;
        } break;
        case (MENU_MODE_SETTINGS):
        {
            if (up)
            {
                if (gMenuState.selected == 0) gMenuState.selected = MENU_ITEM_SETTINGS_TOTAL-1;
                else gMenuState.selected--;
                ResetAnimation(gMenuState.caret_anim);
                PlaySound(gMenuState.snd_change);
            }
            if (down)
            {
                if (gMenuState.selected == MENU_ITEM_SETTINGS_TOTAL-1) gMenuState.selected = 0;
                else gMenuState.selected++;
                ResetAnimation(gMenuState.caret_anim);
                PlaySound(gMenuState.snd_change);
            }
            if (action)
            {
                PlaySound(gMenuState.snd_select);
                switch (gMenuState.selected)
                {
                    case (MENU_ITEM_SETTINGS_FULLSCREEN): SetFullscreen((IsFullscreen()) ? false : true); break;
                    case (MENU_ITEM_SETTINGS_SOUND): SetSound((IsSoundOn()) ? false : true); break;
                    case (MENU_ITEM_SETTINGS_MUSIC): SetMusic((IsMusicOn()) ? false : true); break;
                    case (MENU_ITEM_SETTINGS_BACK): gMenuState.mode = MENU_MODE_MAINMENU; gMenuState.selected = MENU_ITEM_SETTINGS; break;
                }
            }
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
        case (MENU_MODE_MAINMENU):
        {
            tx = roundf((float)WINDOW_SCREEN_W - gMenuState.title.w) / 2;
            ty = 64;

            DrawImage(gMenuState.title, tx,ty);

            std::string play_text = "PLAY GAME";
            std::string controls_text = "CONTROLS";
            std::string options_text = "OPTIONS";
            std::string exit_text = "EXIT GAME";

            ty = WINDOW_SCREEN_H - 48;

            tx = roundf((float)WINDOW_SCREEN_W - GetTextWidth(gAppState.sfont, exit_text)) / 2;
            if (gMenuState.selected == MENU_ITEM_EXITGAME) DrawImage(gMenuState.caret, tx-12,ty, FLIP_NONE, GetAnimationClip(gMenuState.caret_anim));
            DrawText(gAppState.sfont, exit_text, tx,ty, MakeColor(0,0,0));
            ty -= 16;

            tx = roundf((float)WINDOW_SCREEN_W - GetTextWidth(gAppState.sfont, options_text)) / 2;
            if (gMenuState.selected == MENU_ITEM_SETTINGS) DrawImage(gMenuState.caret, tx-12,ty, FLIP_NONE, GetAnimationClip(gMenuState.caret_anim));
            DrawText(gAppState.sfont, options_text, tx,ty, MakeColor(0,0,0));
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
        case (MENU_MODE_SETTINGS):
        {
            tx = roundf((float)WINDOW_SCREEN_W - gMenuState.title.w) / 2;
            ty = 64;

            DrawImage(gMenuState.title, tx,ty);

            std::string fullscreen_text = std::string("FULLSCREEN ") + std::string((IsFullscreen()) ? "ON" : "OFF");
            std::string sound_text = std::string("SOUND ") + std::string((IsSoundOn()) ? "ON" : "OFF");
            std::string music_text = std::string("MUSIC ") + std::string((IsMusicOn()) ? "ON" : "OFF");
            std::string back_text = "BACK";

            ty = WINDOW_SCREEN_H - 48;

            tx = roundf((float)WINDOW_SCREEN_W - GetTextWidth(gAppState.sfont, back_text)) / 2;
            if (gMenuState.selected == MENU_ITEM_SETTINGS_BACK) DrawImage(gMenuState.caret, tx-12,ty, FLIP_NONE, GetAnimationClip(gMenuState.caret_anim));
            DrawText(gAppState.sfont, back_text, tx,ty, MakeColor(0,0,0));
            ty -= 16;

            tx = roundf((float)WINDOW_SCREEN_W - GetTextWidth(gAppState.sfont, music_text)) / 2;
            if (gMenuState.selected == MENU_ITEM_SETTINGS_MUSIC) DrawImage(gMenuState.caret, tx-12,ty, FLIP_NONE, GetAnimationClip(gMenuState.caret_anim));
            DrawText(gAppState.sfont, music_text, tx,ty, MakeColor(0,0,0));
            ty -= 16;

            tx = roundf((float)WINDOW_SCREEN_W - GetTextWidth(gAppState.sfont, sound_text)) / 2;
            if (gMenuState.selected == MENU_ITEM_SETTINGS_SOUND) DrawImage(gMenuState.caret, tx-12,ty, FLIP_NONE, GetAnimationClip(gMenuState.caret_anim));
            DrawText(gAppState.sfont, sound_text, tx,ty, MakeColor(0,0,0));
            ty -= 16;

            tx = roundf((float)WINDOW_SCREEN_W - GetTextWidth(gAppState.sfont, fullscreen_text)) / 2;
            if (gMenuState.selected == MENU_ITEM_SETTINGS_FULLSCREEN) DrawImage(gMenuState.caret, tx-12,ty, FLIP_NONE, GetAnimationClip(gMenuState.caret_anim));
            DrawText(gAppState.sfont, fullscreen_text, tx,ty, MakeColor(0,0,0));
            ty -= 16;
        } break;
    }
}
