GLOBAL constexpr float CHARGEBOY_WALK_SPEED = 2.5f * TILE_W;
GLOBAL constexpr float CHARGEBOY_CHARGE_SPEED = CHARGEBOY_WALK_SPEED * 3;

GLOBAL Image gChargeBoyImage;

INTERNAL void InitChargeBoy ()
{
    LoadImage(gChargeBoyImage, "chargeboy.bmp");
}

INTERNAL void QuitChargeBoy ()
{
    FreeImage(gChargeBoyImage);
}

INTERNAL void CreateChargeBoy (ChargeBoy& chargeboy, float x, float y)
{
    chargeboy.start_pos = { x,y };
    chargeboy.pos = chargeboy.start_pos;
    chargeboy.bounds = { 2,10,12,6 };
    chargeboy.flip = FLIP_NONE;
}

INTERNAL void UpdateChargeBoy (ChargeBoy& chargeboy, float dt)
{
    // If both sides are bad before even moving then we just don't do anything to avoid freaking out.
    if (!ChargeBoyCheckRightIsGood(chargeboy, chargeboy.pos) && !ChargeBoyCheckLeftIsGood(chargeboy, chargeboy.pos)) return;

    Vec2 next_pos = chargeboy.pos;

    if (ChargeBoyShouldCharge(chargeboy, dt)) // Move at a faster speed if we should be charging!
    {
        if (chargeboy.flip == FLIP_NONE) next_pos.x += CHARGEBOY_CHARGE_SPEED * dt; // Right
        if (chargeboy.flip == FLIP_HORZ) next_pos.x -= CHARGEBOY_CHARGE_SPEED * dt; // Left
    }
    else
    {
        if (chargeboy.flip == FLIP_NONE) next_pos.x += CHARGEBOY_WALK_SPEED * dt; // Right
        if (chargeboy.flip == FLIP_HORZ) next_pos.x -= CHARGEBOY_WALK_SPEED * dt; // Left
    }

    // Check if we're off the edge or at a wall for our current direction...
    bool should_move = true;
    if (chargeboy.flip == FLIP_NONE && !ChargeBoyCheckRightIsGood(chargeboy, chargeboy.pos))
    {
        chargeboy.flip = FLIP_HORZ;
        should_move = false;
    }
    if (chargeboy.flip == FLIP_HORZ && !ChargeBoyCheckLeftIsGood(chargeboy, chargeboy.pos))
    {
        chargeboy.flip = FLIP_NONE;
        should_move = false;
    }

    // If it's safe to move then we shall update our position.
    if (should_move) chargeboy.pos = next_pos;
}

INTERNAL void RenderChargeBoy (ChargeBoy& chargeboy, float dt)
{
    DrawImage(gChargeBoyImage, chargeboy.pos.x-4, chargeboy.pos.y-4, chargeboy.flip);
}

INTERNAL void ResetChargeBoy (ChargeBoy& chargeboy)
{
    chargeboy.pos = chargeboy.start_pos;
    chargeboy.flip = FLIP_NONE;
}

// HELPER FUNCTIONS

INTERNAL bool ChargeBoyCheckRightIsGood (ChargeBoy& chargeboy, Vec2 pos)
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

INTERNAL bool ChargeBoyCheckLeftIsGood (ChargeBoy& chargeboy, Vec2 pos)
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

INTERNAL bool ChargeBoyShouldCharge (ChargeBoy& chargeboy, float dt)
{
    // Build a collision box from the charge boy to the end of its platform.
    // If the player is inside of it then we should be charging at them.
    Rect aggro_bounds = { 0, chargeboy.pos.y+4, 0, 12 };
    if (chargeboy.flip == FLIP_NONE) // Right
    {
        aggro_bounds.x = chargeboy.pos.x + TILE_W/2;
        int tx = (int)floorf(aggro_bounds.x / TILE_W), ty = (int)floorf(aggro_bounds.y / TILE_H);
        while (GetMapTile(gWorld.current_map, tx,ty  ).type != TILE_SOLID &&
               GetMapTile(gWorld.current_map, tx,ty+1).type != TILE_EMPTY)
        {
            aggro_bounds.w += CHARGEBOY_WALK_SPEED * dt;
            tx = (int)floorf((aggro_bounds.x+aggro_bounds.w) / TILE_W);
            if (tx >= gWorld.current_map.w-1) break;
        }
    }
    if (chargeboy.flip == FLIP_HORZ) // Left
    {
        aggro_bounds.x = chargeboy.pos.x + TILE_W/2;
        int tx = (int)floorf(aggro_bounds.x / TILE_W), ty = (int)floorf(aggro_bounds.y / TILE_H);
        while (GetMapTile(gWorld.current_map, tx,ty  ).type != TILE_SOLID &&
               GetMapTile(gWorld.current_map, tx,ty+1).type != TILE_EMPTY)
        {
            aggro_bounds.x -= CHARGEBOY_WALK_SPEED * dt;
            aggro_bounds.w += CHARGEBOY_WALK_SPEED * dt;
            tx = (int)floorf((aggro_bounds.x) / TILE_W);
            if (tx <= 0) break;
        }
    }

    return (EntityAndEntityCollision(gGameState.dog.pos,gGameState.dog.bounds, { 0,0 },aggro_bounds));
}
