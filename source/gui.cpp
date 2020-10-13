INTERNAL void InitGui ()
{
    LoadImage(gGui.splat, "splat.bmp");
}

INTERNAL void QuitGui ()
{
    FreeImage(gGui.splat);
}

INTERNAL void DrawGui (float dt)
{
    DrawImage(gGui.splat, 0,0);

    // We pad all values with zeroes so that they are always the same length.

    // Format and display the current bones collected.
    std::string collected = std::to_string(GetBoneCollectedCount());
    std::string total = std::to_string(GetBoneTotalCount());

    while (collected.length() < 3) collected = "0" + collected;
    while (total.length()     < 3) total = "0" + total;

    std::string bone_text = collected + "/" + total;
    if (GetBoneCollectedCount() >= GetBoneTotalCount()) bone_text += "!";

    DrawText(gAppState.sfont, bone_text, 15, 1, MakeColor(1,1,1));

    // Format and display the current timer.
    std::string minutes = std::to_string((int)gGameState.timer / 60);
    std::string seconds = std::to_string((int)gGameState.timer % 60);

    while (minutes.length() < 2) minutes = "0" + minutes;
    while (seconds.length() < 2) seconds = "0" + seconds;

    std::string time_text = minutes + ":" + seconds;

    DrawText(gAppState.sfont, time_text, 15, 15, MakeColor(1,1,1));
}
