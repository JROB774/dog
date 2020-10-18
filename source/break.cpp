INTERNAL void InitBreakableBlock ()
{
    LoadImage(gBreakableBlockImage, "break.bmp");
    LoadSound(gBreakableBlockSound, "break.wav");
}

INTERNAL void DeleteBreakableBlock ()
{
    FreeImage(gBreakableBlockImage);
    FreeSound(gBreakableBlockSound);
}

INTERNAL void CreateBreakableBlock (BreakableBlock& block, float x, float y)
{
    block.pos = { x,y };
    block.bounds = { 0,0,TILE_W,TILE_H };
    block.dead = false;
}

INTERNAL bool TryBreakABlock (Dog& dog, BreakableBlock& block)
{
    if (block.dead) return false; // We already check for this but double-check here just to be safe in case code changes!

    Rect dbounds = { dog.pos.x+dog.bounds.x, dog.pos.y+dog.bounds.y, dog.bounds.w, dog.bounds.h };
    Rect bbounds = { block.pos.x+block.bounds.x, block.pos.y+block.bounds.y, block.bounds.w, block.bounds.h };

    if      (dog.down             ) dbounds.y += 12; // Down
    else if (dog.up               ) dbounds.y -= 12; // Up
    else if (dog.flip == FLIP_NONE) dbounds.x +=  8; // Right
    else                            dbounds.x -=  8; // Left

    if (RectAndRectCollision(dbounds, bbounds))
    {
        BreakBlock(block);
        return true;
    }

    return false;
}

INTERNAL void BreakBlock (BreakableBlock& block)
{
    int tx = (int)block.pos.x / TILE_W;
    int ty = (int)block.pos.y / TILE_H;
    gWorld.current_map.tiles[ty*gWorld.current_map.w+tx].type = TILE_EMPTY;
    block.dead = true;
    CreateParticles(PARTICLE_TYPE_LBREAK, (int)block.pos.x+8,(int)block.pos.y+8,(int)block.pos.x+8,(int)block.pos.y+8, 1,1);
    CreateParticles(PARTICLE_TYPE_MBREAK, (int)block.pos.x+8,(int)block.pos.y+8,(int)block.pos.x+8,(int)block.pos.y+8, 1,2);
    CreateParticles(PARTICLE_TYPE_SBREAK, (int)block.pos.x+8,(int)block.pos.y+8,(int)block.pos.x+8,(int)block.pos.y+8, 1,3);
    CreateParticles(PARTICLE_TYPE_SMOKE2, (int)block.pos.x+8,(int)block.pos.y+8,(int)block.pos.x+8,(int)block.pos.y+8, 1,2);
}

INTERNAL void RenderBreakableBlock (BreakableBlock& block)
{
    if (!block.dead) DrawImage(gBreakableBlockImage, block.pos.x-4, block.pos.y-4);
}

INTERNAL void RespawnMapBlocks ()
{
    // If a block has been destroyed then respawn it.
    gTempBoneCollectedIds.clear();
    for (auto& block: gWorld.current_map.bblocks)
    {
        int tx = (int)block.pos.x / TILE_W;
        int ty = (int)block.pos.y / TILE_H;
        gWorld.current_map.tiles[ty*gWorld.current_map.w+tx].type = TILE_SOLID;
        block.dead = false;
    }
}
