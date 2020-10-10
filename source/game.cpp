INTERNAL void InitGame ()
{
    InitBones();
    InitBreakableBlock();
    InitGui();
    InitBadges();
    InitBones();
    InitCrushBoi();
    InitSpitBoy();
    InitWalkBoy();
    InitChargeBoy();
    InitParticleSystem();
    CreateDog(gGameState.dog, 0, 0, FLIP_NONE);

    LoadMusic(gGameState.mus_fanfare,   "fanfare.wav"  );
    LoadMusic(gGameState.mus_game,      "game.wav"     );
    LoadMusic(gGameState.mus_tutorial,  "tutorial.wav" );
    LoadMusic(gGameState.mus_challenge, "challenge.wav");

    gGameState.challenge_locked = true;
    gGameState.doing_win_sequence = false;
}

INTERNAL void QuitGame ()
{
    FreeMusic(gGameState.mus_fanfare  );
    FreeMusic(gGameState.mus_game     );
    FreeMusic(gGameState.mus_tutorial );
    FreeMusic(gGameState.mus_challenge);

    DeleteDog(gGameState.dog);
    QuitParticleSystem();
    QuitCrushBoi();
    QuitSpitBoy();
    QuitWalkBoy();
    QuitChargeBoy();
    DeleteBreakableBlock();
    DeleteBones();
    QuitBadges();
    QuitGui();
    FreeWorld();
}

INTERNAL void UpdateGame (float dt)
{
    if (!gGameState.doing_win_sequence && (IsKeyPressed(SDL_SCANCODE_ESCAPE) || IsButtonPressed(SDL_CONTROLLER_BUTTON_START))) Pause();

    if (!IsFading()) WorldTransitionIfOutOfBounds();

    UpdateMap(gWorld.current_map, dt);
    UpdateDog(gGameState.dog, dt);
    UpdateParticles(dt);
    UpdateCamera(dt);

    DoWinSequence();
}

INTERNAL void RenderGame (float dt)
{
    BeginCamera();
    DrawMapBackground(gWorld.current_map);
    DrawMapBackEntities(gWorld.current_map, dt);
    DrawDog(gGameState.dog, dt);
    DrawParticles(dt);
    DrawMapFrontEntities(gWorld.current_map, dt);
    DrawMapFrontTiles(gWorld.current_map);
    DrawMapForeground(gWorld.current_map);
    EndCamera();
    DrawGui(dt);
}

INTERNAL void StartGame (GameMode game_mode, bool retry)
{
    gBoneCollectedIds.clear();
    gTempBoneCollectedIds.clear();

    gGameState.mode = game_mode;

    LoadWorld(GAME_MODE_INFO[gGameState.mode].map);

    gGameState.dog.state    = DOG_STATE_IDLE;
    gGameState.dog.pos.x    = GAME_MODE_INFO[gGameState.mode].pos.x;
    gGameState.dog.pos.y    = GAME_MODE_INFO[gGameState.mode].pos.y;
    gGameState.dog.vel.x    = 0;
    gGameState.dog.vel.y    = 0;
    gGameState.dog.flip     = GAME_MODE_INFO[gGameState.mode].flip;
    gGameState.dog.grounded = true;
    gGameState.dog.deaths   = 0;

    gGameState.dog.start_state    = gGameState.dog.state;
    gGameState.dog.start_pos      = gGameState.dog.pos;
    gGameState.dog.start_vel      = gGameState.dog.vel;
    gGameState.dog.start_flip     = gGameState.dog.flip;
    gGameState.dog.start_grounded = gGameState.dog.grounded;

    gGameState.start_time = SDL_GetTicks();

    gAppState.state = APP_STATE_GAME;

    // Prevents the music being reset when retrying, it's much nicer if it just carries on playing.
    if (!retry) PlayMusic(*GAME_MODE_INFO[gGameState.mode].music);
}

INTERNAL void EndGame ()
{
    gGameState.doing_win_sequence = false;
    GoToMenu();
    FreeWorld();
}

INTERNAL void RetryGame ()
{
    FreeWorld();
    StartGame(gGameState.mode, true);
}

INTERNAL void StartWinSequence ()
{
    gGameState.doing_win_sequence = true;
    gGameState.dog.vel.x = 0.0f;
    PlayMusic(gGameState.mus_fanfare, 1);
}

INTERNAL void DoWinSequence ()
{
    if (!gGameState.doing_win_sequence) return;
    if (!IsMusicPlaying()) EndWinSequence();
}

INTERNAL void EndWinSequence ()
{
    float elapsed_seconds = (float)(SDL_GetTicks() - gGameState.start_time) / 1000.0f;

    // Handle unlocking badges!
                                                                          gBadges.unlocked_complete[gGameState.mode] = true; // COMPLETE
    if (gBoneCollectedIds.size() == gCurrentZoneBoneTotal)                gBadges.unlocked_collect [gGameState.mode] = true; // COLLECT
    if (gGameState.dog.deaths == 0)                                       gBadges.unlocked_ironman [gGameState.mode] = true; // IRONMAN
    if (elapsed_seconds <= GAME_MODE_INFO[gGameState.mode].speedrun_time) gBadges.unlocked_speedrun[gGameState.mode] = true; // SPEEDRUN

    StartFade(FADE_SPECIAL, [](){ EndGame(); });
}
