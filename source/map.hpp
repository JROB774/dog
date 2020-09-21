#ifndef MAP_HPP
#define MAP_HPP

typedef int TileType;

GLOBAL constexpr TileType TILE_EMPTY = 0;
GLOBAL constexpr TileType TILE_BACK2 = 1;
GLOBAL constexpr TileType TILE_BACK1 = 2;
GLOBAL constexpr TileType TILE_SOLID = 3;

GLOBAL constexpr int TILE_W = 16;
GLOBAL constexpr int TILE_H = 16;

struct Tile
{
    TileType type;
    int offset;
    int variant;
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
