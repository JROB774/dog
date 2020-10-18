GLOBAL constexpr float CRUSHBOI_COOLDOWN = 0.75f;
GLOBAL constexpr float CRUSHBOI_SPEED = 350.0f;

GLOBAL Image gCrushBoiImage;
GLOBAL Sound gCrushBoiHitSound;

INTERNAL void InitCrushBoi ()
{
    LoadImage(gCrushBoiImage, "crushboy.bmp");
    LoadSound(gCrushBoiHitSound, "crush.wav");
}

INTERNAL void QuitCrushBoi ()
{
    FreeSound(gCrushBoiHitSound);
    FreeImage(gCrushBoiImage);
}

INTERNAL void CreateCrushBoi (CrushBoi& boi, float x, float y, bool vertical)
{
    boi.pos       = { x,y };
    boi.start_pos = { x,y };
    boi.vel       = { 0,0 };
    boi.vertical  = vertical;
    boi.active    = false;
    boi.bounds    = { 0,0,16,16 };
    boi.timer     = 0.0f;
}

INTERNAL void UpdateCrushBoi (CrushBoi& boi, float dt)
{
    if (boi.active)
    {
        Vec2 we_arent_using_this = {0,0};
        if (EntityAndMapCollision(boi.pos,boi.bounds, boi.vel, gWorld.current_map, we_arent_using_this, dt))
        {
            Vec2 particle_pos = { 0,0 };
            if (boi.vertical)
            {
                particle_pos.x = boi.pos.x;
                if (boi.vel.y < 0)
                {
                    particle_pos.y = boi.pos.y;
                    CreateParticlesRotated(PARTICLE_TYPE_PUFF_D, (int)particle_pos.x-2,(int)particle_pos.y,(int)particle_pos.x + 16,(int)particle_pos.y + 2, 4, 8, DegToRad(180));
                    PlaySound(gCrushBoiHitSound);
                    ShakeCamera(0, -1, 0, 1, 0.25f);
                }
                if (boi.vel.y > 0)
                {
                    particle_pos.y = boi.pos.y + boi.bounds.h;
                    CreateParticlesRotated(PARTICLE_TYPE_PUFF_D, (int)particle_pos.x-2,(int)particle_pos.y,(int)particle_pos.x + 16,(int)particle_pos.y, 4, 8, DegToRad(0));
                    PlaySound(gCrushBoiHitSound);
                    ShakeCamera(0, -1, 0, 1, 0.25f);
                }
            }
            if (!boi.vertical)
            {
                particle_pos.y = boi.pos.y;
                if (boi.vel.x < 0)
                {
                    particle_pos.x = boi.pos.x;
                    CreateParticlesRotated(PARTICLE_TYPE_PUFF_D, (int)particle_pos.x,(int)particle_pos.y - 2,(int)particle_pos.x,(int)particle_pos.y + 16, 4, 8, DegToRad(90));
                    PlaySound(gCrushBoiHitSound);
                    ShakeCamera(-1, 0, 1, 0, 0.25f);
                }
                if (boi.vel.x > 0)
                {
                    particle_pos.x = boi.pos.x + boi.bounds.w;
                    CreateParticlesRotated(PARTICLE_TYPE_PUFF_D, (int)particle_pos.x,(int)particle_pos.y - 2,(int)particle_pos.x,(int)particle_pos.y + 16, 4, 8, DegToRad(180));
                    PlaySound(gCrushBoiHitSound);
                    ShakeCamera(-1, 0, 1, 0, 0.25f);
                }
            }

            boi.timer = CRUSHBOI_COOLDOWN;
            boi.active = false;
        }

        if ( boi.vertical) boi.pos.y += boi.vel.y * dt;
        if (!boi.vertical) boi.pos.x += boi.vel.x * dt;
    }

    if (boi.timer > 0.0f) boi.timer -= dt;

    if (gGameState.dog.dead) return;

    if (!boi.active)
    {
        if (boi.timer <= 0.0f)
        {
            if (EntityLineOfSight(boi.pos,boi.bounds, gGameState.dog.pos,gGameState.dog.bounds, gWorld.current_map))
            {
                if (boi.vertical)
                {
                    float temp = gGameState.dog.bounds.x + gGameState.dog.pos.x;
                    if (temp < boi.pos.x && temp + gGameState.dog.bounds.w > boi.pos.x || temp > boi.pos.x && temp < boi.pos.x + 16)
                    {
                        boi.active = true;
                        temp = gGameState.dog.bounds.y + gGameState.dog.pos.y;
                        if(temp < boi.pos.y){boi.vel.y = -CRUSHBOI_SPEED;}
                        if(temp > boi.pos.y){boi.vel.y =  CRUSHBOI_SPEED;}
                    }
                }
                if (!boi.vertical)
                {
                    float temp = gGameState.dog.bounds.y + gGameState.dog.pos.y;
                    if (temp < boi.pos.y && temp + gGameState.dog.bounds.h > boi.pos.y || temp > boi.pos.y && temp < boi.pos.y + 16)
                    {
                        boi.active = true;
                        temp = gGameState.dog.bounds.x + gGameState.dog.pos.x;
                        if(temp < boi.pos.x){boi.vel.x = -CRUSHBOI_SPEED;}
                        if(temp > boi.pos.x){boi.vel.x =  CRUSHBOI_SPEED;}
                    }
                }
            }
        }
    }
}

INTERNAL void RenderCrushBoi (CrushBoi& boi)
{
    SDL_Rect clip = { 0,0,32,32 };
    if (boi.active || boi.timer > 0.0f) clip.x += 32;
    if (!boi.vertical) clip.y += 32;
    DrawImage(gCrushBoiImage, boi.pos.x-8,boi.pos.y-8, FLIP_NONE, &clip);
}

INTERNAL void ResetCrushBoi (CrushBoi& boi)
{
    boi.pos = boi.start_pos;
    boi.active = false;
    boi.timer = 0.0f;
}
