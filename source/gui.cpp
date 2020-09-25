INTERNAL void InitGui ()
{
    LoadImage(gGui.splat, "splat.bmp");
}

INTERNAL void QuitGui ()
{
    FreeImage(gGui.splat);
}

INTERNAL void DrawGui ()
{
    DrawImage(gGui.splat, 0,0);

    std::string scollected = std::to_string(gWorld.current_map.bone_counter.small_bones_collected);
    while (scollected.length() < 3) scollected = "0" + scollected;
    std::string stotal = std::to_string(gWorld.current_map.bone_counter.small_bones_total);
    while (stotal.length() < 3) stotal = "0" + stotal;

    std::string stext = scollected + "/" + stotal;
    std::string ltext = std::to_string(gWorld.current_map.bone_counter.large_bones_collected) + "/" + std::to_string(gWorld.current_map.bone_counter.large_bones_total);

    DrawText(gGameState.sfont, stext, 2, 0, MakeColor(1,1,1));
    DrawText(gGameState.lfont, ltext, 0, 14, MakeColor(1,1,1));
}
