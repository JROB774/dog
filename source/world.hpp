#ifndef WORLD_HPP
#define WORLD_HPP

#if 0
GLOBAL constexpr const char* START_MAP = "main-test-test.bmp";
GLOBAL constexpr int         START_X   = (int)(3.5f * (float)TILE_W);
GLOBAL constexpr int         START_Y   = (int)(6.5f * (float)TILE_H)+4;
#else
GLOBAL constexpr const char* START_MAP = "main-test-start.bmp";
GLOBAL constexpr int         START_X   = (int)(9.5f * (float)TILE_W);
GLOBAL constexpr int         START_Y   = (int)(9.5f * (float)TILE_H)+4;
#endif

GLOBAL constexpr int ROOM_W = 20;
GLOBAL constexpr int ROOM_H = 15;

GLOBAL struct World
{
    std::vector<std::vector<std::string>> rooms;
    Map current_map;
    int current_map_x; // In screens!
    int current_map_y; // In screens!
    // Maps bone counters to the different zones.
    std::string current_zone;
    std::map<std::string, BoneCounter> bones;

} gWorld;

INTERNAL void LoadWorld ();
INTERNAL void FreeWorld ();

INTERNAL void WorldTransitionIfOutOfBounds ();

INTERNAL BoneCounter& GetWorldBoneCounter ();

#endif /* WORLD_HPP */
