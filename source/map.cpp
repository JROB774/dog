////////////////////////////////////////////////////////////////////////////////
//
// HOW TILESETS WORK:
//
// The first two rows of tiles are the different directional pieces that make
// up the solid tile. Row one and two are simply alternate graphics to add
// some more visual variance to the solid tiles. The third row are different
// graphics randomly selected for the inner-solid tiles. These graphics have a
// small random change of appearing instead of the default inner-solid tiles.
// The final row is the different directional pieces for background tiles.
//
////////////////////////////////////////////////////////////////////////////////

//                                        AARRGGBB
GLOBAL constexpr U32 TILE_EMPTY_COLOR = 0xFFFFFFFF;
GLOBAL constexpr U32 TILE_BACKG_COLOR = 0xFF808080;
GLOBAL constexpr U32 TILE_SOLID_COLOR = 0xFF000000;

GLOBAL constexpr int TILE_FLAG_W = 0x01;
GLOBAL constexpr int TILE_FLAG_S = 0x02;
GLOBAL constexpr int TILE_FLAG_E = 0x04;
GLOBAL constexpr int TILE_FLAG_N = 0x08;

GLOBAL constexpr int TILE_CLIP_W = 32;
GLOBAL constexpr int TILE_CLIP_H = 32;

//                                          AARRGGBB
GLOBAL constexpr U32 ENTITY_SPIKE_COLOR = 0xFFFF0000;
GLOBAL constexpr U32 ENTITY_SBONE_COLOR = 0xFFFFFF00;
GLOBAL constexpr U32 ENTITY_LBONE_COLOR = 0xFF00FF00;
GLOBAL constexpr U32 ENTITY_BBLOC_COLOR = 0xFF00FFFF;

INTERNAL bool TileEntityCollision (Vec2 pos, Rect bounds, int tx, int ty, Rect& intersection)
{
    // Entity Bounds
    float x1 = pos.x + bounds.x;
    float y1 = pos.y + bounds.y;
    float x2 = x1    + bounds.w;
    float y2 = y1    + bounds.h;
    // Tile Bounds
    float x3 = (float)tx * TILE_W;
    float y3 = (float)ty * TILE_H;
    float x4 =        x3 + TILE_W;
    float y4 =        y3 + TILE_H;
    // Intersection
    float x5 = std::max(x1, x3);
    float y5 = std::max(y1, y3);
    float x6 = std::min(x2, x4);
    float y6 = std::min(y2, y4);

    intersection.x = x5;
    intersection.y = y5;
    intersection.w = x6 - x5;
    intersection.h = y6 - y5;

    return ((x5 < x6) && (y5 < y6));
}

INTERNAL void LoadMap (Map& map, std::string file_name)
{
    auto tokens = TokenizeString(file_name, '-');
    ASSERT(tokens.size() == 3); // Tileset-Zone-Map

    std::string tileset_file = "t" + tokens[0] + ".bmp";
    LoadImage(map.tileset, tileset_file.c_str());

    file_name = "assets/maps/" + file_name;
    SDL_Surface* surface = SDL_LoadBMP(file_name.c_str());
    if (!surface)
    {
        LOG_ERROR(ERR_MAX, "Failed to load map '%s'! (%s)", file_name.c_str(), SDL_GetError());
    }

    // We want the data to be formatted as 32-bit RGBA so we know how to access the pixels.
    ASSERT(surface->format->BytesPerPixel == 4);

    map.w = surface->w;
    map.h = surface->h;

    map.tiles.resize(map.w*map.h);

    // Seed the random tiles for the map using the map's name so that they remain consistent!
    unsigned int random_seed = 0;
    for (int i=0; i<file_name.length(); ++i) random_seed += file_name[i];
    RandomSeed(random_seed);

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
                tile->xoff = 0;
                tile->yoff = 0;

                // Set the row for solid and background tiles.
                switch (tile->type)
                {
                    case (TILE_SOLID): tile->yoff = RandomRange(0, 1); break;
                    case (TILE_BACKG): tile->yoff = 3;                 break;
                }

                // Set the direction for solid and background tiles.
                switch (tile->type)
                {
                    case (TILE_SOLID):
                    {
                        if ((ix == (      0)) || (pixels[(iy)*map.w+(ix-1)] == TILE_SOLID_COLOR)) tile->xoff |= TILE_FLAG_W;
                        if ((iy == (map.h-1)) || (pixels[(iy+1)*map.w+(ix)] == TILE_SOLID_COLOR)) tile->xoff |= TILE_FLAG_S;
                        if ((ix == (map.w-1)) || (pixels[(iy)*map.w+(ix+1)] == TILE_SOLID_COLOR)) tile->xoff |= TILE_FLAG_E;
                        if ((iy == (      0)) || (pixels[(iy-1)*map.w+(ix)] == TILE_SOLID_COLOR)) tile->xoff |= TILE_FLAG_N;
                    } break;
                    case (TILE_BACKG):
                    {
                        if ((ix == (      0)) || (pixels[(iy)*map.w+(ix-1)] == TILE_BACKG_COLOR) || (pixels[(iy)*map.w+(ix-1)] == TILE_SOLID_COLOR)) tile->xoff |= TILE_FLAG_W;
                        if ((iy == (map.h-1)) || (pixels[(iy+1)*map.w+(ix)] == TILE_BACKG_COLOR) || (pixels[(iy+1)*map.w+(ix)] == TILE_SOLID_COLOR)) tile->xoff |= TILE_FLAG_S;
                        if ((ix == (map.w-1)) || (pixels[(iy)*map.w+(ix+1)] == TILE_BACKG_COLOR) || (pixels[(iy)*map.w+(ix+1)] == TILE_SOLID_COLOR)) tile->xoff |= TILE_FLAG_E;
                        if ((iy == (      0)) || (pixels[(iy-1)*map.w+(ix)] == TILE_BACKG_COLOR) || (pixels[(iy-1)*map.w+(ix)] == TILE_SOLID_COLOR)) tile->xoff |= TILE_FLAG_N;
                    } break;
                }

                // Special case for inner-solid tiles to add some visual variance.
                if ((tile->type == TILE_SOLID) && (tile->xoff == 0x0F))
                {
                    if (RandomRange(0, 100) <= 15)
                    {
                        tile->yoff = 2;
                        tile->xoff = RandomRange(0, 15);
                    }
                }
            }
        }
    }

    map.bone_counter.small_bones_collected = 0;
    map.bone_counter.small_bones_total = 0;
    map.bone_counter.large_bones_collected = 0;
    map.bone_counter.large_bones_total = 0;

    // Handle loading all the different entities in the game.
    for (int iy=0; iy<map.h; ++iy)
    {
        for (int ix=0; ix<map.w; ++ix)
        {
            int index = (iy*map.w+ix);
            U32 pixel = pixels[index];

            switch (pixel)
            {
                case (ENTITY_SPIKE_COLOR): // SPIKES!
                {
                    // Determine what way the spike should face based on the surrounding tiles.
                    SpikeDir sdir = SPIKE_DIR_U;
                    if      ((iy == (map.h-1)) || (pixels[(iy+1)*map.w+(ix)] == TILE_SOLID_COLOR)) sdir = SPIKE_DIR_U;
                    else if ((iy == (      0)) || (pixels[(iy-1)*map.w+(ix)] == TILE_SOLID_COLOR)) sdir = SPIKE_DIR_D;
                    else if ((ix == (      0)) || (pixels[(iy)*map.w+(ix-1)] == TILE_SOLID_COLOR)) sdir = SPIKE_DIR_R;
                    else if ((ix == (map.w-1)) || (pixels[(iy)*map.w+(ix+1)] == TILE_SOLID_COLOR)) sdir = SPIKE_DIR_L;
                    map.spikes.push_back(Spike());
                    CreateSpike(map.spikes.back(), (float)(ix*TILE_W), (float)(iy*TILE_H), sdir);
                } break;
                case (ENTITY_SBONE_COLOR): // SMALL BONES!
                {
                    map.sbones.push_back(SmallBone());
                    CreateSmallBone(map.sbones.back(), (float)(ix*TILE_W), (float)(iy*TILE_H));
                    map.bone_counter.small_bones_total++;
                } break;
                case (ENTITY_LBONE_COLOR): // LARGE BONES!
                {
                    map.lbones.push_back(BigBone());
                    CreateBigBone(map.lbones.back(), (float)(ix*TILE_W), (float)(iy*TILE_H));
                    map.bone_counter.large_bones_total++;
                } break;
                case (ENTITY_BBLOC_COLOR): // BREAKABLE BLOCKS!
                {
                    map.bblocks.push_back(BreakableBlock());
                    CreateBreakableBlock(map.bblocks.back(), (float)(ix*TILE_W), (float)(iy*TILE_H));
                    map.tiles.at(iy*map.w+ix).type = TILE_SOLID;
                    map.tiles.at(iy*map.w+ix).invis = true;
                } break;
            }
        }
    }

    SDL_FreeSurface(surface);
}

INTERNAL void FreeMap (Map& map)
{
    FreeImage(map.tileset);
    map.tiles.clear();
    map.w = 0, map.h = 0;
    // Entities
    for (auto& spike: map.spikes) DeleteSpike(spike);
    map.spikes.clear();
    map.sbones.clear();
    map.lbones.clear();
    map.bblocks.clear();
}

INTERNAL void DrawMapBackg (Map& map)
{
    // Draw the background tiles.
    DrawFill(0.0f,0.0f, (float)(map.w*TILE_W),(float)(map.h*TILE_H), MakeColor(1,1,1));
    SDL_Rect clip = { 0,0,TILE_CLIP_W,TILE_CLIP_H };
    for (int iy=0; iy<map.h; ++iy)
    {
        for (int ix=0; ix<map.w; ++ix)
        {
            Tile* tile = &map.tiles[iy*map.w+ix];
            if (tile->type == TILE_BACKG)
            {
                clip.x = tile->xoff * TILE_CLIP_W, clip.y = tile->yoff * TILE_CLIP_H;
                DrawImage(map.tileset, (float)((ix*TILE_W)+(TILE_W/2)-(TILE_CLIP_W/2)), (float)((iy*TILE_H)+(TILE_H/2)-(TILE_CLIP_H/2)), FLIP_NONE, &clip);
            }
        }
    }
}

INTERNAL void DrawMapEntities (Map& map, float dt)
{
    for (auto& sbone: map.sbones) RenderSmallBone(sbone, dt);
    for (auto& lbone: map.lbones) RenderBigBone(lbone, dt);
    for (auto& bblocks: map.bblocks) RenderBreakableBlock(bblocks);
}

// Special exception becuase it seems better for spikes to draw in front
// of the player whilst the rest of the entities draw behind the player.
INTERNAL void DrawMapSpikes (Map& map)
{
    for (auto& spike: map.spikes) DrawSpike(spike);
}

INTERNAL void DrawMapFront (Map& map)
{
    // Draw the solid tiles.
    SDL_Rect clip = { 0,0,TILE_CLIP_W,TILE_CLIP_H };
    for (int iy=0; iy<map.h; ++iy)
    {
        for (int ix=0; ix<map.w; ++ix)
        {
            Tile* tile = &map.tiles[iy*map.w+ix];
            if (tile->type == TILE_SOLID)
            {
                clip.x = tile->xoff * TILE_CLIP_W, clip.y = tile->yoff * TILE_CLIP_H;
                DrawImage(map.tileset, (float)((ix*TILE_W)+(TILE_W/2)-(TILE_CLIP_W/2)), (float)((iy*TILE_H)+(TILE_H/2)-(TILE_CLIP_H/2)), FLIP_NONE, &clip);
            }
        }
    }
}
