INTERNAL void InitGame ()
{
    LoadFont(gGameState.lfont, 24, 24, "lfont.bmp");
    LoadFont(gGameState.sfont, 12, 12, "sfont.bmp");
    InitBones();
    InitBreakableBlock();
    LoadWorld();
    InitGui();
    InitBones();
    InitParticleSystem();
    CreateDog(gGameState.dog, START_X, START_Y);
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
    WorldTransitionIfOutOfBounds();
	UpdateDog(gGameState.dog, dt);

    if (IsKeyPressed(SDL_SCANCODE_RETURN))
    {
        CreateParticles(PARTICLE_TYPE_TEST0, (int)gGameState.dog.pos.x,(int)gGameState.dog.pos.y,(int)gGameState.dog.pos.x+24,(int)gGameState.dog.pos.y+24, 4,10);
    }

    UpdateParticles(dt);
}

INTERNAL void RenderGame (float dt)
{
    BeginCamera();
    DrawMapBackg(gWorld.current_map);
    DrawMapEntities(gWorld.current_map);
    DrawDog(gGameState.dog, dt);
    DrawParticles(dt);
    DrawMapSpikes(gWorld.current_map);
    DrawMapFront(gWorld.current_map);
    EndCamera();
    DrawGui(dt);
}
