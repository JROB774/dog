INTERNAL void InitGame ()
{
    LoadWorld();
    CreateDog(gGameState.dog, START_X, START_Y);
}

INTERNAL void QuitGame ()
{
    FreeWorld();
}

INTERNAL void UpdateGame (float dt)
{
    WorldTransitionIfOutOfBounds();
	UpdateDog(gGameState.dog, dt);
}

INTERNAL void RenderGame (float dt)
{
    DrawMapBackg(gWorld.current_map);
    DrawDog(gGameState.dog, dt);
    DrawMapFront(gWorld.current_map);
}
