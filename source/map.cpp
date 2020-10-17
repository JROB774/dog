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
GLOBAL constexpr U32 TILE_EMPTY_COLOR = 0xFFFFFFFF; // WHITE
GLOBAL constexpr U32 TILE_SOLID_COLOR = 0xFF000000; // BLACK
GLOBAL constexpr U32 TILE_SPIKE_COLOR = 0xFFFF0000; // RED
GLOBAL constexpr U32 TILE_SBONE_COLOR = 0xFFFFFF00; // YELLOW
GLOBAL constexpr U32 TILE_LBONE_COLOR = 0xFF00FF00; // GREEN
GLOBAL constexpr U32 TILE_BBLOC_COLOR = 0xFF00FFFF; // CYAN
GLOBAL constexpr U32 TILE_SPITB_COLOR = 0xFFFF00FF; // MAGENTA
GLOBAL constexpr U32 TILE_CBOIH_COLOR = 0xFFB6FF00; // LIME
GLOBAL constexpr U32 TILE_CBOIV_COLOR = 0xFF5B7F00; // DARK LIME
GLOBAL constexpr U32 TILE_WALKB_COLOR = 0xFF7F0037; // DARK PINK?? idk i am color blind...
GLOBAL constexpr U32 TILE_CHRGB_COLOR = 0xFFFF006E; // PINK

GLOBAL constexpr int TILE_FLAG_W = 0x01;
GLOBAL constexpr int TILE_FLAG_S = 0x02;
GLOBAL constexpr int TILE_FLAG_E = 0x04;
GLOBAL constexpr int TILE_FLAG_N = 0x08;

GLOBAL constexpr int TILE_CLIP_W = 32;
GLOBAL constexpr int TILE_CLIP_H = 32;

INTERNAL void LoadMap (Map& map, std::string file_name)
{
    auto tokens = TokenizeString(file_name, '-');
    ASSERT(tokens.size() == 3); // Tileset-Zone-Map

    std::string background_file = "backs/" + file_name;
    map.has_background = std::filesystem::exists(gAssetPath + background_file);
    if (map.has_background) LoadImage(map.background, background_file.c_str());

    std::string foreground_file = "fronts/" + file_name;
    map.has_foreground = std::filesystem::exists(gAssetPath + foreground_file);
    if (map.has_foreground) LoadImage(map.foreground, foreground_file.c_str());

    std::string tileset_file = "t" + tokens[1] + ".bmp";
    LoadImage(map.tileset, tileset_file.c_str());

    file_name = gAssetPath + "maps/" + file_name;
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

    // Handle loading all the different entities in the game.
    for (int iy=0; iy<map.h; ++iy)
    {
        for (int ix=0; ix<map.w; ++ix)
        {
            int index = (iy*map.w+ix);
            U32 pixel = pixels[index];

            switch (pixel)
            {
                case (TILE_SPIKE_COLOR): // SPIKES!
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
                case (TILE_SBONE_COLOR): // SMALL BONES!
                {
                    float x = (float)(ix*TILE_W);
                    float y = (float)(iy*TILE_H);
                    map.sbones.push_back(SmallBone());
                    CreateSmallBone(map.sbones.back(), x, y);
                    // Kill bones that have already been collected.
                    if (std::find(gBoneCollectedIds.begin(), gBoneCollectedIds.end(), map.sbones.back().id) != gBoneCollectedIds.end())
                    {
                        map.sbones.back().dead = true;
                    }
                } break;
                case (TILE_LBONE_COLOR): // LARGE BONES!
                {
                    float x = (float)(ix*TILE_W);
                    float y = (float)(iy*TILE_H);
                    map.lbones.push_back(BigBone());
                    CreateBigBone(map.lbones.back(), x, y);
                    // Kill bones that have already been collected.
                    if (std::find(gBoneCollectedIds.begin(), gBoneCollectedIds.end(), map.lbones.back().id) != gBoneCollectedIds.end())
                    {
                        map.lbones.back().dead = true;
                    }
                } break;
                case (TILE_BBLOC_COLOR): // BREAKABLE BLOCKS!
                {
                    map.bblocks.push_back(BreakableBlock());
                    CreateBreakableBlock(map.bblocks.back(), (float)(ix*TILE_W), (float)(iy*TILE_H));
                    map.tiles.at(iy*map.w+ix).type = TILE_SOLID;
                    map.tiles.at(iy*map.w+ix).invis = true;
                } break;
                case (TILE_CBOIV_COLOR): // CRUSHBOI VERTICAL!
                {
                    float x = (float)(ix*TILE_W);
                    float y = (float)(iy*TILE_H);
                    map.cboi.push_back(CrushBoi());
                    CreateCrushBoi(map.cboi.back(),(float)(ix*TILE_W), (float)(iy*TILE_H), true);
                } break;
                case (TILE_CBOIH_COLOR): // CRUSHBOI HORIZONTAL!
                {
                    float x = (float)(ix*TILE_W);
                    float y = (float)(iy*TILE_H);
                    map.cboi.push_back(CrushBoi());
                    CreateCrushBoi(map.cboi.back(),(float)(ix*TILE_W), (float)(iy*TILE_H), false);
                } break;
                case (TILE_SPITB_COLOR): // SPIT BOYS!
                {
                    map.spitboys.push_back(SpitBoy());
                    bool flip = ((iy == (map.h-1)) || (pixels[(iy+1)*map.w+(ix)] == TILE_SOLID_COLOR));
                    CreateSpitBoy(map.spitboys.back(), (float)(ix*TILE_W), (float)(iy*TILE_H), flip);
                } break;
                case (TILE_WALKB_COLOR): // WALK BOYS!
                {
                    map.walkboys.push_back(WalkBoy());
                    CreateWalkBoy(map.walkboys.back(), (float)(ix*TILE_W), (float)(iy*TILE_H));
                } break;
                case (TILE_CHRGB_COLOR): // CHARGE BOYS!
                {
                    map.chargeboys.push_back(ChargeBoy());
                    CreateChargeBoy(map.chargeboys.back(), (float)(ix*TILE_W), (float)(iy*TILE_H));
                } break;
            }
        }
    }

    SDL_FreeSurface(surface);
}

INTERNAL void FreeMap (Map& map)
{
    if (map.has_background) FreeImage(map.background);
    if (map.has_foreground) FreeImage(map.foreground);
    FreeImage(map.tileset);
    map.tiles.clear();
    map.w = 0, map.h = 0;
    map.has_background = false;
    map.has_foreground = false;
    // Entities
    for (auto& spike: map.spikes    ) DeleteSpike    (spike);
    for (auto& spitb: map.spitboys  ) DeleteSpitBoy  (spitb);
    for (auto& walkb: map.walkboys  ) DeleteWalkBoy  (walkb);
    for (auto& chrgb: map.chargeboys) DeleteChargeBoy(chrgb);
    map.spikes.clear();
    map.sbones.clear();
    map.lbones.clear();
    map.bblocks.clear();
    map.spitboys.clear();
    map.cboi.clear();
    map.walkboys.clear();
    map.chargeboys.clear();
}

INTERNAL void UpdateMap (Map& map, float dt)
{
    for (auto& spitb: map.spitboys  ) UpdateSpitBoy  (spitb, dt);
    for (auto& cboi : map.cboi      ) UpdateCrushBoi (cboi,  dt);
    for (auto& walkb: map.walkboys  ) UpdateWalkBoy  (walkb, dt);
    for (auto& chrgb: map.chargeboys) UpdateChargeBoy(chrgb, dt);
}

INTERNAL void DrawMapBackground (Map& map)
{
    if (map.has_background) DrawImage(map.background, 0,0);
    else DrawFill(0.0f,0.0f, (float)(map.w*TILE_W),(float)(map.h*TILE_H), MakeColor(1,1,1));
}

INTERNAL void DrawMapBackEntities (Map& map, float dt)
{
    for (auto& sbone: map.sbones    ) RenderSmallBone(sbone, dt);
    for (auto& lbone: map.lbones    ) RenderBigBone  (lbone, dt);
    for (auto& spitb: map.spitboys  ) RenderSpitBoy  (spitb, dt);
    for (auto& cboi : map.cboi      ) RenderCrushBoi (cboi     );
    for (auto& walkb: map.walkboys  ) RenderWalkBoy  (walkb, dt);
    for (auto& chrgb: map.chargeboys) RenderChargeBoy(chrgb, dt);
}

INTERNAL void DrawMapFrontEntities (Map& map, float dt)
{
    for (auto& spike  : map.spikes ) DrawSpike(spike);
    for (auto& bblocks: map.bblocks) RenderBreakableBlock(bblocks);
}

INTERNAL void DrawMapFrontTiles (Map& map)
{
    // Draw the solid tiles.
    SDL_Rect clip = { 0,0,TILE_CLIP_W,TILE_CLIP_H };
    for (int iy=0; iy<map.h; ++iy)
    {
        for (int ix=0; ix<map.w; ++ix)
        {
            Tile* tile = &map.tiles[iy*map.w+ix];
            if (tile->type == TILE_SOLID && !tile->invis)
            {
                clip.x = tile->xoff * TILE_CLIP_W, clip.y = tile->yoff * TILE_CLIP_H;
                DrawImage(map.tileset, (float)((ix*TILE_W)+(TILE_W/2)-(TILE_CLIP_W/2)), (float)((iy*TILE_H)+(TILE_H/2)-(TILE_CLIP_H/2)), FLIP_NONE, &clip);
            }
        }
    }
}

INTERNAL void DrawMapForeground (Map& map)
{
    if (map.has_foreground) DrawImage(map.foreground, 0,0);
}

INTERNAL void ResetMap ()
{
    ClearParticles();

    RespawnMapBones();
    RespawnMapBlocks();

    for (auto& spitboy  : gWorld.current_map.spitboys  ) ResetSpitBoy  (spitboy  );
    for (auto& cboi     : gWorld.current_map.cboi      ) ResetCrushBoi (cboi     );
    for (auto& walkboy  : gWorld.current_map.walkboys  ) ResetWalkBoy  (walkboy  );
    for (auto& chargeboy: gWorld.current_map.chargeboys) ResetChargeBoy(chargeboy);
}

INTERNAL Tile& GetMapTile (Map& map, int x, int y)
{
    return map.tiles[y * map.w + x];
}
