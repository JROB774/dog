GLOBAL constexpr U32 TILE_EMPTY_COLOR = 0xFFFFFFFF;
GLOBAL constexpr U32 TILE_SOLID_COLOR = 0xFF000000;

GLOBAL constexpr TileFlag TILE_FLAG_W = 0x01;
GLOBAL constexpr TileFlag TILE_FLAG_S = 0x02;
GLOBAL constexpr TileFlag TILE_FLAG_E = 0x04;
GLOBAL constexpr TileFlag TILE_FLAG_N = 0x00;

INTERNAL void LoadMap (Map& map, const char* file_name)
{
    LoadImage(map.tileset, "assets/tilestd.bmp"); // @Hardcoded!

    SDL_Surface* surface = SDL_LoadBMP(file_name);
    ASSERT(surface);

    // We want the data to be formatted as 32-bit RGBA so we know how to access the pixels.
    ASSERT(surface->format->BytesPerPixel == 4);

    map.w = surface->w;
    map.h = surface->h;

    map.tiles = MALLOC(Tile, map.w*map.h);
    ASSERT(map.tiles);

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
                case (TILE_SOLID_COLOR): tile->type = TILE_SOLID; break;
            }

            // Special case for TILE_SOLID type tiles where we check the surrounding tiles
            // and set flags for each of the directions, determining the correct graphic.
            tile->flag = 0x00;
            if (tile->type == TILE_SOLID)
            {
                // @Incomplete: ...
            }
        }
    }

    SDL_FreeSurface(surface);
}

INTERNAL void FreeMap (Map& map)
{
    FreeImage(map.tileset);
    FREE(map.tiles);
    map.w = 0, map.h = 0;
}

INTERNAL void DrawMap (Map& map)
{
    for (int iy=0; iy<map.h; ++iy)
    {
        for (int ix=0; ix<map.w; ++ix)
        {
            Tile* tile = &map.tiles[iy*map.w+ix];
            switch (tile->type)
            {
                case (TILE_EMPTY): DrawFill(ix*TILE_W, iy*TILE_H, TILE_W,TILE_H, MakeColor(1,1,1)); break;
                case (TILE_SOLID): DrawFill(ix*TILE_W, iy*TILE_H, TILE_W,TILE_H, MakeColor(0,0,0)); break;
            }
        }
    }
}
