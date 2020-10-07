GLOBAL constexpr float WALKBOY_SPEED = 2.5f * TILE_W;

GLOBAL Image gWalkBoyImage;

INTERNAL void InitWalkBoy ()
{
    LoadImage(gWalkBoyImage, "walkboy.bmp");
}

INTERNAL void QuitWalkBoy ()
{
    FreeImage(gWalkBoyImage);
}

INTERNAL void CreateWalkBoy (WalkBoy& walkboy, float x, float y)
{
    walkboy.start_pos = { x,y };
    walkboy.pos = walkboy.start_pos;
    walkboy.bounds = { 2,10,12,6 };
    walkboy.flip = FLIP_NONE;
}

INTERNAL void UpdateWalkBoy (WalkBoy& walkboy, float dt)
{
    // If both sides are bad before even moving then we just don't do anything to avoid freaking out.
    if (!WalkBoyCheckRightIsGood(walkboy, walkboy.pos) && !WalkBoyCheckLeftIsGood(walkboy, walkboy.pos)) return;

    Vec2 next_pos = walkboy.pos;

    if (walkboy.flip == FLIP_NONE) next_pos.x += WALKBOY_SPEED * dt; // Right
    if (walkboy.flip == FLIP_HORZ) next_pos.x -= WALKBOY_SPEED * dt; // Left

    // Check if we're off the edge or at a wall for our current direction...
    bool should_move = true;
    if (walkboy.flip == FLIP_NONE && !WalkBoyCheckRightIsGood(walkboy, walkboy.pos))
    {
        walkboy.flip = FLIP_HORZ;
        should_move = false;
    }
    if (walkboy.flip == FLIP_HORZ && !WalkBoyCheckLeftIsGood(walkboy, walkboy.pos))
    {
        walkboy.flip = FLIP_NONE;
        should_move = false;
    }

    // If it's safe to move then we shall update our position.
    if (should_move) walkboy.pos = next_pos;
}

INTERNAL void RenderWalkBoy (WalkBoy& walkboy, float dt)
{
    DrawImage(gWalkBoyImage, walkboy.pos.x-4, walkboy.pos.y-4, walkboy.flip);
}

INTERNAL void ResetWalkBoy (WalkBoy& walkboy)
{
    walkboy.pos = walkboy.start_pos;
    walkboy.flip = FLIP_NONE;
}

INTERNAL bool WalkBoyCheckRightIsGood (WalkBoy& walkboy, Vec2 pos)
{
    float x = pos.x + TILE_W;
    int tx = (int)floorf(x / TILE_W), ty = (int)floorf(pos.y / TILE_H);
    // If the tile next to us is solid or the one below it is empty then turn around.
    if (GetMapTile(gWorld.current_map, tx,ty  ).type == TILE_SOLID ||
        GetMapTile(gWorld.current_map, tx,ty+1).type == TILE_EMPTY)
    {
        return false;
    }
    return true;
}

INTERNAL bool WalkBoyCheckLeftIsGood (WalkBoy& walkboy, Vec2 pos)
{
    float x = pos.x-1;
    int tx = (int)floorf(x / TILE_W), ty = (int)floorf(pos.y / TILE_H);
    // If the tile next to us is solid or the one below it is empty then turn around.
    if (GetMapTile(gWorld.current_map, tx,ty  ).type == TILE_SOLID ||
        GetMapTile(gWorld.current_map, tx,ty+1).type == TILE_EMPTY)
    {
        return false;
    }
    return true;
}
