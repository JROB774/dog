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

INTERNAL void CreateParticles (ParticleType type, int minx, int miny, int maxx, int maxy, int min_count, int max_count)
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
        particle.pos.x = (float)RandomRange(minx, maxx);
        particle.pos.y = (float)RandomRange(miny, maxy);
        particle.vel = { 0,0 };
        LoadAnimation(particle.anim, base.anims[RandomRange(0, (int)base.anims.size()-1)]);
        particle.dead = false;
        particle.visible = true;
        particle.lifetime = RandomFloatRange(base.min_lifetime, base.max_lifetime);

        base.create(particle);
    }
}

INTERNAL void CreateParticles (ParticleType type, int minx, int miny, int maxx, int maxy, int count)
{
    CreateParticles(type, minx, miny, maxx, maxy, count, count);
}

INTERNAL void UpdateParticles (float dt)
{
    for (auto& particle: gParticleSystem.particles)
    {
        if (!particle.dead)
        {
            PARTICLE_BASE[particle.type].update(particle, dt);
            particle.lifetime -= dt;
            if (particle.lifetime <= 0.0f)
            {
                particle.dead = true;
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
            DrawImage(gParticleSystem.image, particle.pos.x, particle.pos.y, FLIP_NONE, GetAnimationClip(particle.anim));
        }
    }
}

// Update functions for the different particle types.

INTERNAL void ParticleCreateTest0 (Particle& particle)
{
    // Nothing...
}

INTERNAL void ParticleUpdateTest0 (Particle& particle, float dt)
{
    // Nothing...
}
