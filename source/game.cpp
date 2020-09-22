INTERNAL void InitGame ()
{
    LoadMap(gGameState.map, "assets/maptest.bmp");
    CreateDog(gGameState.dog, 40, 100);
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
    DrawMap(gGameState.map);
    DrawDog(gGameState.dog, dt);
}
