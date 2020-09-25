#ifndef PARTICLE_HPP
#define PARTICLE_HPP

enum ParticleType
{
    PARTICLE_TYPE_TEST,
    PARTICLE_TYPE_SPEC,
    PARTICLE_TYPE_TOTAL
};

struct Particle
{
    ParticleType type;
    Vec2 pos,vel;
    Animation anim;
    Color color;
    bool dead;
    bool visible;

    // -1 can be used to make its life infinite. Which allows for the programmer
    // to specify a different method of deletion in the particle's update e.g.
    // after coming to a complete stop, travelling off-screen, etc.
    float lifetime;
};

INTERNAL void InitParticleSystem ();
INTERNAL void QuitParticleSystem ();

INTERNAL void CreateParticles (ParticleType type, int minx, int miny, int maxx, int maxy, int min_count, int max_count, float lifetime_multiplier = 1.0f);
INTERNAL void CreateParticles (ParticleType type, int minx, int miny, int maxx, int maxy, int count, float lifetime_multiplier = 1.0f);

INTERNAL void UpdateParticles (float dt);
INTERNAL void DrawParticles   (float dt);

// Create and update functions for the different particle types.

INTERNAL void ParticleCreateTest (Particle& particle);
INTERNAL void ParticleUpdateTest (Particle& particle, float dt);
INTERNAL void ParticleCreateSpec (Particle& particle);
INTERNAL void ParticleUpdateSpec (Particle& particle, float dt);

// Base information for each type of particle.

typedef void(*ParticleCreate)(Particle& particle);
typedef void(*ParticleUpdate)(Particle& particle, float dt);

struct ParticleBase
{
    ParticleCreate create;
    ParticleUpdate update;
    std::vector<std::string> anims;
    float min_lifetime;
    float max_lifetime;
};

GLOBAL const ParticleBase PARTICLE_BASE[PARTICLE_TYPE_TOTAL]
{
    { ParticleCreateTest, ParticleUpdateTest, { "effect-test0.anim", "effect-test1.anim", "effect-test2.anim", "effect-test3.anim" }, 0.5f, 2.5f }, // PARTICLE_TYPE_TEST
    { ParticleCreateSpec, ParticleUpdateSpec, { "effect-spec0.anim", "effect-spec1.anim", "effect-spec2.anim", "effect-spec3.anim", "effect-spec4.anim", "effect-spec5.anim", "effect-spec6.anim", "effect-spec7.anim" }, 0.05f, 0.2f }, // PARTICLE_TYPE_SPEC
};

#endif /* PARTICLE_HPP */
