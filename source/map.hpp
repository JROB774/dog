#ifndef MAP_HPP
#define MAP_HPP

GLOBAL constexpr int TILE_W = 16;
GLOBAL constexpr int TILE_H = 16;

enum TileType { TILE_EMPTY, TILE_BACKG, TILE_SOLID };

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
