#ifndef WORLD_HPP
#define WORLD_HPP

GLOBAL constexpr const char* START_MAP  = "tutorial-main-start.bmp";
GLOBAL constexpr int         START_X    = 188;
GLOBAL constexpr int         START_Y    = 140;
GLOBAL constexpr Flip        START_FLIP = FLIP_HORZ;

GLOBAL constexpr int ROOM_W = 20;
GLOBAL constexpr int ROOM_H = 15;

GLOBAL struct World
{
    std::vector<std::vector<std::string>> rooms;
    Map current_map;
    int current_map_x; // In screens!
    int current_map_y; // In screens!
    std::string current_map_name;
    std::string current_zone;

} gWorld;

INTERNAL void LoadWorld (std::string start_map);
INTERNAL void FreeWorld ();

INTERNAL void WorldTransitionIfOutOfBounds ();

#endif /* WORLD_HPP */
