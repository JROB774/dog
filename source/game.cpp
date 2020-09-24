INTERNAL void InitGame ()
{
    LoadWorld();
    CreateDog(gGameState.dog, START_X, START_Y);
}

INTERNAL void QuitGame ()
{
    DeleteDog(gGameState.dog);
    FreeWorld();
}

INTERNAL void UpdateGame (float dt)
{
    WorldTransitionIfOutOfBounds();
	UpdateDog(gGameState.dog, dt);
}

INTERNAL void RenderGame (float dt)
{
    BeginCamera();
    DrawMapBackg(gWorld.current_map);
    DrawMapEntities(gWorld.current_map);
    DrawDog(gGameState.dog, dt);
    DrawMapSpikes(gWorld.current_map);
    DrawMapFront(gWorld.current_map);
    EndCamera();
}
