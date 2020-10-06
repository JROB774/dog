INTERNAL void InitApplication ()
{
    LoadFont(gAppState.lfont, 24, 24, "lfont.bmp");
    LoadFont(gAppState.sfont, 12, 12, "sfont.bmp");

    InitFade ();
    InitMenu ();
    InitGame ();
    InitPause();

    GoToMenu();
}

INTERNAL void QuitApplication ()
{
    SaveSettings();

    QuitPause();
    QuitGame ();
    QuitMenu ();
    QuitFade ();

    FreeFont(gAppState.sfont);
    FreeFont(gAppState.lfont);
}

INTERNAL void UpdateApplication (float dt)
{
    /*
    // Debug reset for the game if either F5 on keyboard or both shoulder buttons on gamepad are pressed.
    #if defined(BUILD_DEBUG)
    if (IsKeyPressed(SDL_SCANCODE_F5) || (IsButtonDown(SDL_CONTROLLER_BUTTON_LEFTSHOULDER) && IsButtonDown(SDL_CONTROLLER_BUTTON_RIGHTSHOULDER)))
    {
        gWindow.running = false;
        gWindow.reset = true;
    }
    #endif
    */

    if (!IsFading())
    {
        switch (gAppState.state)
        {
            case (APP_STATE_MENU ): UpdateMenu (dt); break;
            case (APP_STATE_GAME ): UpdateGame (dt); break;
            case (APP_STATE_PAUSE): UpdatePause(dt); break;
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
    }

    RenderFade(dt);
}
