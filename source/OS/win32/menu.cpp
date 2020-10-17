enum MenuItem
{
    MENU_ITEM_PLAYGAME,
    MENU_ITEM_BADGES,
    MENU_ITEM_SETTINGS,
    MENU_ITEM_CREDITS,
    MENU_ITEM_EXITGAME,
    MENU_ITEM_TOTAL
};

enum MenuSettingsItem
{
    MENU_ITEM_SETTINGS_FULLSCREEN,
    MENU_ITEM_SETTINGS_SOUND,
    MENU_ITEM_SETTINGS_MUSIC,
    MENU_ITEM_SETTINGS_RESET,
    MENU_ITEM_SETTINGS_BACK,
    MENU_ITEM_SETTINGS_TOTAL
};

INTERNAL void UpdateMenuMain (float dt, bool up, bool down, bool right, bool left, bool action, bool back)
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
            case (MENU_ITEM_PLAYGAME): gMenuState.mode = MENU_MODE_PLAYGAME; gMenuState.selected = 0; break;
            case (MENU_ITEM_BADGES  ): gMenuState.mode = MENU_MODE_BADGES;                            break;
            case (MENU_ITEM_SETTINGS): gMenuState.mode = MENU_MODE_SETTINGS; gMenuState.selected = 0; break;
            case (MENU_ITEM_CREDITS ): gMenuState.mode = MENU_MODE_CREDITS;                           break;
            case (MENU_ITEM_EXITGAME): gWindow.running = false;                                       break;
        }
    }
    if (back || IsKeyPressed(SDL_SCANCODE_ESCAPE))
    {
        gWindow.running = false;
    }
}
INTERNAL void RenderMenuMain (float dt)
{
    float tx = roundf((float)WINDOW_SCREEN_W - gMenuState.title.w) / 2;
    float ty = 24;

    DrawImage(gMenuState.title, tx,ty);

    std::string playgame_text  = "PLAY GAME";
    std::string badges_text    = "ACHIEVEMENTS";
    std::string options_text   = "OPTIONS";
    std::string credits_text   = "CREDITS";
    std::string exit_text      = "EXIT GAME";

    ty = WINDOW_SCREEN_H - 48;

    tx = roundf((float)WINDOW_SCREEN_W - GetTextWidth(gAppState.sfont, exit_text)) / 2;
    if (gMenuState.selected == MENU_ITEM_EXITGAME) DrawImage(gMenuState.caret, tx-12,ty, FLIP_NONE, GetAnimationClip(gMenuState.caret_anim));
    DrawText(gAppState.sfont, exit_text, tx,ty, MakeColor(0,0,0));
    ty -= 16;

    tx = roundf((float)WINDOW_SCREEN_W - GetTextWidth(gAppState.sfont, credits_text)) / 2;
    if (gMenuState.selected == MENU_ITEM_CREDITS) DrawImage(gMenuState.caret, tx-12,ty, FLIP_NONE, GetAnimationClip(gMenuState.caret_anim));
    DrawText(gAppState.sfont, credits_text, tx,ty, MakeColor(0,0,0));
    ty -= 16;

    tx = roundf((float)WINDOW_SCREEN_W - GetTextWidth(gAppState.sfont, options_text)) / 2;
    if (gMenuState.selected == MENU_ITEM_SETTINGS) DrawImage(gMenuState.caret, tx-12,ty, FLIP_NONE, GetAnimationClip(gMenuState.caret_anim));
    DrawText(gAppState.sfont, options_text, tx,ty, MakeColor(0,0,0));
    ty -= 16;

    tx = roundf((float)WINDOW_SCREEN_W - GetTextWidth(gAppState.sfont, badges_text)) / 2;
    if (gMenuState.selected == MENU_ITEM_BADGES) DrawImage(gMenuState.caret, tx-12,ty, FLIP_NONE, GetAnimationClip(gMenuState.caret_anim));
    DrawText(gAppState.sfont, badges_text, tx,ty, MakeColor(0,0,0));
    ty -= 16;

    tx = roundf((float)WINDOW_SCREEN_W - GetTextWidth(gAppState.sfont, playgame_text)) / 2;
    if (gMenuState.selected == MENU_ITEM_PLAYGAME) DrawImage(gMenuState.caret, tx-12,ty, FLIP_NONE, GetAnimationClip(gMenuState.caret_anim));
    DrawText(gAppState.sfont, playgame_text, tx,ty, MakeColor(0,0,0));
    ty -= 16;
}

INTERNAL void UpdateMenuSettings (float dt, bool up, bool down, bool right, bool left, bool action, bool back)
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
    if (left)
    {
        if (gMenuState.selected == MENU_ITEM_SETTINGS_SOUND)
        {
            if (GetSoundVolume() > 0.0f)
            {
                SetSoundVolume(GetSoundVolume()-0.1f);
                PlaySound(gMenuState.snd_select);
            }
        }
        if (gMenuState.selected == MENU_ITEM_SETTINGS_MUSIC)
        {
            if (GetMusicVolume() > 0.0f)
            {
                SetMusicVolume(GetMusicVolume()-0.1f);
                PlaySound(gMenuState.snd_select);
            }
        }
    }
    if (right)
    {
        if (gMenuState.selected == MENU_ITEM_SETTINGS_SOUND)
        {
            if (GetSoundVolume() < 1.0f)
            {
                SetSoundVolume(GetSoundVolume()+0.1f);
                PlaySound(gMenuState.snd_select);
            }
        }
        if (gMenuState.selected == MENU_ITEM_SETTINGS_MUSIC)
        {
            if (GetMusicVolume() < 1.0f)
            {
                SetMusicVolume(GetMusicVolume()+0.1f);
                PlaySound(gMenuState.snd_select);
            }
        }
    }
    if (action)
    {
        PlaySound(gMenuState.snd_select);
        switch (gMenuState.selected)
        {
            case (MENU_ITEM_SETTINGS_FULLSCREEN): SetFullscreen((IsFullscreen()) ? false : true); break;
            case (MENU_ITEM_SETTINGS_RESET): ResetSettings(); break;
            case (MENU_ITEM_SETTINGS_BACK):
            {
                SaveSettings();
                gMenuState.mode = MENU_MODE_MAINMENU;
                gMenuState.selected = MENU_ITEM_SETTINGS;
            } break;
        }
    }
    if (back || IsKeyPressed(SDL_SCANCODE_ESCAPE))
    {
        PlaySound(gMenuState.snd_select);
        SaveSettings();
        gMenuState.mode = MENU_MODE_MAINMENU;
        gMenuState.selected = MENU_ITEM_SETTINGS;
    }
}
INTERNAL void RenderMenuSettings (float dt)
{
    float tx = roundf((float)WINDOW_SCREEN_W - gMenuState.title.w) / 2;
    float ty = 24;

    DrawImage(gMenuState.title, tx,ty);

    std::string fullscreen_text = std::string("FULLSCREEN ") + std::string((IsFullscreen()) ? "ON" : "OFF");
    std::string sound_text = "SOUND ";
    std::string music_text = "MUSIC ";
    std::string reset_text = "RESET OPTIONS";
    std::string delete_text = "DELETE SAVE GAME";
    std::string back_text = "BACK";

    ty = WINDOW_SCREEN_H - 48;

    tx = roundf((float)WINDOW_SCREEN_W - GetTextWidth(gAppState.sfont, back_text)) / 2;
    if (gMenuState.selected == MENU_ITEM_SETTINGS_BACK) DrawImage(gMenuState.caret, tx-12,ty, FLIP_NONE, GetAnimationClip(gMenuState.caret_anim));
    DrawText(gAppState.sfont, back_text, tx,ty, MakeColor(0,0,0));
    ty -= 16;

    tx = roundf((float)WINDOW_SCREEN_W - GetTextWidth(gAppState.sfont, reset_text)) / 2;
    if (gMenuState.selected == MENU_ITEM_SETTINGS_RESET) DrawImage(gMenuState.caret, tx-12,ty, FLIP_NONE, GetAnimationClip(gMenuState.caret_anim));
    DrawText(gAppState.sfont, reset_text, tx,ty, MakeColor(0,0,0));
    ty -= 16;

    tx = roundf((float)WINDOW_SCREEN_W - (GetTextWidth(gAppState.sfont, music_text) + gMenuState.bar.w)) / 2;
    if (gMenuState.selected == MENU_ITEM_SETTINGS_MUSIC) DrawImage(gMenuState.caret, tx-12,ty, FLIP_NONE, GetAnimationClip(gMenuState.caret_anim));
    DrawText(gAppState.sfont, music_text, tx,ty, MakeColor(0,0,0));
    tx += GetTextWidth(gAppState.sfont, music_text);
    SDL_Rect music_bar_clip = { 0, 0, (int)gMenuState.bar.w, 12 };
    music_bar_clip.y = (int)roundf((gMenuState.bar.h-12) * GetMusicVolume());
    DrawImage(gMenuState.bar, tx,ty, FLIP_NONE, &music_bar_clip);
    ty -= 16;

    tx = roundf((float)WINDOW_SCREEN_W - (GetTextWidth(gAppState.sfont, sound_text) + gMenuState.bar.w)) / 2;
    if (gMenuState.selected == MENU_ITEM_SETTINGS_SOUND) DrawImage(gMenuState.caret, tx-12,ty, FLIP_NONE, GetAnimationClip(gMenuState.caret_anim));
    DrawText(gAppState.sfont, sound_text, tx,ty, MakeColor(0,0,0));
    tx += GetTextWidth(gAppState.sfont, sound_text);
    SDL_Rect sound_bar_clip = { 0, 0, (int)gMenuState.bar.w, 12 };
    sound_bar_clip.y = (int)roundf((gMenuState.bar.h-12) * GetSoundVolume());
    DrawImage(gMenuState.bar, tx,ty, FLIP_NONE, &sound_bar_clip);
    ty -= 16;

    tx = roundf((float)WINDOW_SCREEN_W - GetTextWidth(gAppState.sfont, fullscreen_text)) / 2;
    if (gMenuState.selected == MENU_ITEM_SETTINGS_FULLSCREEN) DrawImage(gMenuState.caret, tx-12,ty, FLIP_NONE, GetAnimationClip(gMenuState.caret_anim));
    DrawText(gAppState.sfont, fullscreen_text, tx,ty, MakeColor(0,0,0));
    ty -= 16;
}
