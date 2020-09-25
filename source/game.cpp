INTERNAL void InitGame ()
{
    LoadFont(gGameState.lfont, 24, 24, "lfont.bmp");
    LoadFont(gGameState.sfont, 12, 12, "sfont.bmp");

    LoadWorld();
    InitGui();
    InitBones();

    CreateDog(gGameState.dog, START_X, START_Y);
}

INTERNAL void QuitGame ()
{
    DeleteDog(gGameState.dog);
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
    DrawGui(dt);
}
