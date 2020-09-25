INTERNAL void InitGui ()
{
    LoadImage(gGui.splat, "splat.bmp");

    // gGui.current_x = -128.0f;
    // gGui.target_x = -128.0f;

    // gGui.timer = 0.0f;

    gGui.current_x = 0.0f;
}

INTERNAL void QuitGui ()
{
    FreeImage(gGui.splat);
}

INTERNAL void DrawGui (float dt)
{
    /*
    gGui.timer -= dt;
    if (gGui.timer <= 0.0f) gGui.target_x = -128.0f;
    else gGui.target_x = 0.0f;

    gGui.current_x = Lerp(gGui.current_x, gGui.target_x, dt*10);
    */

    DrawImage(gGui.splat, gGui.current_x,0);

    // Pad the values with zeroes so that they are always three digits long.
    std::string scollected = std::to_string(gWorld.current_map.bone_counter.small_bones_collected);
    while (scollected.length() < 3) scollected = "0" + scollected;
    std::string stotal = std::to_string(gWorld.current_map.bone_counter.small_bones_total);
    while (stotal.length() < 3) stotal = "0" + stotal;

    std::string stext = scollected + "/" + stotal;
    DrawText(gGameState.sfont, stext, gGui.current_x+2, 0, MakeColor(1,1,1));

    // std::string ltext = std::to_string(gWorld.current_map.bone_counter.large_bones_collected) + "/" + std::to_string(gWorld.current_map.bone_counter.large_bones_total);
    // DrawText(gGameState.lfont, ltext, gGui.current_x+0, 14, MakeColor(1,1,1));
}

/*
INTERNAL void DisplayGui ()
{
    gGui.target_x = 0;
    gGui.timer = 2.5; // Seconds!
}
*/
