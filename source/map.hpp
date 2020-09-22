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

INTERNAL bool TileEntityCollision (Vec2 pos, Rect bounds, int tx, int ty, Rect& intersection);

INTERNAL void LoadMap (Map& map, const char* file_name);
INTERNAL void FreeMap (Map& map);

INTERNAL void DrawMapBackg (Map& map);
INTERNAL void DrawMapFront (Map& map);

#endif /* MAP_HPP */
