#ifndef MAP_HPP
#define MAP_HPP

GLOBAL constexpr int TILE_W      = 16;
GLOBAL constexpr int TILE_CLIP_W = 24;
GLOBAL constexpr int TILE_H      = 16;
GLOBAL constexpr int TILE_CLIP_H = 24;

typedef U8 TileType;
typedef U8 TileFlag;

GLOBAL constexpr TileType TILE_EMPTY = 0x00;
GLOBAL constexpr TileType TILE_SOLID = 0xFF;

struct Tile
{
    TileType type;
    TileFlag flag;
};

struct Map
{
    Image tileset;
    int w,h;
    Tile* tiles;
};

INTERNAL void LoadMap (Map& map, const char* file_name);
INTERNAL void FreeMap (Map& map);
INTERNAL void DrawMap (Map& map);

#endif /* MAP_HPP */
