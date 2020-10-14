INTERNAL void InitApplication ()
{
    LoadFont(gAppState.lfont, 24, 24, "lfont.bmp");
    LoadFont(gAppState.sfont, 12, 12, "sfont.bmp");

    LoadData();

    InitFade ();
    InitMenu ();
    InitGame ();
    InitPause();
    InitStats();

    GoToMenu();
}

INTERNAL void QuitApplication ()
{
    SaveSettings();
    SaveData();

    QuitStats();
    QuitPause();
    QuitGame ();
    QuitMenu ();
    QuitFade ();

    FreeFont(gAppState.sfont);
    FreeFont(gAppState.lfont);
}

INTERNAL void UpdateApplication (float dt)
{
    if (IsKeyPressed(SDL_SCANCODE_F) || IsKeyPressed(SDL_SCANCODE_F11)){SetFullscreen(!IsFullscreen());}
    
    if (!IsFading())
    {
        switch (gAppState.state)
        {
            case (APP_STATE_MENU ): UpdateMenu (dt); break;
            case (APP_STATE_GAME ): UpdateGame (dt); break;
            case (APP_STATE_PAUSE): UpdatePause(dt); break;
            case (APP_STATE_STATS): UpdateStats(dt); break;
        }
    }
}

INTERNAL void RenderApplication (float dt)
{
    switch (gAppState.state)
    {
        case (APP_STATE_MENU ): RenderMenu (dt); break;
        case (APP_STATE_GAME ): RenderGame (dt); break;
        case (APP_STATE_PAUSE): RenderPause(dt); break;
        case (APP_STATE_STATS): RenderStats(dt); break;
    }

    RenderFade(dt);
}
