Map gTestMap;

INTERNAL void InitGame ()
{
    LoadMap(gTestMap, "assets/maptest.bmp");
    DogCreate();
}
INTERNAL void QuitGame ()
{
    FreeMap(gTestMap);
}

INTERNAL void UpdateGame (float dt)
{
    // ...
	DogUpdate(dt);
}

INTERNAL void RenderGame (float dt)
{
    DrawMap(gTestMap);
    DogDraw();
}
