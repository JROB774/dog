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
