#ifndef WORLD_HPP
#define WORLD_HPP

#if 1
GLOBAL constexpr const char* START_MAP = "main-test.bmp";
GLOBAL constexpr int         START_X   = (int)(3.5f * (float)TILE_W);
GLOBAL constexpr int         START_Y   = (int)(6.5f * (float)TILE_H);
#else
GLOBAL constexpr const char* START_MAP = "main-start.bmp";
GLOBAL constexpr int         START_X   = (int)(9.5f * (float)TILE_W);
GLOBAL constexpr int         START_Y   = (int)(9.5f * (float)TILE_H);
#endif

GLOBAL constexpr int ROOM_W = 20;
GLOBAL constexpr int ROOM_H = 15;

GLOBAL struct World
{
    std::vector<std::vector<std::string>> rooms;
    Map current_map;
    int current_map_x; // In screens!
    int current_map_y; // In screens!

} gWorld;

INTERNAL void LoadWorld ();
INTERNAL void FreeWorld ();

INTERNAL void WorldTransitionIfOutOfBounds ();

#endif /* WORLD_HPP */
