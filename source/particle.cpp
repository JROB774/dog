GLOBAL struct ParticleSystem
{
    std::vector<Particle> particles;
    Image image;
    float clear_timer;

} gParticleSystem;

INTERNAL void InitParticleSystem ()
{
    LoadImage(gParticleSystem.image, "effect.bmp");
    gParticleSystem.clear_timer = 0.0f;
}

INTERNAL void QuitParticleSystem ()
{
    FreeImage(gParticleSystem.image);
    gParticleSystem.particles.clear();
}

INTERNAL void CreateParticles (ParticleType type, int minx, int miny, int maxx, int maxy, int min_count, int max_count, float lifetime_multiplier)
{
    int count = RandomRange(min_count, max_count);
    for (int i=0; i<count; ++i)
    {
        gParticleSystem.particles.push_back(Particle());

        Particle& particle = gParticleSystem.particles.back();
        const ParticleBase& base = PARTICLE_BASE[type];

        ASSERT(base.create);
        ASSERT(base.update);

        particle.type = type;
        particle.vel = { 0,0 };
        LoadAnimation(particle.anim, base.anims[RandomRange(0, (int)base.anims.size()-1)]);
        particle.color = MakeColor(1,1,1);
        particle.dead = false;
        particle.visible = true;
        particle.lifetime = RandomFloatRange(base.min_lifetime, base.max_lifetime) * lifetime_multiplier;

        int fw = GetAnimationFrameWidth(particle.anim);
        int fh = GetAnimationFrameHeight(particle.anim);

        particle.pos.x = (float)RandomRange(minx-(fw/2), maxx-(fw/2));
        particle.pos.y = (float)RandomRange(miny-(fh/2), maxy-(fh/2));

        base.create(particle);
    }
}

INTERNAL void CreateParticles (ParticleType type, int minx, int miny, int maxx, int maxy, int count, float lifetime_multiplier)
{
    CreateParticles(type, minx, miny, maxx, maxy, count, count, lifetime_multiplier);
}

INTERNAL void UpdateParticles (float dt)
{
    for (auto& particle: gParticleSystem.particles)
    {
        if (!particle.dead)
        {
            PARTICLE_BASE[particle.type].update(particle, dt);
            if (particle.lifetime > 0.0f) // Particles with negative lifetime don't use it.
            {
                particle.lifetime -= dt;
                if (particle.lifetime <= 0.0f)
                {
                    particle.dead = true;
                }
            }
        }
    }

    // Every few seconds we remove dead particles from the array to keep memory usage low.
    gParticleSystem.clear_timer += dt;
    if (gParticleSystem.clear_timer >= 5.0f)
    {
        gParticleSystem.particles.erase(std::remove_if(
            gParticleSystem.particles.begin(), gParticleSystem.particles.end(),
            [](const Particle& p) { return p.dead; }),
            gParticleSystem.particles.end()
        );
    }
}

INTERNAL void DrawParticles (float dt)
{
    for (auto& particle: gParticleSystem.particles)
    {
        if (particle.visible && !particle.dead)
        {
            UpdateAnimation(particle.anim, dt);
            gParticleSystem.image.color = particle.color;
            DrawImage(gParticleSystem.image, particle.pos.x, particle.pos.y, FLIP_NONE, GetAnimationClip(particle.anim));
        }
    }
}

// PARTICLE_TYPE_TEST

INTERNAL void ParticleCreateTest (Particle& particle)
{
    // Nothing...
}

INTERNAL void ParticleUpdateTest (Particle& particle, float dt)
{
    // Nothing...
}

// PARTICLE_TYPE_SPEC

GLOBAL constexpr float PARTICLE_SPEC_FORCE = 90.0f;

INTERNAL void ParticleCreateSpec (Particle& particle)
{
    particle.vel = RotateVec2({ PARTICLE_SPEC_FORCE, 0.0f }, RandomFloatRange(0, (float)M_PI*2));
}

INTERNAL void ParticleUpdateSpec (Particle& particle, float dt)
{
    particle.pos.x += particle.vel.x * dt;
    particle.pos.y += particle.vel.y * dt;
}

// PARTICLE_TYPE_PUFF

GLOBAL constexpr float PARTICLE_PUFF_FORCE = 15.0f;
GLOBAL constexpr float PARTICLE_PUFF_RAISE =  4.0f;

INTERNAL void ParticleCreatePuff (Particle& particle)
{
    particle.vel = { -PARTICLE_PUFF_FORCE, 0.0f };
    particle.vel = RotateVec2(particle.vel, RandomFloatRange(DegToRad(30), DegToRad(150)));
}

INTERNAL void ParticleUpdatePuff (Particle& particle, float dt)
{
    if (IsAnimationDone(particle.anim)) particle.dead = true;
    if (Random() % 2 == 0) UpdateAnimation(particle.anim, dt); // Randomly update some frames faster to add variance.

    particle.vel.y -= PARTICLE_PUFF_RAISE;

    particle.pos.x += particle.vel.x * dt;
    particle.pos.y += particle.vel.y * dt;
    // particle.pos.y -= PARTICLE_PUFF_RAISE * dt;
}

// PARTICLE_BASH_FORCE

GLOBAL constexpr float PARTICLE_BASH_FORCE = 90.0f;

INTERNAL void ParticleCreateBash (Particle& particle)
{
    particle.vel = { PARTICLE_BASH_FORCE, 0.0f };
    particle.vel = RotateVec2(particle.vel, RandomFloatRange(DegToRad(30), DegToRad(150)));
}

INTERNAL void ParticleUpdateBash (Particle& particle, float dt)
{
    particle.pos.x += particle.vel.x * dt;
    particle.pos.y += particle.vel.y * dt;
}

// PARTICLE_BASH_EXPLODE1

INTERNAL void ParticleCreateExplode1 (Particle& particle)
{
    // Nothing...
}

INTERNAL void ParticleUpdateExplode1 (Particle& particle, float dt)
{
    if (IsAnimationDone(particle.anim)) particle.dead = true;
    if (Random() % 2 == 0) UpdateAnimation(particle.anim, dt); // Randomly update some frames faster to add variance.
}

// PARTICLE_TYPE_SMOKE

GLOBAL constexpr float PARTICLE_SMOKE_FORCE_MIN = 30.0f;
GLOBAL constexpr float PARTICLE_SMOKE_FORCE_MAX = 90.0f;
GLOBAL constexpr float PARTICLE_SMOKE_RAISE     =  1.0f;
GLOBAL constexpr float PARTICLE_SMOKE_DRAG      =  1.0f;

INTERNAL void ParticleCreateSmoke (Particle& particle)
{
    particle.vel = RotateVec2({ RandomFloatRange(PARTICLE_SMOKE_FORCE_MIN, PARTICLE_SMOKE_FORCE_MAX), 0.0f }, RandomFloatRange(0, (float)M_PI*2));
}

INTERNAL void ParticleUpdateSmoke (Particle& particle, float dt)
{
    if (Random() % 2 == 0) UpdateAnimation(particle.anim, dt); // Randomly update some frames faster to add variance.
    if (IsAnimationDone(particle.anim)) particle.lifetime = RandomFloatRange(0.0f, 0.8f);

    particle.vel.y -= PARTICLE_SMOKE_RAISE;

    if (particle.vel.x < 0.0f)
    {
        particle.vel.x += PARTICLE_SMOKE_DRAG;
        if (particle.vel.x > 0.0f) particle.vel.x = 0.0f;
    }
    else if (particle.vel.x > 0.0f)
    {
        particle.vel.x -= PARTICLE_SMOKE_DRAG;
        if (particle.vel.x < 0.0f) particle.vel.x = 0.0f;
    }

    particle.pos.x += particle.vel.x * dt;
    particle.pos.y += particle.vel.y * dt;
}
