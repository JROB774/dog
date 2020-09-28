INTERNAL void InitGui ()
{
    LoadImage(gGui.splat, "splat.bmp");
    gGui.current_x = 0.0f;
}

INTERNAL void QuitGui ()
{
    FreeImage(gGui.splat);
}

INTERNAL void DrawGui (float dt)
{
    DrawImage(gGui.splat, gGui.current_x,0);

    // Pad the values with zeroes so that they are always three digits long.
    std::string collected = std::to_string(GetBoneCollectedCount());
    while (collected.length() < 3) collected = "0" + collected;
    std::string total = std::to_string(GetBoneTotalCount());
    while (total.length() < 3) total = "0" + total;
    std::string text = collected + "/" + total;
    if (GetBoneCollectedCount() >= GetBoneTotalCount()) text += "!";
    DrawText(gAppState.sfont, text, gGui.current_x+15, 1, MakeColor(1,1,1));
}

/*
INTERNAL void DisplayGui ()
{
    gGui.target_x = 0;
    gGui.timer = 2.5; // Seconds!
}
*/
