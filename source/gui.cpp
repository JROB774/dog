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
    // Hard-coded that the bone counter doesn't display in the tutorial or hub zones as there's no bones.
    if (gWorld.current_zone == "tutorial" || gWorld.current_zone == "hub") return;

    if (IsFading() && gFade.state == FADE_OUT) return;

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
