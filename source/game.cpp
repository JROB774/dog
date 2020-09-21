Map gTestMap;

INTERNAL void InitGame ()
{
    LoadMap(gTestMap, "assets/maptest.bmp");
}
INTERNAL void QuitGame ()
{
    FreeMap(gTestMap);
}

INTERNAL void UpdateGame (float dt)
{
    // ...
}

INTERNAL void RenderGame (float dt)
{
    DrawMap(gTestMap);
}
