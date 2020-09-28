INTERNAL void InitGame ()
{
    InitBones();
    InitBreakableBlock();
    InitGui();
    InitBones();
    InitParticleSystem();
    CreateDog(gGameState.dog, START_X, START_Y);
    // LoadWorld(START_MAP);
}

INTERNAL void QuitGame ()
{
    DeleteDog(gGameState.dog);
    QuitParticleSystem();
    DeleteBreakableBlock();
    DeleteBones();
    QuitGui();
    FreeWorld();
}

INTERNAL void UpdateGame (float dt)
{
    if (IsKeyPressed(SDL_SCANCODE_ESCAPE) || IsButtonPressed(SDL_CONTROLLER_BUTTON_START)) Pause();

    WorldTransitionIfOutOfBounds();
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
    EndCamera();
    DrawGui(dt);
}

INTERNAL void StartGame ()
{
    LoadData();
    LoadWorld(START_MAP);

    gGameState.dog.state    = DOG_STATE_IDLE;
    gGameState.dog.pos.x    = START_X;
    gGameState.dog.pos.y    = START_Y;
    gGameState.dog.vel.x    = 0;
    gGameState.dog.vel.y    = 0;
    gGameState.dog.flip     = FLIP_NONE;
    gGameState.dog.grounded = true;

    gGameState.dog.start_state    = gGameState.dog.state;
    gGameState.dog.start_pos      = gGameState.dog.pos;
    gGameState.dog.start_vel      = gGameState.dog.vel;
    gGameState.dog.start_flip     = gGameState.dog.flip;
    gGameState.dog.start_grounded = gGameState.dog.grounded;

    gAppState.state = APP_STATE_GAME;
    LoadData();
}

INTERNAL void EndGame ()
{
    gAppState.state = APP_STATE_MENU;
    SaveData();
    FreeWorld();
}
