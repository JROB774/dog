GLOBAL constexpr float SPITBOY_SPIT_COOLDOWN = 0.5f;
GLOBAL constexpr float SPITBOY_SPIT_FORCE = 225.0f;

GLOBAL Image gSpitBoyImage;
GLOBAL Image gSpitImage;
GLOBAL Sound gSpitBoySpitSound;
GLOBAL Sound gSpitBoyHitSound;

INTERNAL void InitSpitBoy ()
{
    LoadImage(gSpitBoyImage, "spitboy.bmp");
    LoadImage(gSpitImage, "spit.bmp");
    LoadSound(gSpitBoySpitSound, "spit.wav");
    LoadSound(gSpitBoyHitSound, "hit.wav");
}

INTERNAL void QuitSpitBoy ()
{
    FreeImage(gSpitBoyImage);
    FreeImage(gSpitImage);
    FreeSound(gSpitBoySpitSound);
    FreeSound(gSpitBoyHitSound);
}

INTERNAL void CreateSpitBoy (SpitBoy& spitboy, float x, float y, bool flip)
{
    spitboy.state = SPITBOY_STATE_IDLE;
    spitboy.pos.x = x, spitboy.pos.y = y;
    spitboy.angle = DegToRad(270);
    spitboy.bounds = { 4,4,16,16 };
    spitboy.flip = (flip) ? FLIP_VERT : FLIP_NONE;
    spitboy.timer = 0.0f;

    LoadAnimation(spitboy.anim[SPITBOY_STATE_IDLE], "spitboy-idle.anim");
    LoadAnimation(spitboy.anim[SPITBOY_STATE_SPIT], "spitboy-spit.anim");
}

INTERNAL void DeleteSpitBoy (SpitBoy& spitboy)
{
    FreeAnimation(spitboy.anim[SPITBOY_STATE_IDLE]);
    FreeAnimation(spitboy.anim[SPITBOY_STATE_SPIT]);
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

                float spit_angle = spitboy.angle /*+ DegToRad(RandomFloatRange(-3.0f, 3.0f))*/;

                nvel.x = vel.x * cos(spit_angle) - vel.y * sin(spit_angle);
                nvel.y = vel.x * sin(spit_angle) + vel.y * cos(spit_angle);

                spitboy.timer = SPITBOY_SPIT_COOLDOWN;
                spitboy.spit.push_back({ pos, nvel, { 2,2,4,4 }, false });
                spitboy.state = SPITBOY_STATE_SPIT;
                LoadAnimation(spitboy.spit.back().anim, "spit.anim");
                ResetAnimation(spitboy.anim[SPITBOY_STATE_SPIT]);
                PlaySound(gSpitBoySpitSound);
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

    // Reset the animation back to idle once the spitting animation is done.
    if (spitboy.state == SPITBOY_STATE_SPIT)
    {
        if (IsAnimationDone(spitboy.anim[SPITBOY_STATE_SPIT]))
        {
            spitboy.state = SPITBOY_STATE_IDLE;
        }
    }
}

INTERNAL void RenderSpitBoy (SpitBoy& spitboy, float dt)
{
    // Draw the spit.
    for (auto& spit: spitboy.spit)
    {
        if (!spit.dead)
        {
            UpdateAnimation(spit.anim, dt);
            DrawImage(gSpitImage, spit.pos.x-spit.bounds.x, spit.pos.y-spit.bounds.y, FLIP_NONE, GetAnimationClip(spit.anim));
        }
    }
    // Draw the spit boy.
    UpdateAnimation(spitboy.anim[spitboy.state], dt);
    DrawImage(gSpitBoyImage, spitboy.pos.x-spitboy.bounds.x, spitboy.pos.y-spitboy.bounds.y, spitboy.flip, GetAnimationClip(spitboy.anim[spitboy.state]));
}

INTERNAL void ResetSpitBoy (SpitBoy& spitboy)
{
    ResetAnimation(spitboy.anim[SPITBOY_STATE_SPIT]);
    spitboy.state = SPITBOY_STATE_IDLE;
    spitboy.timer = 0.0f;
    spitboy.angle = DegToRad(270);
    for (auto& spit: spitboy.spit) FreeAnimation(spit.anim);
    spitboy.spit.clear();
}

INTERNAL void KillSpit (Spit& spit)
{
    CreateParticles(PARTICLE_TYPE_PUFF, (int)spit.pos.x+4,(int)spit.pos.y+4,(int)spit.pos.x+4,(int)spit.pos.y+4, 1,3);
    CreateParticles(PARTICLE_TYPE_SPEC, (int)spit.pos.x+4,(int)spit.pos.y+4,(int)spit.pos.x+4,(int)spit.pos.y+4, 2,4, 1.5f);
    spit.dead = true;
    PlaySound(gSpitBoyHitSound);
}
