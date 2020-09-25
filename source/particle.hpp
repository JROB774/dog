#ifndef PARTICLE_HPP
#define PARTICLE_HPP

enum ParticleType
{
    PARTICLE_TYPE_TEST0,
    PARTICLE_TYPE_TOTAL
};

struct Particle
{
    ParticleType type;
    Vec2 pos,vel;
    Animation anim;
    bool dead;
    bool visible;

    // -1 can be used to make its life infinite. Which allows for the programmer
    // to specify a different method of deletion in the particle's update e.g.
    // after coming to a complete stop, travelling off-screen, etc.
    float lifetime;
};

INTERNAL void InitParticleSystem ();
INTERNAL void QuitParticleSystem ();

INTERNAL void CreateParticles (ParticleType type, int minx, int miny, int maxx, int maxy, int min_count, int max_count);
INTERNAL void CreateParticles (ParticleType type, int minx, int miny, int maxx, int maxy, int count);

INTERNAL void UpdateParticles (float dt);
INTERNAL void DrawParticles   (float dt);

// Create and update functions for the different particle types.

INTERNAL void ParticleCreateTest0 (Particle& particle);
INTERNAL void ParticleUpdateTest0 (Particle& particle, float dt);

// Base information for each type of particle.

typedef void(*ParticleCreate)(Particle& particle);
typedef void(*ParticleUpdate)(Particle& particle, float dt);

struct ParticleBase
{
    ParticleCreate create;
    ParticleUpdate update;
    std::string animation;
};

GLOBAL const ParticleBase PARTICLE_BASE[PARTICLE_TYPE_TOTAL]
{
    { ParticleCreateTest0, ParticleUpdateTest0, "effect-test0.anim" }, // PARTIICLE_TYPE_TEST0
};

#endif /* PARTICLE_HPP */
