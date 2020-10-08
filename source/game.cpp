INTERNAL void InitGame ()
{
    InitBones();
    InitBreakableBlock();
    InitGui();
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
    QuitGui();
    FreeWorld();
}

INTERNAL void UpdateGame (float dt)
{
    if (IsKeyPressed(SDL_SCANCODE_ESCAPE) || IsButtonPressed(SDL_CONTROLLER_BUTTON_START)) Pause();

    if (!IsFading()) WorldTransitionIfOutOfBounds();

    UpdateMap(gWorld.current_map, dt);
    UpdateDog(gGameState.dog, dt);
    UpdateParticles(dt);
    UpdateCamera(dt);
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

INTERNAL void StartGame (std::string start_map, float start_x, float start_y, Flip start_flip, Music& music)
{
    gBoneCollectedIds.clear();
    gTempBoneCollectedIds.clear();

    LoadWorld(start_map);

    gGameState.dog.state    = DOG_STATE_IDLE;
    gGameState.dog.pos.x    = start_x;
    gGameState.dog.pos.y    = start_y;
    gGameState.dog.vel.x    = 0;
    gGameState.dog.vel.y    = 0;
    gGameState.dog.flip     = start_flip;
    gGameState.dog.grounded = true;

    gGameState.dog.start_state    = gGameState.dog.state;
    gGameState.dog.start_pos      = gGameState.dog.pos;
    gGameState.dog.start_vel      = gGameState.dog.vel;
    gGameState.dog.start_flip     = gGameState.dog.flip;
    gGameState.dog.start_grounded = gGameState.dog.grounded;

    gAppState.state = APP_STATE_GAME;

    PlayMusic(music);
}

INTERNAL void EndGame ()
{
    GoToMenu();
    FreeWorld();
}
