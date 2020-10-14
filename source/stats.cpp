INTERNAL void InitStats ()
{
    LoadImage(gStatsState.back, "statsback.bmp");
}

INTERNAL void QuitStats ()
{
    FreeImage(gStatsState.back);
}

INTERNAL void UpdateStats (float dt)
{
    bool action = (IsKeyPressed(SDL_SCANCODE_Z     ) || IsButtonPressed(SDL_CONTROLLER_BUTTON_A    ) || IsButtonPressed(SDL_CONTROLLER_BUTTON_X));
    bool back   = (IsKeyPressed(SDL_SCANCODE_X     ) || IsButtonPressed(SDL_CONTROLLER_BUTTON_B    )                                            );
    bool start  = (IsKeyPressed(SDL_SCANCODE_ESCAPE) || IsButtonPressed(SDL_CONTROLLER_BUTTON_START)                                            );

    if (action || back || start)
    {
        // HACK: We don't call GoToMenu() because we don't want the music to play again as it's already playgin!
        StartFade(FADE_SPECIAL, []()
        {
            gMenuState.mode = MENU_MODE_MAINMENU;
            gMenuState.selected = 0;
            gAppState.state = APP_STATE_MENU;
        });
    }
}

INTERNAL void RenderStats (float dt)
{
    for (int i=0; i<BADGE_TYPE_TOTAL; ++i) UpdateAnimation(gBadges.anim[i], dt);

    DrawImage(gStatsState.back, 0,0);

    // Format and create the bones string.
    std::string collected = std::to_string(GetBoneCollectedCount());
    std::string total = std::to_string(GetBoneTotalCount());
    while (collected.length() < 3) collected = "0" + collected;
    while (total.length()     < 3) total = "0" + total;
    std::string bone_text = collected + "/" + total;
    float bone_half_width = GetTextWidth(gAppState.sfont, bone_text)/2; // Calculate the width before the "!" so it doesn't impact placement.
    if (GetBoneCollectedCount() >= GetBoneTotalCount()) bone_text += "!";

    // Format and create the time string.
    std::string minutes = std::to_string((int)gGameState.timer / 60);
    std::string seconds = std::to_string((int)gGameState.timer % 60);
    while (minutes.length() < 2) minutes = "0" + minutes;
    while (seconds.length() < 2) seconds = "0" + seconds;
    std::string time_text = minutes + ":" + seconds;
    float time_half_width = GetTextWidth(gAppState.sfont, time_text)/2; // Calculate the width before the "!" so it doesn't impact placement.
    if (gGameState.timer <= GAME_MODE_INFO[gGameState.mode].speedrun_time) time_text += "!";

    // Draw the bones string.
    DrawText(gAppState.sfont, bone_text, 87-bone_half_width, 117, MakeColor(0,0,0));

    // Draw the time string.
    DrawText(gAppState.sfont, time_text, 242-time_half_width, 117, MakeColor(0,0,0));

    // Draw the achievements for the current game mode that was played.
    DrawImage(gBadges.badges,  42, 175, FLIP_NONE, GetAnimationClip((gBadges.unlocked_complete[gGameState.mode]) ? gBadges.anim[BADGE_TYPE_UNLOCKED_COMPLETE] : gBadges.anim[BADGE_TYPE_LOCKED_COMPLETE]));
    DrawImage(gBadges.badges, 110, 175, FLIP_NONE, GetAnimationClip((gBadges.unlocked_collect [gGameState.mode]) ? gBadges.anim[BADGE_TYPE_UNLOCKED_COLLECT ] : gBadges.anim[BADGE_TYPE_LOCKED_COLLECT ]));
    DrawImage(gBadges.badges, 178, 175, FLIP_NONE, GetAnimationClip((gBadges.unlocked_ironman [gGameState.mode]) ? gBadges.anim[BADGE_TYPE_UNLOCKED_IRONMAN ] : gBadges.anim[BADGE_TYPE_LOCKED_IRONMAN ]));
    DrawImage(gBadges.badges, 246, 175, FLIP_NONE, GetAnimationClip((gBadges.unlocked_speedrun[gGameState.mode]) ? gBadges.anim[BADGE_TYPE_UNLOCKED_SPEEDRUN] : gBadges.anim[BADGE_TYPE_LOCKED_SPEEDRUN]));
}

INTERNAL void GoToStats ()
{
    gAppState.state = APP_STATE_STATS;
    PlayMusic(gMenuState.music); // We're stealing this from the menu! :)
}
