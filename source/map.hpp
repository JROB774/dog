#ifndef MAP_HPP
#define MAP_HPP

GLOBAL constexpr int TILE_W = 16;
GLOBAL constexpr int TILE_H = 16;

enum TileType { TILE_EMPTY, TILE_BACKG, TILE_SOLID };

struct Tile
{
    TileType type;
    int xoff,yoff; // In tiles!
};

struct Map
{
    Image tileset;
    int w,h;
    std::vector<Tile> tiles;
    // Entities
    std::vector<Spike> spikes;
};

INTERNAL bool TileEntityCollision (Vec2 pos, Rect bounds, int tx, int ty, Rect& intersection);

INTERNAL void LoadMap (Map& map, std::string file_name);
INTERNAL void FreeMap (Map& map);

INTERNAL void DrawMapBackg    (Map& map);
INTERNAL void DrawMapEntities (Map& map);
INTERNAL void DrawMapSpikes   (Map& map);
INTERNAL void DrawMapFront    (Map& map);

#endif /* MAP_HPP */
