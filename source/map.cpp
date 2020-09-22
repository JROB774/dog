#include <algorithm>

GLOBAL constexpr U32 TILE_EMPTY_COLOR = 0xFFFFFFFF;
GLOBAL constexpr U32 TILE_BACKG_COLOR = 0xFF808080;
GLOBAL constexpr U32 TILE_SOLID_COLOR = 0xFF000000;

GLOBAL constexpr int TILE_FLAG_W = 0x01;
GLOBAL constexpr int TILE_FLAG_S = 0x02;
GLOBAL constexpr int TILE_FLAG_E = 0x04;
GLOBAL constexpr int TILE_FLAG_N = 0x08;

GLOBAL constexpr int TILE_CLIP_W = 32;
GLOBAL constexpr int TILE_CLIP_H = 32;

INTERNAL bool TileEntityCollision (Vec2 pos, Rect bounds, int tx, int ty, Rect& intersection)
{
    // Entity Bounds
    float x1 = pos.x + bounds.x;
    float y1 = pos.y + bounds.y;
    float x2 = x1    + bounds.w;
    float y2 = y1    + bounds.h;
    // Tile Bounds
    float x3 = tx * TILE_W;
    float y3 = ty * TILE_H;
    float x4 = x3 + TILE_W;
    float y4 = y3 + TILE_H;
    // Intersection
    float x5 = MAX(x1, x3);
    float y5 = MAX(y1, y3);
    float x6 = MIN(x2, x4);
    float y6 = MIN(y2, y4);

    intersection.x = x5;
    intersection.y = y5;
    intersection.w = x6 - x5;
    intersection.h = y6 - y5;

    return ((x5 < x6) && (y5 < y6));
}

INTERNAL void LoadMap (Map& map, const char* file_name)
{
    LoadImage(map.tileset, "assets/tilestd.bmp"); // @Hardcoded!

    SDL_Surface* surface = SDL_LoadBMP(file_name);
    ASSERT(surface);

    // We want the data to be formatted as 32-bit RGBA so we know how to access the pixels.
    ASSERT(surface->format->BytesPerPixel == 4);

    map.w = surface->w;
    map.h = surface->h;

    map.tiles = (Tile*)malloc(map.w*map.h * sizeof(Tile));
    ASSERT(map.tiles);

    // Seed the random tiles for the map using the map's name so that they remain consistent!
    unsigned int random_seed = 0;
    for (int i=0; i<strlen(file_name); ++i) random_seed += file_name[i];
    srand(random_seed);

    U32* pixels = (U32*)surface->pixels;
    for (int iy=0; iy<map.h; ++iy)
    {
        for (int ix=0; ix<map.w; ++ix)
        {
            int index = (iy*map.w+ix);
            U32 pixel = pixels[index];

            Tile* tile = &map.tiles[index];

            switch (pixel)
            {
                case (TILE_EMPTY_COLOR): tile->type = TILE_EMPTY; break;
                case (TILE_BACKG_COLOR): tile->type = TILE_BACKG; break;
                case (TILE_SOLID_COLOR): tile->type = TILE_SOLID; break;
            }

            if (tile->type != TILE_EMPTY)
            {
                tile->variant = 0;
                tile->offset = 0;

                switch (tile->type)
                {
                    case (TILE_SOLID): tile->variant = rand() % (int)((map.tileset.h/TILE_CLIP_H)-1); break;
                    case (TILE_BACKG): tile->variant =          (int)((map.tileset.h/TILE_CLIP_H)-1); break;
                }

                switch (tile->type)
                {
                    case (TILE_SOLID):
                    {
                        if ((ix == (      0)) || (pixels[(iy)*map.w+(ix-1)] == TILE_SOLID_COLOR)) tile->offset |= TILE_FLAG_W;
                        if ((iy == (map.h-1)) || (pixels[(iy+1)*map.w+(ix)] == TILE_SOLID_COLOR)) tile->offset |= TILE_FLAG_S;
                        if ((ix == (map.w-1)) || (pixels[(iy)*map.w+(ix+1)] == TILE_SOLID_COLOR)) tile->offset |= TILE_FLAG_E;
                        if ((iy == (      0)) || (pixels[(iy-1)*map.w+(ix)] == TILE_SOLID_COLOR)) tile->offset |= TILE_FLAG_N;
                    } break;
                    case (TILE_BACKG):
                    {
                        if ((ix == (      0)) || (pixels[(iy)*map.w+(ix-1)] != TILE_EMPTY_COLOR)) tile->offset |= TILE_FLAG_W;
                        if ((iy == (map.h-1)) || (pixels[(iy+1)*map.w+(ix)] != TILE_EMPTY_COLOR)) tile->offset |= TILE_FLAG_S;
                        if ((ix == (map.w-1)) || (pixels[(iy)*map.w+(ix+1)] != TILE_EMPTY_COLOR)) tile->offset |= TILE_FLAG_E;
                        if ((iy == (      0)) || (pixels[(iy-1)*map.w+(ix)] != TILE_EMPTY_COLOR)) tile->offset |= TILE_FLAG_N;
                    } break;
                }
            }
        }
    }

    SDL_FreeSurface(surface);
}

INTERNAL void FreeMap (Map& map)
{
    FreeImage(map.tileset);
    free(map.tiles);
    map.w = 0, map.h = 0;
}

INTERNAL void DrawMap (Map& map)
{
    SDL_Rect clip = { 0,0,TILE_CLIP_W,TILE_CLIP_H };

    DrawFill(0.0f,0.0f, (float)(map.w*TILE_W),(float)(map.h*TILE_H), MakeColor(1,1,1));

    // Draw the background tiles.
    for (int iy=0; iy<map.h; ++iy)
    {
        for (int ix=0; ix<map.w; ++ix)
        {
            Tile* tile = &map.tiles[iy*map.w+ix];
            if (tile->type == TILE_BACKG)
            {
                clip.x = tile->offset * TILE_CLIP_W, clip.y = tile->variant * TILE_CLIP_H;
                DrawImage(map.tileset, (float)((ix*TILE_W)+(TILE_W/2)-(TILE_CLIP_W/2)), (float)((iy*TILE_H)+(TILE_H/2)-(TILE_CLIP_H/2)), FLIP_NONE, &clip);
            }
        }
    }
    // Draw the solid tiles.
    for (int iy=0; iy<map.h; ++iy)
    {
        for (int ix=0; ix<map.w; ++ix)
        {
            Tile* tile = &map.tiles[iy*map.w+ix];
            if (tile->type == TILE_SOLID)
            {
                clip.x = tile->offset * TILE_CLIP_W, clip.y = tile->variant * TILE_CLIP_H;
                DrawImage(map.tileset, (float)((ix*TILE_W)+(TILE_W/2)-(TILE_CLIP_W/2)), (float)((iy*TILE_H)+(TILE_H/2)-(TILE_CLIP_H/2)), FLIP_NONE, &clip);
            }
        }
    }
}
