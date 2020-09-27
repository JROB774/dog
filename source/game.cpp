INTERNAL void InitGame ()
{
    InitBones();
    InitBreakableBlock();
    InitGui();
    InitBones();
    InitParticleSystem();
    CreateDog(gGameState.dog, START_X, START_Y);
    LoadWorld(START_MAP);
}

INTERNAL void QuitGame ()
{
    DeleteDog(gGameState.dog);
    QuitParticleSystem();
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
    DrawMapBackg(gWorld.current_map);
    DrawMapEntities(gWorld.current_map, dt);
    DrawDog(gGameState.dog, dt);
    DrawParticles(dt);
    DrawMapSpikes(gWorld.current_map);
    DrawMapFront(gWorld.current_map);
    EndCamera();
    DrawGui(dt);
}

INTERNAL void StartGame ()
{
    gAppState.state = APP_STATE_GAME;
    LoadData();
}

INTERNAL void EndGame ()
{
    gAppState.state = APP_STATE_MENU;
    SaveData();
}
