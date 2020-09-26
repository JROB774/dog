INTERNAL void InitGame ()
{
    LoadFont(gGameState.lfont, 24, 24, "lfont.bmp");
    LoadFont(gGameState.sfont, 12, 12, "sfont.bmp");
    InitBones();
    InitBreakableBlock();
    InitGui();
    InitBones();
    InitParticleSystem();
    CreateDog(gGameState.dog, START_X, START_Y);
    LoadWorld();
}

INTERNAL void QuitGame ()
{
    DeleteDog(gGameState.dog);
    QuitParticleSystem();
    DeleteBones();
    QuitGui();
    FreeWorld();
    FreeFont(gGameState.sfont);
    FreeFont(gGameState.lfont);
}

INTERNAL void UpdateGame (float dt)
{
    // Debug reset for the game if either F5 on keyboard or both shoulder buttons on gamepad are pressed.
    #if defined(BUILD_DEBUG)
    if (IsKeyPressed(SDL_SCANCODE_F5) || (IsButtonDown(SDL_CONTROLLER_BUTTON_LEFTSHOULDER) && IsButtonDown(SDL_CONTROLLER_BUTTON_RIGHTSHOULDER)))
    {
        gWindow.running = false;
        gWindow.reset = true;
    }
    #endif

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
