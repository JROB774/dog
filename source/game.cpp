INTERNAL void InitGame ()
{
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
}

INTERNAL void UpdateGame (float dt)
{
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
