GLOBAL constexpr float SPITBOY_SPIT_COOLDOWN = 0.1f;
GLOBAL constexpr float SPITBOY_SPIT_FORCE = 225.0f;

GLOBAL Image gSpitBoyImage;
GLOBAL Image gSpitImage;
GLOBAL Sound gSpitBoySound;

INTERNAL void InitSpitBoy ()
{
    LoadImage(gSpitBoyImage, "spitboy.bmp");
    LoadImage(gSpitImage, "spit.bmp");
    LoadSound(gSpitBoySound, "spit.wav");
}

INTERNAL void QuitSpitBoy ()
{
    FreeSound(gSpitBoySound);
    FreeImage(gSpitBoyImage);
    FreeImage(gSpitImage);
}

INTERNAL void CreateSpitBoy (SpitBoy& spitboy, float x, float y)
{
    spitboy.pos.x = x, spitboy.pos.y = y;
    spitboy.angle = DegToRad(270);
    spitboy.bounds = { 4,4,16,16 };
}

INTERNAL void UpdateSpitBoy (SpitBoy& spitboy, float dt)
{
    float ax = spitboy.pos.x + 12;
    float ay = spitboy.pos.y + 12;
    float bx = gGameState.dog.pos.x + gGameState.dog.bounds.x + (gGameState.dog.bounds.w/2);
    float by = gGameState.dog.pos.y + gGameState.dog.bounds.y + (gGameState.dog.bounds.h/2);

    float angle = atan2(ay - by, ax - bx);

    spitboy.sight = EntityLineOfSight(spitboy.pos,spitboy.bounds, gGameState.dog.pos,gGameState.dog.bounds, gWorld.current_map);
    if (spitboy.sight) spitboy.angle = angle;

    if (spitboy.timer > 0.0f) spitboy.timer -= dt;
    else
    {
        if (!gGameState.dog.dead)
        {
            if (spitboy.sight)
            {
                Vec2 pos = { ax-(8/2)-2, ay-(8/2)-2 };
                Vec2 vel = { -SPITBOY_SPIT_FORCE, 0.0f }, nvel;

                float spit_angle = spitboy.angle + DegToRad(RandomFloatRange(-3.0f, 3.0f));

                nvel.x = vel.x * cos(spit_angle) - vel.y * sin(spit_angle);
                nvel.y = vel.x * sin(spit_angle) + vel.y * cos(spit_angle);

                spitboy.timer = SPITBOY_SPIT_COOLDOWN;
                spitboy.spit.push_back({ pos, nvel, { 2,2,4,4 }, false });
            }
        }
    }

    for (auto& spit: spitboy.spit)
    {
        if (!spit.dead)
        {
            Vec2 contact_normal = { 0,0 };
            if (EntityAndMapCollision(spit.pos,spit.bounds,spit.vel, gWorld.current_map, contact_normal, dt))
            {
                KillSpit(spit);
                continue;
            }
            spit.pos.x += spit.vel.x * dt;
            spit.pos.y += spit.vel.y * dt;
        }
    }
}

INTERNAL void RenderSpitBoy (SpitBoy& spitboy, float dt)
{
    float degrees = RadToDeg(spitboy.angle); // RadToDeg(RoundToMultiple(spitboy.angle, (float)(M_PI*2)/16));
    for (auto& spit: spitboy.spit) if (!spit.dead) DrawImage(gSpitImage, spit.pos.x-spit.bounds.x, spit.pos.y-spit.bounds.y);
    DrawImageEx(gSpitBoyImage, spitboy.pos.x-spitboy.bounds.x, spitboy.pos.y-spitboy.bounds.y, degrees);
}

INTERNAL void ResetSpitBoy (SpitBoy& spitboy)
{
    spitboy.angle = DegToRad(270);
    spitboy.spit.clear();
}

INTERNAL void KillSpit (Spit& spit)
{
    CreateParticles(PARTICLE_TYPE_PUFF, (int)spit.pos.x+4,(int)spit.pos.y+4,(int)spit.pos.x+4,(int)spit.pos.y+4, 1,3);
    CreateParticles(PARTICLE_TYPE_SPEC, (int)spit.pos.x+4,(int)spit.pos.y+4,(int)spit.pos.x+4,(int)spit.pos.y+4, 2,4, 1.5f);
    spit.dead = true;
}
