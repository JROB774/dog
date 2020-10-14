enum MenuItem
{
    MENU_ITEM_PLAYGAME,
    MENU_ITEM_BADGES,
    MENU_ITEM_SETTINGS,
    MENU_ITEM_CREDITS,
    MENU_ITEM_EXITGAME,
    MENU_ITEM_TOTAL
};

enum MenuPlayGameItem
{
    MENU_ITEM_PLAYGAME_NORMAL,
    MENU_ITEM_PLAYGAME_CHALLENGE,
    MENU_ITEM_PLAYGAME_TUTORIAL,
    MENU_ITEM_PLAYGAME_BACK,
    MENU_ITEM_PLAYGAME_TOTAL
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

INTERNAL void InitMenu ()
{
    gMenuState.mode = MENU_MODE_MAINMENU;
    gMenuState.selected = 0;

    LoadImage(gMenuState.title, "title.bmp");
    LoadImage(gMenuState.bar, "bar.bmp");
    LoadImage(gMenuState.caret, "caret.bmp");
    LoadImage(gMenuState.credit, "credit.bmp");

    LoadAnimation(gMenuState.caret_anim, "caret.anim");

    LoadSound(gMenuState.snd_change, "change.wav");
    LoadSound(gMenuState.snd_select, "select.wav");

    LoadMusic(gMenuState.music, "menu.wav");
}

INTERNAL void QuitMenu ()
{
    FreeMusic(gMenuState.music);

    FreeSound(gMenuState.snd_change);
    FreeSound(gMenuState.snd_select);

    FreeAnimation(gMenuState.caret_anim);

    FreeImage(gMenuState.title);
    FreeImage(gMenuState.bar);
    FreeImage(gMenuState.caret);
    FreeImage(gMenuState.credit);
}

INTERNAL void UpdateMenu (float dt)
{
    bool up     = (IsKeyPressed(SDL_SCANCODE_UP)    || IsKeyPressed(SDL_SCANCODE_W)      || IsButtonPressed(SDL_CONTROLLER_BUTTON_DPAD_UP)    || IsLeftStickUpPressed());
    bool down   = (IsKeyPressed(SDL_SCANCODE_DOWN)  || IsKeyPressed(SDL_SCANCODE_S)      || IsButtonPressed(SDL_CONTROLLER_BUTTON_DPAD_DOWN)  || IsLeftStickDownPressed());
    bool right  = (IsKeyPressed(SDL_SCANCODE_RIGHT) || IsKeyPressed(SDL_SCANCODE_D)      || IsButtonPressed(SDL_CONTROLLER_BUTTON_DPAD_RIGHT) || IsLeftStickRightPressed());
    bool left   = (IsKeyPressed(SDL_SCANCODE_LEFT)  || IsKeyPressed(SDL_SCANCODE_A)      || IsButtonPressed(SDL_CONTROLLER_BUTTON_DPAD_LEFT)  || IsLeftStickLeftPressed());
    bool action = (IsKeyPressed(SDL_SCANCODE_Z)     || IsKeyPressed(SDL_SCANCODE_SPACE)  || IsButtonPressed(SDL_CONTROLLER_BUTTON_A)          || IsButtonPressed(SDL_CONTROLLER_BUTTON_X));
    bool back   = (IsKeyPressed(SDL_SCANCODE_X)     || IsKeyPressed(SDL_SCANCODE_ESCAPE) || IsButtonPressed(SDL_CONTROLLER_BUTTON_B));

    switch (gMenuState.mode)
    {
        case (MENU_MODE_MAINMENU): UpdateMenuMain    (dt, up, down, right, left, action, back); break;
        case (MENU_MODE_PLAYGAME): UpdateMenuPlayGame(dt, up, down, right, left, action, back); break;
        case (MENU_MODE_BADGES  ): UpdateMenuBadges  (dt, up, down, right, left, action, back); break;
        case (MENU_MODE_SETTINGS): UpdateMenuSettings(dt, up, down, right, left, action, back); break;
        case (MENU_MODE_CREDITS ): UpdateMenuCredits (dt, up, down, right, left, action, back); break;
    }
}

INTERNAL void RenderMenu (float dt)
{
    DrawFill(0.0f,0.0f,WINDOW_SCREEN_W,WINDOW_SCREEN_H, MakeColor(1,1,1));

    UpdateAnimation(gMenuState.caret_anim, dt);

    switch (gMenuState.mode)
    {
        case (MENU_MODE_MAINMENU): RenderMenuMain    (dt); break;
        case (MENU_MODE_PLAYGAME): RenderMenuPlayGame(dt); break;
        case (MENU_MODE_BADGES  ): RenderMenuBadges  (dt); break;
        case (MENU_MODE_SETTINGS): RenderMenuSettings(dt); break;
        case (MENU_MODE_CREDITS ): RenderMenuCredits (dt); break;
    }
}

INTERNAL void GoToMenu ()
{
    gMenuState.mode = MENU_MODE_MAINMENU;
    gMenuState.selected = 0;
    gAppState.state = APP_STATE_MENU;
    PlayMusic(gMenuState.music);
}

INTERNAL void UpdateMenuMain (float dt, bool up, bool down, bool right, bool left, bool action, bool back)
{
    // If the player hasn't beaten normal mode then challenge mode is locked!
    // bool challenge_locked = (!gBadges.unlocked_complete[GAME_MODE_NORMAL]);

    if (up)
    {
        if (gMenuState.selected == 0) gMenuState.selected = MENU_ITEM_TOTAL-1;
        else gMenuState.selected--;
        // if (gMenuState.selected == MENU_ITEM_PLAYCHALLENGE && challenge_locked) gMenuState.selected--; // Move again if on the locked challenge.
        ResetAnimation(gMenuState.caret_anim);
        PlaySound(gMenuState.snd_change);
    }
    if (down)
    {
        if (gMenuState.selected == MENU_ITEM_TOTAL-1) gMenuState.selected = 0;
        else gMenuState.selected++;
        // if (gMenuState.selected == MENU_ITEM_PLAYCHALLENGE && challenge_locked) gMenuState.selected++; // Move again if on the locked challenge.
        ResetAnimation(gMenuState.caret_anim);
        PlaySound(gMenuState.snd_change);
    }
    if (action)
    {
        PlaySound(gMenuState.snd_select);
        switch (gMenuState.selected)
        {
            // case (MENU_ITEM_PLAYGAME     ):                        StartFade(FADE_SPECIAL, [](){ StartGame(GAME_MODE_NORMAL   ); }); break;
            // case (MENU_ITEM_PLAYCHALLENGE): if (!challenge_locked) StartFade(FADE_SPECIAL, [](){ StartGame(GAME_MODE_CHALLENGE); }); break;
            // case (MENU_ITEM_PLAYTUT      ):                        StartFade(FADE_SPECIAL, [](){ StartGame(GAME_MODE_TUTORIAL ); }); break;
            case (MENU_ITEM_PLAYGAME): gMenuState.mode = MENU_MODE_PLAYGAME; gMenuState.selected = 0; break;
            case (MENU_ITEM_BADGES  ): gMenuState.mode = MENU_MODE_BADGES;                            break;
            case (MENU_ITEM_SETTINGS): gMenuState.mode = MENU_MODE_SETTINGS; gMenuState.selected = 0; break;
            case (MENU_ITEM_CREDITS ): gMenuState.mode = MENU_MODE_CREDITS;                           break;
            case (MENU_ITEM_EXITGAME): gWindow.running = false;                                       break;
        }
    }
    if (back)
    {
        PlaySound(gMenuState.snd_select);
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

INTERNAL void UpdateMenuPlayGame (float dt, bool up, bool down, bool right, bool left, bool action, bool back)
{
    // If the player hasn't beaten normal mode then challenge mode is locked!
    bool challenge_locked = (!gBadges.unlocked_complete[GAME_MODE_NORMAL]);

    if (up)
    {
        if (gMenuState.selected == 0) gMenuState.selected = MENU_ITEM_PLAYGAME_TOTAL-1;
        else gMenuState.selected--;
        if (gMenuState.selected == MENU_ITEM_PLAYGAME_CHALLENGE && challenge_locked) gMenuState.selected--; // Move again if on the locked challenge.
        ResetAnimation(gMenuState.caret_anim);
        PlaySound(gMenuState.snd_change);
    }
    if (down)
    {
        if (gMenuState.selected == MENU_ITEM_PLAYGAME_TOTAL-1) gMenuState.selected = 0;
        else gMenuState.selected++;
        if (gMenuState.selected == MENU_ITEM_PLAYGAME_CHALLENGE && challenge_locked) gMenuState.selected++; // Move again if on the locked challenge.
        ResetAnimation(gMenuState.caret_anim);
        PlaySound(gMenuState.snd_change);
    }
    if (action)
    {
        PlaySound(gMenuState.snd_select);
        switch (gMenuState.selected)
        {
            case (MENU_ITEM_PLAYGAME_NORMAL   ):                        StartFade(FADE_SPECIAL, [](){ StartGame(GAME_MODE_NORMAL   ); }); break;
            case (MENU_ITEM_PLAYGAME_CHALLENGE): if (!challenge_locked) StartFade(FADE_SPECIAL, [](){ StartGame(GAME_MODE_CHALLENGE); }); break;
            case (MENU_ITEM_PLAYGAME_TUTORIAL ):                        StartFade(FADE_SPECIAL, [](){ StartGame(GAME_MODE_TUTORIAL ); }); break;
            case (MENU_ITEM_PLAYGAME_BACK     ): gMenuState.mode = MENU_MODE_MAINMENU; gMenuState.selected = MENU_ITEM_PLAYGAME;          break;
        }
    }
    if (back)
    {
        PlaySound(gMenuState.snd_select);
        gMenuState.mode = MENU_MODE_MAINMENU;
        gMenuState.selected = MENU_ITEM_PLAYGAME;
    }
}
INTERNAL void RenderMenuPlayGame (float dt)
{
    // If the player hasn't beaten normal mode then challenge mode is locked!
    bool challenge_locked = (!gBadges.unlocked_complete[GAME_MODE_NORMAL]);

    float tx = roundf((float)WINDOW_SCREEN_W - gMenuState.title.w) / 2;
    float ty = 24;

    DrawImage(gMenuState.title, tx,ty);

    std::string normal_text    = "NORMAL";
    std::string challenge_text = "CHALLENGE";
    std::string tutorial_text  = "TUTORIAL";
    std::string back_text      = "BACK";

    ty = WINDOW_SCREEN_H - 56;

    tx = roundf((float)WINDOW_SCREEN_W - GetTextWidth(gAppState.sfont, back_text)) / 2;
    if (gMenuState.selected == MENU_ITEM_PLAYGAME_BACK) DrawImage(gMenuState.caret, tx-12,ty, FLIP_NONE, GetAnimationClip(gMenuState.caret_anim));
    DrawText(gAppState.sfont, back_text, tx,ty, MakeColor(0,0,0));
    ty -= 16;

    tx = roundf((float)WINDOW_SCREEN_W - GetTextWidth(gAppState.sfont, tutorial_text)) / 2;
    if (gMenuState.selected == MENU_ITEM_PLAYGAME_TUTORIAL) DrawImage(gMenuState.caret, tx-12,ty, FLIP_NONE, GetAnimationClip(gMenuState.caret_anim));
    DrawText(gAppState.sfont, tutorial_text, tx,ty, MakeColor(0,0,0));
    ty -= 16;

    tx = roundf((float)WINDOW_SCREEN_W - GetTextWidth(gAppState.sfont, challenge_text)) / 2;
    if (gMenuState.selected == MENU_ITEM_PLAYGAME_CHALLENGE) DrawImage(gMenuState.caret, tx-12,ty, FLIP_NONE, GetAnimationClip(gMenuState.caret_anim));
    DrawText(gAppState.sfont, challenge_text, tx,ty, (challenge_locked) ? MakeColor(0.75f,0.75f,0.75f) : MakeColor(0,0,0));
    ty -= 16;

    tx = roundf((float)WINDOW_SCREEN_W - GetTextWidth(gAppState.sfont, normal_text)) / 2;
    if (gMenuState.selected == MENU_ITEM_PLAYGAME_NORMAL) DrawImage(gMenuState.caret, tx-12,ty, FLIP_NONE, GetAnimationClip(gMenuState.caret_anim));
    DrawText(gAppState.sfont, normal_text, tx,ty, MakeColor(0,0,0));
    ty -= 16;
}

INTERNAL void UpdateMenuBadges (float dt, bool up, bool down, bool right, bool left, bool action, bool back)
{
    if (action || back)
    {
        gMenuState.mode = MENU_MODE_MAINMENU;
        PlaySound(gMenuState.snd_select);
        return;
    }

    // Navigate the badge screen with the cursor..
    if (up   ) if (gBadges.cursor_y > 0) { gBadges.cursor_y--; PlaySound(gMenuState.snd_change); ResetAnimation(gBadges.caret_anim); }
    if (down ) if (gBadges.cursor_y < 1) { gBadges.cursor_y++; PlaySound(gMenuState.snd_change); ResetAnimation(gBadges.caret_anim); }
    if (right) if (gBadges.cursor_x < 3) { gBadges.cursor_x++; PlaySound(gMenuState.snd_change); ResetAnimation(gBadges.caret_anim); }
    if (left ) if (gBadges.cursor_x > 0) { gBadges.cursor_x--; PlaySound(gMenuState.snd_change); ResetAnimation(gBadges.caret_anim); }
}
INTERNAL void RenderMenuBadges (float dt)
{
    for (int i=0; i<BADGE_TYPE_TOTAL; ++i) UpdateAnimation(gBadges.anim[i], dt);

    DrawImage(gBadges.background, 0, 0);

    // COMPLETE
    DrawImage(gBadges.badges,  42,  63, FLIP_NONE, GetAnimationClip((gBadges.unlocked_complete[0]) ? gBadges.anim[BADGE_TYPE_UNLOCKED_COMPLETE] : gBadges.anim[BADGE_TYPE_LOCKED_COMPLETE]));
    DrawImage(gBadges.badges,  42, 109, FLIP_NONE, GetAnimationClip((gBadges.unlocked_complete[1]) ? gBadges.anim[BADGE_TYPE_UNLOCKED_COMPLETE] : gBadges.anim[BADGE_TYPE_LOCKED_COMPLETE]));
    // COLLECT
    DrawImage(gBadges.badges, 110,  63, FLIP_NONE, GetAnimationClip((gBadges.unlocked_collect [0]) ? gBadges.anim[BADGE_TYPE_UNLOCKED_COLLECT ] : gBadges.anim[BADGE_TYPE_LOCKED_COLLECT ]));
    DrawImage(gBadges.badges, 110, 109, FLIP_NONE, GetAnimationClip((gBadges.unlocked_collect [1]) ? gBadges.anim[BADGE_TYPE_UNLOCKED_COLLECT ] : gBadges.anim[BADGE_TYPE_LOCKED_COLLECT ]));
    // IRONMAN
    DrawImage(gBadges.badges, 178,  63, FLIP_NONE, GetAnimationClip((gBadges.unlocked_ironman [0]) ? gBadges.anim[BADGE_TYPE_UNLOCKED_IRONMAN ] : gBadges.anim[BADGE_TYPE_LOCKED_IRONMAN ]));
    DrawImage(gBadges.badges, 178, 109, FLIP_NONE, GetAnimationClip((gBadges.unlocked_ironman [1]) ? gBadges.anim[BADGE_TYPE_UNLOCKED_IRONMAN ] : gBadges.anim[BADGE_TYPE_LOCKED_IRONMAN ]));
    // SPEEDRUN
    DrawImage(gBadges.badges, 246,  63, FLIP_NONE, GetAnimationClip((gBadges.unlocked_speedrun[0]) ? gBadges.anim[BADGE_TYPE_UNLOCKED_SPEEDRUN] : gBadges.anim[BADGE_TYPE_LOCKED_SPEEDRUN]));
    DrawImage(gBadges.badges, 246, 109, FLIP_NONE, GetAnimationClip((gBadges.unlocked_speedrun[1]) ? gBadges.anim[BADGE_TYPE_UNLOCKED_SPEEDRUN] : gBadges.anim[BADGE_TYPE_LOCKED_SPEEDRUN]));

    float cx = 0.0f;
    float cy = 0.0f;

    switch (gBadges.cursor_x)
    {
    case (0): cx =  42; break;
    case (1): cx = 110; break;
    case (2): cx = 178; break;
    case (3): cx = 246; break;
    }
    switch (gBadges.cursor_y)
    {
    case (0): cy =  63; break;
    case (1): cy = 109; break;
    }

    cx -= 4;
    cy -= 4;

    UpdateAnimation(gBadges.caret_anim, dt);
    DrawImage(gBadges.caret, cx,cy, FLIP_NONE, GetAnimationClip(gBadges.caret_anim));

    float tx = WINDOW_SCREEN_W / 2;
    float ty = 215;

    tx -= GetTextWidth(gAppState.sfont, gBadges.description[gBadges.cursor_x][gBadges.cursor_y]) / 2;
    ty -= GetTextHeight(gAppState.sfont, gBadges.description[gBadges.cursor_x][gBadges.cursor_y]) / 2;

    DrawText(gAppState.sfont, gBadges.description[gBadges.cursor_x][gBadges.cursor_y], tx, ty, MakeColor(0,0,0));
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
    if (back)
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

INTERNAL void UpdateMenuCredits (float dt, bool up, bool down, bool right, bool left, bool action, bool back)
{
    if (action || back)
    {
        gMenuState.mode = MENU_MODE_MAINMENU;
        PlaySound(gMenuState.snd_select);
        return;
    }
}
INTERNAL void RenderMenuCredits (float dt)
{
    DrawImage(gMenuState.credit, 0,0);
}
