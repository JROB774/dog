INTERNAL void InitGame ()
{
    LoadMap(gGameState.map, "maptest.bmp");
    CreateDog(gGameState.dog, 48, 100);
}

INTERNAL void QuitGame ()
{
    FreeMap(gGameState.map);
}

INTERNAL void UpdateGame (float dt)
{
	UpdateDog(gGameState.dog, dt);
}

INTERNAL void RenderGame (float dt)
{
    DrawMapBackg(gGameState.map);
    DrawDog(gGameState.dog, dt);
    DrawMapFront(gGameState.map);
}
